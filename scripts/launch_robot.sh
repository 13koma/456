#!/usr/bin/env bash
set -eo pipefail
source "$(dirname "$0")/ros_env.sh"
exec ros2 launch jaka_driver robot_start.launch.py ip:=${JAKA_ROBOT_IP}
