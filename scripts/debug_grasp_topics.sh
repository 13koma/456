#!/usr/bin/env bash
set -eo pipefail

source "$(dirname "$0")/ros_env.sh"

cat <<'EOF'
Useful debug commands for the active JAKA grasp runtime:

1) Perception outputs
  ros2 topic echo /grasp_inference_node/grasp_pose_base --once
  ros2 topic echo /grasp_inference_node/grasp_pose_gripper --once
  ros2 topic echo /grasp_inference_node/object_center_base --once

2) Executor inputs and derived motion targets
  ros2 topic echo /gripper_exec_node/debug/input_object_center --once
  ros2 topic echo /gripper_exec_node/debug/input_grasp_pose --once
  ros2 topic echo /gripper_exec_node/debug/current_tcp --once
  ros2 topic echo /gripper_exec_node/debug/current_tip --once
  ros2 topic echo /gripper_exec_node/debug/target_tip --once
  ros2 topic echo /gripper_exec_node/debug/target_tcp --once

3) Live controller pose
  ros2 topic echo /jaka_driver/tool_position --once

4) TF checks
  ros2 run tf2_ros tf2_echo base_link camera_link
  ros2 run tf2_ros tf2_echo base_link tool0
  ros2 run tf2_ros tf2_echo base_link jaka_tcp
  ros2 run tf2_ros tf2_echo base_link gripper_tip

5) Params that currently matter most
  ros2 param get /gripper_exec_node tcp_to_tip_offset_m
  ros2 param get /gripper_exec_node pregrasp_settle_distance
  ros2 param get /grasp_inference_node grasp_depth_offset
  ros2 param get /heightmap_node plane_min
  ros2 param get /heightmap_node plane_max
EOF
