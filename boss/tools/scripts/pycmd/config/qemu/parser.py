
import json
import os
from typing import Any

from pycmd.utils import warn

cfg_json = {
    "name": "qemu",
    "version": "0.0.0",
    "target": ""
}

def parser_config_qemu(path: str) -> Any:
    info = ""
    cfg = os.path.join(path, 'config.json')
    try:
        with open(cfg, 'r', encoding='utf-8') as fd:
            info = json.load(fd)
    except FileNotFoundError:
        warn(f'{cfg} not exists.')
        return

    # update cfg cache
    cfg_json["target"] = info
    cfg = os.path.join(os.path.dirname(path), 'config.json')
    with open(cfg, 'w', encoding='utf-8') as fd:
        json.dump(cfg_json, fd, ensure_ascii=False, indent=4)
    return cfg_json
