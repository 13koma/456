#!/usr/bin/env bash
set -eo pipefail

SESSION="grasp-dev"
ROOT="${ROS_WS:-/workspaces/grasp_jaka_ws}"

if tmux has-session -t "$SESSION" 2>/dev/null; then
  exec tmux attach -t "$SESSION"
fi

tmux new-session -d -s "$SESSION" -n shell  "bash -lc 'cd ${ROOT}; bash'"
tmux new-window  -t "$SESSION" -n robot   "bash -lc 'cd ${ROOT}; ./scripts/launch_robot.sh; bash'"
tmux new-window  -t "$SESSION" -n tf      "bash -lc 'cd ${ROOT}; ./scripts/launch_tf.sh; bash'"
tmux new-window  -t "$SESSION" -n gripper "bash -lc 'cd ${ROOT}; ./scripts/launch_gripper.sh; bash'"
tmux new-window  -t "$SESSION" -n camera  "bash -lc 'cd ${ROOT}; ./scripts/launch_camera.sh; bash'"
tmux new-window  -t "$SESSION" -n grasp   "bash -lc 'cd ${ROOT}; ./scripts/launch_grasp.sh; bash'"
tmux new-window  -t "$SESSION" -n exec    "bash -lc 'cd ${ROOT}; source ./scripts/ros_env.sh; bash'"
tmux new-window  -t "$SESSION" -n debug   "bash -lc 'cd ${ROOT}; source ./scripts/ros_env.sh; ros2 topic list; bash'"

tmux select-window -t "$SESSION":shell
exec tmux attach -t "$SESSION"
