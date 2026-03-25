#!/usr/bin/env bash
set -eo pipefail
source "$(dirname "$0")/ros_env.sh"

exec ros2 launch realsense2_camera rs_launch.py \
  camera_namespace:=camera \
  camera_name:=camera \
  pointcloud.enable:=true \
  pointcloud.ordered_pc:=true \
  align_depth.enable:=true
