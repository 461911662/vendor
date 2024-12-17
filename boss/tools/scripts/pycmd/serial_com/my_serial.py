import codecs
import io
import os
import subprocess
import sys
import queue
import threading
from typing import Any, List, NoReturn, Optional, Type, Union  # noqa: F401

import serial
from serial.tools import list_ports, miniterm

from .base.exceptions import SerialStopException
from .base.ansi_color_converter import get_ansi_converter
from .base.argument_parser import get_parser
from .base.console_parser import ConsoleParser
from .base.console_reader import ConsoleReader
from .base.constants import DEFAULT_TARGET_RESET, DEFAULT_TOOLCHAIN_PREFIX, EVENT_QUEUE_TIMEOUT, PANIC_DECODE_DISABLE, PANIC_IDLE, TAG_CMD, TAG_KEY, TAG_SERIAL, TAG_SERIAL_FLUSH
from .base.coredump import COREDUMP_DECODE_INFO, CoreDump
from .base.line_matcher import LineMatcher
from .base.logger import Logger
from .base.output_helpers import normal_print, note_print, warning_print
from .base.serial_handler import SerialHandler, SerialHandlerNoElf
from .base.serial_reader import LinuxReader, Reader, SerialReader
from .base.web_socket_client import WebSocketClient

from . import __version__

key_description = miniterm.key_description

# list environment variable follow as:
IDF_SERIAL_FLAG_TEST='ESP_IDF_MONITOR_TEST'

