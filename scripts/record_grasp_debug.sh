#!/usr/bin/env bash
set -euo pipefail

source "$(dirname "$0")/ros_env.sh"

STAMP="$(date +%Y%m%d_%H%M%S)"
DEFAULT_OUTDIR="/tmp/grasp_debug_${STAMP}"
OUTDIR="${1:-$DEFAULT_OUTDIR}"

if [[ "${EUID:-$(id -u)}" -eq 0 ]]; then
  echo "Do not run this recorder with sudo."
  echo "Run it from the same non-root ROS terminal that sees the active graph."
  exit 2
fi

if ! mkdir -p "$OUTDIR" 2>/dev/null; then
  echo "Cannot create output directory: $OUTDIR"
  echo "Falling back to: $DEFAULT_OUTDIR"
  OUTDIR="$DEFAULT_OUTDIR"
  mkdir -p "$OUTDIR"
fi

TOPICS=(
  /tf
  /tf_static
  /joint_states
  /jaka_driver/tool_position
  /heightmap_node/heightmap/color
  /heightmap_node/heightmap/height
  /heightmap_node/heightmap/mask
  /grasp_inference_node/grasp_pose_base
  /grasp_inference_node/grasp_pose_gripper
  /grasp_inference_node/object_center_base
  /gripper_exec_node/debug/input_object_center
  /gripper_exec_node/debug/input_grasp_pose
  /gripper_exec_node/debug/current_tcp
  /gripper_exec_node/debug/current_tip
  /gripper_exec_node/debug/target_tip
  /gripper_exec_node/debug/target_tcp
)

SHOT_TOPICS=(
  /jaka_driver/tool_position
  /grasp_inference_node/grasp_pose_base
  /grasp_inference_node/grasp_pose_gripper
  /grasp_inference_node/object_center_base
)

CAMERA_TOPICS=(
  /camera/camera/depth/color/points
  /camera/camera/color/image_raw
  /camera/camera/aligned_depth_to_color/image_rect_raw
  /camera/camera/aligned_depth_to_color/camera_info
)

echo "Recording grasp debug bundle into: $OUTDIR"
echo "Press Ctrl+C to stop recording."

{
  echo "timestamp=$STAMP"
  echo "user=$(id -un)"
  echo "uid=$(id -u)"
  echo "pwd=$(pwd)"
  echo "hostname=$(hostname)"
  echo "ros_ws=${ROS_WS:-}"
  echo "ROS_DOMAIN_ID=${ROS_DOMAIN_ID:-}"
  echo "RMW_IMPLEMENTATION=${RMW_IMPLEMENTATION:-}"
  echo "ROS_LOCALHOST_ONLY=${ROS_LOCALHOST_ONLY:-}"
  echo "AMENT_PREFIX_PATH=${AMENT_PREFIX_PATH:-}"
} > "$OUTDIR/env.txt"

ros2 topic list > "$OUTDIR/topic_list.txt" 2>&1 || true
ros2 topic list -t > "$OUTDIR/topic_list_typed.txt" 2>&1 || true
ros2 node list > "$OUTDIR/node_list.txt" 2>&1 || true
ros2 service list > "$OUTDIR/service_list.txt" 2>&1 || true
ros2 param list > "$OUTDIR/param_list.txt" 2>&1 || true

if [[ ! -s "$OUTDIR/topic_list.txt" ]] || [[ ! -s "$OUTDIR/node_list.txt" ]]; then
  echo "ROS graph is not visible from this terminal."
  echo "Check:"
  echo "  source ./scripts/ros_env.sh"
  echo "  ros2 topic list"
  echo "  ros2 node list"
  echo "Environment snapshot saved to: $OUTDIR/env.txt"
  exit 2
fi

for node in /heightmap_node /grasp_inference_node /gripper_exec_node; do
  ros2 param dump "$node" > "$OUTDIR/$(basename "$node")_params.yaml" 2>&1 || true
done

for topic in "${TOPICS[@]}" "${CAMERA_TOPICS[@]}"; do
  safe_name="$(echo "$topic" | sed 's#^/##; s#/#__#g')"
  ros2 topic info "$topic" > "$OUTDIR/topic_info__${safe_name}.txt" 2>&1 || true
done

for topic in "${SHOT_TOPICS[@]}"; do
  safe_name="$(echo "$topic" | sed 's#^/##; s#/#__#g')"
  timeout 5s ros2 topic echo --once "$topic" > "$OUTDIR/topic_echo_once__${safe_name}.txt" 2>&1 || true
done

for tf_pair in \
  "base_link camera_link" \
  "base_link tool0" \
  "base_link jaka_tcp" \
  "base_link gripper_tip" \
  "jaka_tcp camera_link" \
  "camera_link gripper_tip" \
  "camera_link tool0"
do
  parent="$(echo "$tf_pair" | awk '{print $1}')"
  child="$(echo "$tf_pair" | awk '{print $2}')"
  timeout 3s ros2 run tf2_ros tf2_echo "$parent" "$child" \
    > "$OUTDIR/tf__${parent}__${child}.txt" 2>&1 || true
done

cat > "$OUTDIR/README.txt" <<EOF
How to use this debug bundle:

1. This folder contains:
   - bag/: recorded ROS topics
   - *_params.yaml: node parameters
   - tf__*.txt: TF snapshots
   - env.txt: ROS environment seen by the recorder
   - topic_list/topic_list_typed/node_list/service_list: runtime topology
   - topic_echo_once__*.txt: one-shot values for the key motion topics

2. To inspect locally:
   ros2 bag info "$OUTDIR/bag"
   ros2 bag play "$OUTDIR/bag"

3. The most important recorded topics are:
   /grasp_inference_node/grasp_pose_base
   /grasp_inference_node/grasp_pose_gripper
   /grasp_inference_node/object_center_base
   /gripper_exec_node/debug/input_object_center
   /gripper_exec_node/debug/input_grasp_pose
   /gripper_exec_node/debug/current_tcp
   /gripper_exec_node/debug/current_tip
   /gripper_exec_node/debug/target_tip
   /gripper_exec_node/debug/target_tcp
   /jaka_driver/tool_position
EOF

trap 'echo "Recording stopped. Inspect with: ros2 bag info \"$OUTDIR/bag\""' EXIT

ros2 bag record -o "$OUTDIR/bag" "${TOPICS[@]}"
