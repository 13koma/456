#!/usr/bin/env bash
set -eo pipefail
source "$(dirname "$0")/ros_env.sh"
sudo chmod 666 "${GRIPPER_PORT}" || true
exec ros2 launch dh_gripper_driver gripper.launch.py port:=${GRIPPER_PORT} auto_init:=true default_force:=50
