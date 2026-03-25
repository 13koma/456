#!/usr/bin/env bash
set -eo pipefail
source "$(dirname "$0")/ros_env.sh"
exec ros2 launch grasp_inference_pkg grasp_inference_jaka.launch.py
