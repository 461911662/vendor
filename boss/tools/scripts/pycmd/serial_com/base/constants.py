# SPDX-FileCopyrightText: 2015-2024 Espressif Systems (Shanghai) CO LTD
# SPDX-License-Identifier: Apache-2.0


# Control-key characters
CTRL_C = '\x03'
CTRL_H = '\x08'

# VT100 escape sequences
CONSOLE_STATUS_QUERY = b'\x1b[5n'

# Command parsed from console inputs
CMD_STOP = 1
CMD_RESET = 2
CMD_OUTPUT_TOGGLE = 3
CMD_TOGGLE_LOGGING = 4
CMD_ENTER_BOOT = 5
CMD_TOGGLE_TIMESTAMPS = 6

# Tags for tuples in queues
TAG_KEY = 0
TAG_SERIAL = 1
TAG_SERIAL_FLUSH = 2
TAG_CMD = 3

DEFAULT_TOOLCHAIN_PREFIX = 'xtensa-esp32-elf-'

DEFAULT_PRINT_FILTER = ''
DEFAULT_TARGET_RESET = False  # reset target when open serial

# panic handler decoding states
PANIC_IDLE = 0
PANIC_READING = 1
PANIC_READING_STACK = 2

# panic handler decoding options
PANIC_DECODE_DISABLE = 'disable'
PANIC_DECODE_BACKTRACE = 'backtrace'

EVENT_QUEUE_TIMEOUT = 0.03  # timeout before raising queue.Empty exception in case of empty event queue

RECONNECT_DELAY =  0.5  # timeout between reconnect tries
CHECK_ALIVE_FLAG_TIMEOUT = 0.25  # timeout for checking alive flags (currently used by serial reader)

# Port names to filter out
FILTERED_PORTS = ('Bluetooth-Incoming-Port', 'wlan-debug')

# closing wait timeout for serial port
ASYNC_CLOSING_WAIT_NONE = 0xFFFF  # don't wait at all

# DTR and RTS pin settings
LOW = True
HIGH = False
