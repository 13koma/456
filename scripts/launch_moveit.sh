#!/usr/bin/env bash
set -euo pipefail
source /opt/ros/humble/setup.bash
if [ -f "$ROS_WS/install/setup.bash" ]; then
  source "$ROS_WS/install/setup.bash"
fi
exec ros2 launch jaka_planner moveit_server.launch.py ip:=${JAKA_ROBOT_IP} model:=${JAKA_ROBOT_MODEL}
