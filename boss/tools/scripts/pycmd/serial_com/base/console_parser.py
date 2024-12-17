# SPDX-FileCopyrightText: 2015-2023 Espressif Systems (Shanghai) CO LTD
# SPDX-License-Identifier: Apache-2.0

import queue
import textwrap
from typing import Any, Optional

from serial.tools import miniterm

from pycmd.serial_com import __version__

from .output_helpers import COMMON_PREFIX, error_print, note_print, red_print
from .key_config import CHIP_RESET_KEY, COMMAND_KEYS, EXIT_KEY, EXIT_MENU_KEY, MENU_KEY, SKIP_MENU_KEY, TOGGLE_LOG_KEY, TOGGLE_OUTPUT_KEY, TOGGLE_TIMESTAMPS_KEY
from .constants import CMD_OUTPUT_TOGGLE, CMD_RESET, CMD_STOP, CMD_TOGGLE_LOGGING, CMD_TOGGLE_TIMESTAMPS, CTRL_H, TAG_CMD, TAG_KEY

key_description = miniterm.key_description

class ConsoleParser(object):

    def __init__(self, eol='CRLF'):  # type: (str) -> None
        self.translate_eol = {
            'CRLF': lambda c: c.replace('\n', '\r\n'),
            'CR': lambda c: c.replace('\n', '\r'),
            'LF': lambda c: c.replace('\r', '\n'),
        }[eol]
        self._pressed_menu_key = False

    def parse(self, key):  # type: (str) -> Optional[tuple]
        ret = None
        # check for command_keys, so the monitor will not complain about not know key, when used with skip menu option
        if self._pressed_menu_key or (SKIP_MENU_KEY and key in COMMAND_KEYS):
            ret = self._handle_menu_key(key)
        elif key == MENU_KEY:
            self._pressed_menu_key = True
            note_print('Entry Serial_com Menu: '
                    f'Type {key_description(CTRL_H)}, h, H, or ? '
                    'to see help.', prefix='\n')
        elif key == EXIT_KEY:
            ret = (TAG_CMD, CMD_STOP)
        else:
            key = self.translate_eol(key)
            ret = (TAG_KEY, key)
        return ret

    def _handle_menu_key(self, c):  # type: (str) -> Optional[tuple]
        ret = None  # type: Optional[tuple[int, Any[str, int]]]
        if c in [EXIT_KEY, MENU_KEY]:  # send verbatim
            ret = (TAG_KEY, c)
        elif c in [CTRL_H, 'h', 'H', '?']:
            red_print(self.get_help_text())
        elif c == TOGGLE_OUTPUT_KEY:  # Toggle output display
            ret = (TAG_CMD, CMD_OUTPUT_TOGGLE)
        elif c in [EXIT_MENU_KEY, 'x', 'X']:  # Exiting from within the menu
            ret = (TAG_CMD, CMD_STOP)
        elif c in [TOGGLE_TIMESTAMPS_KEY, 'i', 'I']:  # Toggle printing timestamps
            ret = (TAG_CMD, CMD_TOGGLE_TIMESTAMPS)
        elif c == TOGGLE_LOG_KEY:  # Toggle saving output into file
            ret = (TAG_CMD, CMD_TOGGLE_LOGGING)
        elif c == CHIP_RESET_KEY:  # Reset device via RTS
            ret = (TAG_CMD, CMD_RESET)
        else:
            error_print(f'Unknown menu character {key_description(c)}')

        if self._pressed_menu_key:
            self._pressed_menu_key = False
            note_print('Exit Serial_com Menu.', prefix='\n')
        return ret

    def get_help_text(self):  # type: () -> str
        text = f"""\n\
            {COMMON_PREFIX} serial_com ({__version__}) - Serial Controller tool
            {COMMON_PREFIX} based on miniterm from pySerial
            {COMMON_PREFIX}
            {COMMON_PREFIX} {key_description(EXIT_KEY):8} Exit program
            {COMMON_PREFIX} {key_description(MENU_KEY):8} Menu escape key, followed by:
            {COMMON_PREFIX} Menu keys:
            {COMMON_PREFIX}    {key_description(MENU_KEY):14} Send the menu character itself to remote
            {COMMON_PREFIX}    {key_description(EXIT_KEY):14} Send the exit character itself to remote
            {COMMON_PREFIX}    {key_description(CHIP_RESET_KEY):14} Reset target board via RTS line
            {COMMON_PREFIX}    {key_description(TOGGLE_OUTPUT_KEY):14} Toggle output display
            {COMMON_PREFIX}    {key_description(TOGGLE_LOG_KEY):14} Toggle saving output into file
            {COMMON_PREFIX}    {key_description(TOGGLE_TIMESTAMPS_KEY) + ' (or I)':14} Toggle printing timestamps
            {COMMON_PREFIX}    {key_description(EXIT_MENU_KEY) + ' (or X)':14} Exit program"""

        if SKIP_MENU_KEY:
            text += f"""
            {COMMON_PREFIX}
            {COMMON_PREFIX} Using the "skip_menu_key" option from a config file. Commands can be executed without pressing the menu escape key.
            """
        return textwrap.dedent(text)

    def get_next_action_text(self):  # type: () -> str
        pass

    def parse_next_action_key(self, c):  # type: (str) -> Optional[tuple]
        pass

def prompt_next_action(reason, console, console_parser, event_queue, cmd_queue):
    # type: (str, miniterm.Console, ConsoleParser, queue.Queue, queue.Queue) -> None
    console.setup()  # set up console to trap input characters
    try:
        red_print(f'{COMMON_PREFIX} {reason}')
        red_print(console_parser.get_next_action_text())

        k = MENU_KEY  # ignore CTRL-T here, so people can muscle-memory Ctrl-T Ctrl-F, etc.
        while k == MENU_KEY:
            k = console.getkey()
    finally:
        console.cleanup()
    ret = console_parser.parse_next_action_key(k)
    if ret is not None:
        cmd = ret[1]
        if cmd == CMD_STOP:
            # the stop command should be handled last
            event_queue.put(ret)
        else:
            cmd_queue.put(ret)
