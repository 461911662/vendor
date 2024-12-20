
import json
import os
from typing import Any

from pycmd.utils import warn
from .qemu.parser import parser_config_qemu

cfg_json= {
    "version": '0.0.0',
    "type": [
    ],
}

TYPE_QEMU='qemu'

supported_types = [
    TYPE_QEMU,
]

def is_supported_config_types(type:str) -> bool:
    return type if type in supported_types else ''

def get_config_type(type: str) -> Any:
    for d in cfg_json['type']:
        if d['name'] == type:
            return d
    return None

def parser_config(type: str, path: str) -> Any:
    global cfg_json
    info = ""
    cfg = os.path.join(os.path.dirname(os.path.abspath(__file__)), 'config.json')
    try:
        with open(cfg, 'r', encoding='utf-8') as fd:
            cfg_json = json.load(fd) # here a bug when config.json is error
    except Exception:
        warn(f'{cfg} not exists, create it.')
        with open(cfg, 'w', encoding='utf-8') as fd:
            json.dump(cfg_json, fd, ensure_ascii=False, indent=4)

    if type == TYPE_QEMU:
        info = parser_config_qemu(path)
    else:
        pass

    types = []
    for dict in cfg_json['type']:
        if dict['name'] != info['name']:
            types.append(dict)
    types.append(info)
    cfg_json['type'] = types

    # update cfg cache
    with open(cfg, 'w', encoding='utf-8') as fd:
        json.dump(cfg_json, fd, ensure_ascii=False, indent=4)
    return cfg_json
