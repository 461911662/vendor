# SPDX-FileCopyrightText: 2015-2023 Espressif Systems (Shanghai) CO LTD
# SPDX-License-Identifier: Apache-2.0

import re


class LineMatcher(object):
    """
    Assembles a dictionary of filtering rules based on the --print_filter
    argument of serial_com. Then later it is used to match lines and
    determine whether they should be shown on screen or not.
    """

    def __init__(self, print_filter):
        # type: (str) -> None
        pass

    def match(self, line):
        # type: (str) -> bool
        return True