class Controller:
    """
    Serial application base class.

    This was originally derived from miniterm.Miniterm, but it turned out to be easier to write from scratch for this
    purpose.

    Main difference is that all event processing happens in the main thread, not the worker threads.
    """

    def __init__(
        self,
        serial_instance,  # type: serial.Serial
        elf_files,  # type: List[str]
        print_filter,  # type: str
        reset=DEFAULT_TARGET_RESET,  # type: bool
        open_port_attempts=1,  # type: int
        toolchain_prefix=DEFAULT_TOOLCHAIN_PREFIX,  # type: str
        eol='CRLF',  # type: str
        decode_coredumps=COREDUMP_DECODE_INFO,  # type: str
        decode_panic=PANIC_DECODE_DISABLE,  # type: str
        target='esp32',  # type: str
        timestamps=False,  # type: bool
        timestamp_format='',  # type: str
        force_color=False,  # type: bool
        disable_auto_color=False,  # type: bool
    ):
        self.event_queue = queue.Queue()  # type: queue.Queue
        self.cmd_queue = queue.Queue()  # type: queue.Queue
        self.console = miniterm.Console()
        # if the variable is set ANSI will be printed even if we do not print to terminal
        sys.stderr = get_ansi_converter(sys.stderr, force_color=force_color)  # type: ignore
        self.console.output = get_ansi_converter(self.console.output, force_color=force_color)
        self.console.byte_output = get_ansi_converter(self.console.byte_output, force_color=force_color)

        self.elf_files = elf_files or []
        self.elf_exists = False
        self.logger = Logger(self.elf_files, self.console, timestamps, timestamp_format)

        self.coredump = CoreDump(decode_coredumps, self.event_queue, self.logger,
                                 self.elf_files) if self.elf_exists else None

        self.target = target

        if isinstance(self, SerialController):
            # testing hook: when running tests, input from console is ignored
            socket_test_mode = os.environ.get(IDF_SERIAL_FLAG_TEST) == '1'
            self.serial = serial_instance
            self.serial_reader = SerialReader(self.serial, self.event_queue, reset, open_port_attempts, target)  # type: Reader
        else:
            socket_test_mode = False
            self.serial = subprocess.Popen(self.elf_files, stdin=subprocess.PIPE, stdout=subprocess.PIPE,
                                           stderr=subprocess.STDOUT, bufsize=0)
            self.serial_reader = LinuxReader(self.serial, self.event_queue)

        cls = SerialHandler if self.elf_exists else SerialHandlerNoElf
        self.serial_handler = cls(b'', self.logger, True, disable_auto_color, self.serial, target)

        self.console_parser = ConsoleParser(eol)
        self.console_reader = ConsoleReader(self.console, self.event_queue, self.cmd_queue, self.console_parser,
                                            socket_test_mode)

        self._line_matcher = LineMatcher(print_filter)

        # internal state
        self._invoke_processing_last_line_timer = None  # type: Optional[threading.Timer]

    def __enter__(self) -> None:
        """ Use 'with self' to temporarily disable monitoring behaviour """
        self.serial_reader.stop()
        self.console_reader.stop()

    def __exit__(self, exc_type, exc_val, exc_tb) -> None:  # type: ignore
        raise NotImplementedError

    def _pre_start(self) -> None:
        self.console_reader.start()
        self.serial_reader.start()

    def main_loop(self) -> None:
        self._pre_start()

        try:
            while (self.console_reader.alive and self.serial_reader.alive) or True:
                try:
                    self._main_loop()
                except KeyboardInterrupt:
                    raise
        except SerialStopException:
            normal_print('Stopping condition has been received\n')
        except KeyboardInterrupt:
            raise
        finally:
            try:
                self.console_reader.stop()
                self.serial_reader.stop()
                self.logger.stop_logging()
                # Cancelling _invoke_processing_last_line_timer is not
                # important here because receiving empty data doesn't matter.
                self._invoke_processing_last_line_timer = None
            except Exception:  # noqa
                raise
            normal_print('\n')

    def serial_write(self, *args: str, **kwargs: str) -> None:
        raise NotImplementedError

    def _main_loop(self) -> None:
        try:
            item = self.cmd_queue.get_nowait()
        except queue.Empty:
            try:
                item = self.event_queue.get(timeout=EVENT_QUEUE_TIMEOUT)
            except queue.Empty:
                return

        event_tag, data = item
        if event_tag == TAG_CMD:
            self.serial_handler.handle_commands(data, self.console_reader, self.serial_reader)
        elif event_tag == TAG_KEY: # 将终端输入的数据发送到串口设备
            self.serial_write(codecs.encode(data))
        elif event_tag == TAG_SERIAL: # 将收到的串口数据显示到终端
            self.serial_handler.handle_serial_input(data, self._line_matcher)
            # If no further data is received in the next short period
            # of time then the _invoke_processing_last_line_timer
            # generates an event which will result in the finishing of
            # the last line. This is fix for handling lines sent
            # without EOL.
            # finalizing the line when coredump is in progress causes decoding issues
            # the espcoredump loader uses empty line as a sign for end-of-coredump
            # line is finalized only for non coredump data
        elif event_tag == TAG_SERIAL_FLUSH:
            pass
        else:
            raise RuntimeError('Bad event data %r' % ((event_tag, data),))


class SerialController(Controller):
    def __exit__(self, exc_type, exc_val, exc_tb) -> None:  # type: ignore
        """ Use 'with self' to temporarily disable monitoring behaviour """
        self.console_reader.start()
        if self.elf_exists:
            self.serial_reader.gdb_exit = self.gdb_helper.gdb_exit  # type: ignore # write gdb_exit flag
        self.serial_reader.start()

    def _pre_start(self) -> None:
        super()._pre_start()
        if self.elf_exists:
            self.gdb_helper.gdb_exit = False  # type: ignore
        self.serial_handler.start_cmd_sent = False

    def serial_write(self, *args: str, **kwargs: str) -> None:
        self.serial: serial.Serial
        try:
            self.serial.write(*args, **kwargs)
            self.timeout_cnt = 0
        except serial.SerialTimeoutException:
            if not self.timeout_cnt:
                warning_print('Writing to serial is timing out. Please make sure that your application supports '
                              'an interactive console and that you have picked the correct console for serial communication.')
            self.timeout_cnt += 1
            self.timeout_cnt %= 3
        except serial.SerialException:
            pass  # this shouldn't happen, but sometimes port has closed in serial thread
        except UnicodeEncodeError:
            pass  # this can happen if a non-ascii character was passed, ignoring

    def _main_loop(self) -> None:
        super()._main_loop()


