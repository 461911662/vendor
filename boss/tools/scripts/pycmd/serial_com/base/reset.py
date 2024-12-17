# SPDX-FileCopyrightText: 2023 Espressif Systems (Shanghai) CO LTD
# SPDX-License-Identifier: Apache-2.0

import os
import time
import struct
from typing import Optional

import serial
from serial.tools import list_ports

from .constants import HIGH, LOW
from .output_helpers import error_print

if os.name != 'nt':
    import fcntl
    import termios

    # Constants used for terminal status lines reading/setting.
    # Taken from pySerial's backend for IO:
    # https://github.com/pyserial/pyserial/blob/master/serial/serialposix.py
    TIOCMSET = getattr(termios, 'TIOCMSET', 0x5418)
    TIOCMGET = getattr(termios, 'TIOCMGET', 0x5415)
    TIOCM_DTR = getattr(termios, 'TIOCM_DTR', 0x002)
    TIOCM_RTS = getattr(termios, 'TIOCM_RTS', 0x004)


class Reset:

    format_dict = {
        'D': 'self._setDTR({})',
        'R': 'self._setRTS({})',
        'W': 'time.sleep({})',
        'U': 'self._setDTRandRTS({})',
    }

    def __init__(self, serial_instance: serial.Serial, chip: str) -> None:
        self.serial_instance = serial_instance
        self.port_pid = self._get_port_pid()
        self.chip = chip

    def _get_port_pid(self) -> Optional[int]:
        """Get port PID to differentiate between JTAG and UART reset sequences"""
        if not hasattr(self.serial_instance, 'port'):
            # Linux target serial does not have a port and thus does not support resseting
            return None
        for port in list_ports.comports():
            if port.device == self.serial_instance.port:
                return port.pid  # type: ignore
        return None  # port not found in connected ports

    def _setDTR(self, value: bool) -> None:
        """Wrapper for setting DTR"""
        self.serial_instance.setDTR(value)

    def _setRTS(self, value: bool) -> None:
        """Wrapper for setting RTS with workaround for Windows"""
        self.serial_instance.setRTS(value)
        self.serial_instance.setDTR(self.serial_instance.dtr)  # usbser.sys workaround

    def _setDTRandRTS(self, dtr: bool = HIGH, rts: bool = HIGH) -> None:
        """Set DTR and RTS at the same time, this is only supported on linux with custom reset sequence"""
        if not self.serial_instance.is_open:
            error_print('Serial port is not connected')
            return None
        status = struct.unpack(
            'I', fcntl.ioctl(self.serial_instance.fileno(), TIOCMGET, struct.pack('I', 0))
        )[0]
        if dtr:
            status |= TIOCM_DTR
        else:
            status &= ~TIOCM_DTR
        if rts:
            status |= TIOCM_RTS
        else:
            status &= ~TIOCM_RTS
        fcntl.ioctl(self.serial_instance.fileno(), TIOCMSET, struct.pack('I', status))

    def _parse_string_to_seq(self, seq_str: str) -> str:
        """Parse custom reset sequence from a config"""
        try:
            cmds = seq_str.split('|')
            fn_calls_list = [self.format_dict[cmd[0]].format(cmd[1:]) for cmd in cmds]
        except Exception as e:
            error_print(f'Invalid "custom_reset_sequence" option format: {e}')
            return ''
        return '\n'.join(fn_calls_list)

    def hard(self) -> None:
        """Hard reset chip"""
        self._setRTS(LOW)  # EN=LOW, chip in reset
        time.sleep(0.3)
        self._setRTS(HIGH)  # EN=HIGH, chip out of reset

    def to_bootloader(self) -> None:
        """Reset chip into bootloader"""
        pass
