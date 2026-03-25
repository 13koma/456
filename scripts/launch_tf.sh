#!/usr/bin/env bash
set -eo pipefail
source "$(dirname "$0")/ros_env.sh"
exec ros2 launch jaka_zu12_tf_tools jaka_zu12_rsp.launch.py