class LinuxSerialController(Controller):
    def __exit__(self, exc_type, exc_val, exc_tb) -> None:  # type: ignore
        """ Use 'with self' to temporarily disable monitoring behaviour """
        self.console_reader.start()
        self.serial_reader.start()

    def serial_write(self, *args: str, **kwargs: str) -> None:
        self.serial.stdin.write(*args, **kwargs)
        self.serial.stdin.flush()

    def check_gdb_stub_and_run(self, line: bytes) -> None:
        return  # fake function for linux target


def detect_port() -> Union[str, NoReturn]:
    """Detect connected ports and return the last one"""
    try:
        port_list = list_ports.comports()
        if sys.platform == 'darwin':
            port_list = [
                port
                for port in port_list
                if not port.device.endswith(FILTERED_PORTS)
            ]
        port: str = port_list[-1].device
        # keep the `/dev/ttyUSB0` default port on linux if connected
        # TODO: This can be removed in next major release
        if sys.platform == 'linux':
            for p in port_list:
                if p.device == '/dev/ttyUSB0':
                    port = p.device
                    break
        note_print(f'Using autodetected port {port}')
        return port
    except IndexError:
        sys.exit('No serial ports detected.')


def main() -> None:
    if not sys.stdin.isatty():
        sys.exit('Error: my_serial requires standard input to be attached to TTY. Try using a different terminal.')
    parser = get_parser()
    args = parser.parse_args()

    # use EOL from argument; defaults to LF for Linux targets and CR otherwise
    args.eol = args.eol or ('LF' if args.target == 'linux' else 'CR')

    ws = WebSocketClient(args.ws) if args.ws else None
    try:
        cls: Type[Controller]
        if args.target == 'linux':
            serial_instance = None
            cls = LinuxSerialController
            note_print(f'serial_com {__version__} on linux')
        else:
            # The port name is changed in cases described in the following lines.
            # Use a local argument and avoid the modification of args.port.
            port = args.port

            # if no port was set, detect connected ports and use one of them
            if port is None:
                port = detect_port()
            # GDB uses CreateFile to open COM port, which requires the COM name to be r'\\.\COMx' if the COM
            # number is larger than 10
            if os.name == 'nt' and port.startswith('COM'):
                port = port.replace('COM', r'\\.\COM')
                warning_print('GDB cannot open serial ports accessed as COMx')
                note_print(f'Using {port} instead...')
            elif port.startswith('/dev/tty.') and sys.platform == 'darwin':
                port = port.replace('/dev/tty.', '/dev/cu.')
                warning_print('Serial ports accessed as /dev/tty.* will hang gdb if launched.')
                note_print(f'Using {port} instead...')

            serial_instance = serial.serial_for_url(port, args.baud, do_not_open=True, exclusive=True)
            # setting write timeout is not supported for RFC2217 in pyserial
            if not port.startswith('rfc2217://'):
                serial_instance.write_timeout = 0.3

            cls = SerialController
            note_print('serial_com {v} on {p.name} {p.baudrate}'.format(v=__version__, p=serial_instance))

        controller  = cls(serial_instance,
                        "",
                        args.print_filter,
                        not args.no_reset,
                        args.open_port_attempts,
                        "", #args.toolchain_prefix,
                        args.eol,
                        "", #args.decode_coredumps,
                        "", #args.decode_panic,
                        args.target,
                        args.timestamps,
                        args.timestamp_format,
                        args.force_color,
                        args.disable_auto_color)

        controller.main_loop()
    except KeyboardInterrupt:
        pass
    finally:
        if ws:
            ws.close()
