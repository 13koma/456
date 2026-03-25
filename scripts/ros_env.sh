#!/usr/bin/env bash
set -eo pipefail

export ROS_WS="${ROS_WS:-/workspaces/grasp_jaka_ws}"

set +u
source /opt/ros/humble/setup.bash
if [ -f "${ROS_WS}/install/setup.bash" ]; then
  source "${ROS_WS}/install/setup.bash"
fi
set -u 2>/dev/null || true
