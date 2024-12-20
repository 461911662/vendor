
import binascii
import os
import subprocess
import sys
from typing import Any, Dict, List
from click import Context

from pycmd.utils import fatal, info
from pycmd.idf_py_actions.tools import PropertyDict
from pycmd.config.parser import get_config_type, is_supported_config_types, parser_config

# Some ports used by QEMU. Could be made configurable, if necessary.
# Note that port 3333 is also assumed by gdb extension.
QEMU_PORT_SERIAL = 5555
PYSERIAL_PORT = f'socket://localhost:{QEMU_PORT_SERIAL}'
QEMU_PORT_GDB = 3333
GBD_PORT = f'localhost:{QEMU_PORT_GDB}'

QEMU_SYSTEM_XTENSA='qemu-system-xtensa'
QEMU_MERGED_BIN='nuttx.merged.bin'

class QemuTaskRunOptions:
    """
    Some options related to QEMU execution, which depend on the presence of other tasks: gdb and monitor.
    """
    def __init__(self) -> None:
        self.bg_mode = False
        self.wait_for_gdb = False
        self.wait_for_monitor = False

def action_extensions(base_actions: Dict, project_path: str) -> Dict:
    # Shared state between "global_callback" and "qemu" action.
    # Stores options which depend on the presence of other tasks.

    def global_callback(ctx: Context, global_args: Dict, tasks: List) -> None:
        pass

    def _add_qemu_xtensa_args(args: PropertyDict, cfg: dict) -> List:
        chip = cfg['chip']
        flash_size = '16MB'
        bin_path = os.path.join(args.build_dir, QEMU_MERGED_BIN)
        info(f'Generating flash image: {bin_path}')
        subprocess.check_call([
            sys.executable, '-m', 'esptool', f'--chip={chip}', 'merge_bin', f'--output={bin_path}',
            f'--fill-flash-size={flash_size}', '@flash_args'], cwd=args.build_dir)

        efuse_bin_path = os.path.join(args.build_dir, 'qemu_efuse.bin')
        info(f'Generating efuse image: {efuse_bin_path}')
        efuse_data = ''
        for data in cfg['default_efuse']:
            efuse_data += data
        efuse_data = binascii.unhexlify(efuse_data)
        with open(efuse_bin_path, 'wb') as f:
            f.write(efuse_data)

        # set qemu_args for esp32
        qemu_args = [
            '-drive', f'file={bin_path},if=mtd,format=raw',
            '-drive', f'file={efuse_bin_path},if=none,format=raw,id=efuse', '-global', f'driver=nvram.{chip}.efuse,property=drive,value=efuse',
            '-global', f'driver=timer.{chip}.timg,property=wdt_disable,value=true',
        ]
        return qemu_args

    def _load_config(type: str, target: str) -> Any:
        path = os.path.dirname(os.path.abspath(__file__))
        path = os.path.join(os.path.dirname(path), 'config', type, target)
        if not os.path.exists(path):
            fatal(f'{path} not exists.')
            return
        return parser_config(type, path)

    def qemu(action: str, ctx: Context, args: PropertyDict, target: str, qemu_extra_args: str, gdb: bool, graphics: bool) -> None:
        if not is_supported_config_types(action):
            fatal(f'QEMU is not supported for config {action}')
            return

        obj = _load_config('qemu', target)
        if not obj:
            fatal(f'QEMU parser config failed')
            return

        config = get_config_type('qemu')
        qemu_args = [config['target']['qemu_prog']]
        qemu_args += config['target']['args'].split(' ')
        if config['target']['qemu_prog'] == QEMU_SYSTEM_XTENSA:
            qemu_args += _add_qemu_xtensa_args(args, config['target'])
        else:
            pass

        if '-nic' not in qemu_extra_args:
            qemu_args += ['-nic', 'user,model=open_eth']

        if gdb:
            qemu_args += ['-gdb', f'tcp::{QEMU_PORT_GDB}', '-S']

        if qemu_extra_args:
            qemu_args += qemu_extra_args.split(' ')

        if graphics:
            qemu_args += ['-display', 'sdl']
        else:
            qemu_args += ['-nographic']

        qemu_args += ['-serial', 'mon:stdio']
        info('Running qemu (fg): ' + ' '.join(qemu_args))
        subprocess.run(qemu_args)

    qemu_actions = {
        'global_action_callbacks': [global_callback],
        'actions': {
            'qemu': {
                'callback': qemu,
                'help': 'Run QEMU.',
                # 'dependencies': ['all'],
                'options': [
                    {
                        'names': ['--qemu-extra-args'],
                        'help': 'Extra arguments to pass to QEMU',
                        'hidden': False,
                        'is_flag': False,
                        'default': '',
                    },
                    {
                        'names': ['-t', '--target'],
                        'help': ('Specify a target for running QEMU.'),
                        'hidden': False,
                        'is_flag': False,
                        'default': 'esp32s3',
                    },
                    {
                        'names': ['-d', '--gdb'],
                        'help': ('Wait for gdb to connect. '
                                 'Use this option to run "idf.py qemu --gdb monitor" in one terminal window '
                                 'and "idf.py gdb" in another. The program will start running when gdb connects.'),
                        'is_flag': True,
                        'default': False,
                    },
                    {
                        'names': ['-g', '--graphics'],
                        'help': 'Enable graphical window',
                        'is_flag': True,
                        'default': False,
                    }
                ]
            }
        }
    }
    return qemu_actions