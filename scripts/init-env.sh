#!/usr/bin/env bash
set -euo pipefail

cp -n .env.example .env || true
python3 - <<'PY'
from pathlib import Path
import os

p = Path('.env')
vals = {}
if p.exists():
    for raw in p.read_text().splitlines():
        line = raw.strip()
        if not line or line.startswith('#') or '=' not in line:
            continue
        k, v = line.split('=', 1)
        vals[k] = v

def default(key, value):
    vals[key] = os.environ.get(key, vals.get(key, value))

default('LOCAL_USER', vals.get('LOCAL_USER', 'dev'))
default('LOCAL_UID', str(os.getuid()))
default('LOCAL_GID', str(os.getgid()))
default('DISPLAY', os.environ.get('DISPLAY', ':0'))
default('ROS_DOMAIN_ID', '21')
default('ROS_LOCALHOST_ONLY', '0')
default('JAKA_ROBOT_IP', '10.5.5.100')
default('JAKA_ROBOT_MODEL', 'zu12')
default('GRIPPER_PORT', '/dev/ttyUSB0')
default('CAMERA_NAMESPACE', '/camera/camera')
default('LIBGL_ALWAYS_SOFTWARE', '1')
default('NVIDIA_VISIBLE_DEVICES', 'all')
default('NVIDIA_DRIVER_CAPABILITIES', 'all')

order = [
    'LOCAL_USER', 'LOCAL_UID', 'LOCAL_GID', 'DISPLAY',
    'ROS_DOMAIN_ID', 'ROS_LOCALHOST_ONLY',
    'JAKA_ROBOT_IP', 'JAKA_ROBOT_MODEL', 'GRIPPER_PORT', 'CAMERA_NAMESPACE',
    'LIBGL_ALWAYS_SOFTWARE',
    'NVIDIA_VISIBLE_DEVICES', 'NVIDIA_DRIVER_CAPABILITIES',
]

p.write_text(''.join(f'{k}={vals[k]}\n' for k in order))
print('.env updated')
PY
