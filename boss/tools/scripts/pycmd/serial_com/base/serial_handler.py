
from typing import Callable, List, Optional

from .reset import Reset
from .line_matcher import LineMatcher
from .exceptions import SerialStopException
from .console_parser import ConsoleParser
from .console_reader import ConsoleReader
from .constants import CMD_ENTER_BOOT, CMD_OUTPUT_TOGGLE, CMD_RESET, CMD_STOP, CMD_TOGGLE_LOGGING, CMD_TOGGLE_TIMESTAMPS, CONSOLE_STATUS_QUERY
from .serial_reader import Reader
from .logger import Logger  # noqa: F401

from .output_helpers import ANSI_GREEN_B, ANSI_NORMAL_B, ANSI_RED_B, ANSI_YELLOW_B, AUTO_COLOR_REGEX, warning_print


class SerialHandler:
    """
    The class is responsible for buffering serial input and performing corresponding commands.
    """
    def __init__(self, last_line_part, logger, force_line_print, disable_auto_color,
                 serial_instance, target,
    ):
        self._last_line_part = last_line_part

        self.logger = logger
        self._force_line_print = force_line_print
        self._trailing_color = False
        self.disable_auto_color = disable_auto_color

        self.reset = Reset(serial_instance, target)

    def splitdata(self, data):  # type: (bytes) -> List[bytes]
        """
        Split data into lines, while keeping newlines, and move unfinished line for future processing
        """
        # if data is empty fallback to empty string for easier concatenation with last line
        sp = data.splitlines(keepends=True) or [b'']
        if self._last_line_part != b'':
            # add unprocessed part from previous "data" to the first line
            sp[0] = self._last_line_part + sp[0]
            self._last_line_part = b''
        if not sp[-1].endswith(b'\n'):
            # last part is not a full line
            self._last_line_part = sp.pop()
        return sp

    def print_colored(self, line: bytes) -> None:
        if self.disable_auto_color:
            self.logger.print(line)
            return

        # Line ending can be only at the end because of the split in splitdata
        line_stripped = line.rstrip(b'\r\n')
        new_line = line[len(line_stripped):]

        match = AUTO_COLOR_REGEX.match(line_stripped)
        if not match:
            if self._trailing_color and new_line:
                # Color set in some previous call and now we have a line
                # ending, so reset the color
                self.logger.print(line_stripped + ANSI_NORMAL_B + new_line)
                self._trailing_color = False
            else:
                # No color and no need for reset, just print the line
                self.logger.print(line)
            return

        if match.group(1) == b'I':
            color = ANSI_GREEN_B
        elif match.group(1) == b'W':
            color = ANSI_YELLOW_B
        elif match.group(1) == b'E':
            color = ANSI_RED_B

        if new_line:
            # Full line, print with color and reset
            self.logger.print(color + line_stripped + ANSI_NORMAL_B + new_line)
        else:
            # Partial line, print with color and without reset, which will be
            # handled by some future call
            self.logger.print(color + line)
            self._trailing_color = True

    def handle_serial_input(self, data, console_parser, coredump, gdb_helper, line_matcher,
                            check_gdb_stub_and_run, finalize_line=False):
        #  type: (bytes, ConsoleParser, CoreDump, Optional[GDBHelper], LineMatcher, Callable, bool) -> None
        pass

    def check_panic_decode_trigger(self, line):  # type: (bytes) -> None
        pass

    def get_flashed_sha256(self, line: str) -> Optional[str]:
        pass

    def compare_elf_sha256(self, line):  # type: (str) -> None
        pass

    def handle_commands(self, cmd, console_reader, serial_reader):
        # type: (int, ConsoleReader, Reader) -> None
        if cmd == CMD_STOP:
            console_reader.stop()
            serial_reader.stop()
        elif cmd == CMD_RESET:
            self.reset.hard()
            self.logger.output_enabled = True
        elif cmd == CMD_OUTPUT_TOGGLE:
            self.logger.output_toggle()
        elif cmd == CMD_TOGGLE_TIMESTAMPS:
            self.logger.toggle_timestamps()
        elif cmd == CMD_TOGGLE_LOGGING:
            self.logger.toggle_logging()
        else:
            raise RuntimeError('Bad command data %d' % cmd)  # type: ignore


class SerialHandlerNoElf(SerialHandler):
    def handle_serial_input(self, data, line_matcher, finalize_line=False):
        #  type: (bytes, LineMatcher, bool) -> None
        sp = self.splitdata(data)
        for line in sp:
            if line_matcher.match(line.decode(errors='ignore')):
                self.print_colored(line)

        if self._last_line_part.startswith(CONSOLE_STATUS_QUERY):
            self.logger.print(CONSOLE_STATUS_QUERY)
            self._last_line_part = self._last_line_part[len(CONSOLE_STATUS_QUERY):]

        if self._last_line_part != b'':
            self.print_colored(self._last_line_part)
            self._last_line_part = b''
