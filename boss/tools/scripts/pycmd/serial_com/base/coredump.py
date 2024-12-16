# SPDX-FileCopyrightText: 2023 Espressif Systems (Shanghai) CO LTD
# SPDX-License-Identifier: Apache-2.0

# coredump states
from contextlib import contextmanager
import queue
from typing import Generator, List, Optional

from .logger import Logger


COREDUMP_IDLE = 0
COREDUMP_READING = 1
COREDUMP_DONE = 2

# coredump decoding options
COREDUMP_DECODE_DISABLE = 'disable'
COREDUMP_DECODE_INFO = 'info'

class CoreDump:
    def __init__(self, decode_coredumps, event_queue, logger, elf_files):
        # type: (str, queue.Queue, Logger, List[str]) -> None

        self._coredump_buffer = b''
        self._decode_coredumps = decode_coredumps
        self.event_queue = event_queue
        self._reading_coredump = COREDUMP_IDLE
        self.logger = logger
        self.elf_files = elf_files[0]

    @property
    def in_progress(self) -> bool:
        return bool(self._coredump_buffer)

    @contextmanager
    def check(self, line):  # type: (bytes) -> Generator
        self._check_coredump_trigger_before_print(line)
        try:
            yield
        finally:
            self._check_coredump_trigger_after_print()

    def _check_coredump_trigger_before_print(self, line):  # type: (bytes) -> None
        if self._decode_coredumps == COREDUMP_DECODE_DISABLE:
            return
        # TODO: 如下是检测到coredump之后的操作：
        # 将coredump状态更新为COREDUMP_READING
        # 关闭日志日志输出到终端，self.logger.output_enabled = False
        # 接收coredump文件保存到本地self._coredump_buffer
        # 完成后更新为COREDUMP_DONE

    def _check_coredump_trigger_after_print(self):  # type: () -> None
        if self._decode_coredumps == COREDUMP_DECODE_DISABLE:
            return

        # Re-enable output after the last line of core dump has been consumed
        if not self.logger.output_enabled and self._reading_coredump == COREDUMP_DONE:
            self._reading_coredump = COREDUMP_IDLE
            self.logger.output_enabled = True
            self._coredump_buffer = b''
