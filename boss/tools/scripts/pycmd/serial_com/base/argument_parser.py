# SPDX-FileCopyrightText: 2015-2024 Espressif Systems (Shanghai) CO LTD
# SPDX-License-Identifier: Apache-2.0

import argparse
import os
import sys

from .constants import DEFAULT_PRINT_FILTER, DEFAULT_TARGET_RESET

# list environment variable follow as:
SERIAL_PORT1="ESPTOOL_PORT"
SERIAL_BAUD1="IDF_MONITOR_BAUD"
SERIAL_BAUD2="MONITORBAUD"
IDF_TARGET="IDF_TARGET"
ESP_IDF_MONITOR_WS=""
ESP_IDF_MONITOR_PRINT_FILTER="ESP_IDF_MONITOR_PRINT_FILTER"
ESP_IDF_MONITOR_NO_RESET="ESP_IDF_MONITOR_NO_RESET"

def get_parser():  # type: () -> argparse.ArgumentParser
    parser = argparse.ArgumentParser('serial_com - a serial output Com.')

    parser.add_argument(
        '--port', '-p',
        help='Serial port device. If not set, a connected port will be used.' +
        (' Defaults to `/dev/ttyUSB0` if connected.' if sys.platform == 'linux' else ''),
        default=os.environ.get(SERIAL_PORT1, None)
    )

    parser.add_argument(
        '--baud', '-b',
        help='Serial port baud rate',
        type=int,
        default=os.getenv(SERIAL_BAUD1, os.getenv(SERIAL_BAUD2, 115200)))

    parser.add_argument(
        '--eol',
        choices=['CR', 'LF', 'CRLF'],
        type=lambda c: c.upper(),
        help='End of line to use when sending to the serial port. '
             'Defaults to LF for Linux targets and CR otherwise.',
        )

    parser.add_argument(
        '--ws',
        default=os.environ.get(ESP_IDF_MONITOR_WS, None),
        help='WebSocket URL for communicating with IDE tools for debugging purposes'
    )

    parser.add_argument(
        '--target',
        help='Target name (used when stack dump decoding is enabled)',
        default=os.environ.get('IDF_TARGET', 'esp32')
    )

    parser.add_argument(
        '--print_filter',
        help='Filtering string',
        default=os.environ.get(ESP_IDF_MONITOR_PRINT_FILTER, DEFAULT_PRINT_FILTER))

    parser.add_argument(
        '--no-reset',
        help='Do not reset the chip on monitor startup',
        action='store_true',
        default=bool(os.getenv(ESP_IDF_MONITOR_NO_RESET, not DEFAULT_TARGET_RESET))
    )

    parser.add_argument(
        '--timestamps',
        help='Add timestamp for each line',
        default=False,
        action='store_true')

    parser.add_argument(
        '--timestamp-format',
        default=os.environ.get('ESP_IDF_MONITOR_TIMESTAMP_FORMAT', '%Y-%m-%d %H:%M:%S'),
        help='Set a strftime()-compatible timestamp format'
    )

    parser.add_argument(
        '--force-color',
        help='Always colored monitor output, even if output is redirected.',
        default=False,
        action='store_true')

    parser.add_argument(
        '--disable-auto-color',
        help='Disable automatic color addition to monitor output based on the log level',
        default=False,
        action='store_true')

    parser.add_argument(
        '--open-port-attempts',
        help='Number of attempts to wait for the port to appear (useful if the device is not connected or in deep sleep). '
        'The delay between attempts can be defined by the `reconnect_delay` option in a configuration file (by default 0.5 sec). '
        'Use 0 for infinite attempts.',
        default=1,
        type=int
    )

    return parser
