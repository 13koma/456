#!/usr/bin/env bash
set -euo pipefail

export ROS_DISTRO="${ROS_DISTRO:-jazzy}"
source "/opt/ros/${ROS_DISTRO}/setup.bash"
if [ -f "$ROS_WS/install/setup.bash" ]; then
  source "$ROS_WS/install/setup.bash"
fi

printf '\n[1/7] Python imports\n'
python3 - <<'PY'
mods = [
    'torch', 'torchvision', 'cv2', 'numpy', 'ultralytics',
    'segmentation_models_pytorch', 'pymodbus', 'rclpy'
]
for m in mods:
    try:
        __import__(m)
        print(f'OK  {m}')
    except Exception as e:
        print(f'ERR {m}: {e}')
PY

printf '\n[2/7] ROS packages\n'
for pkg in jaka_driver jaka_msgs jaka_planner grasp_inference_pkg dh_gripper_driver; do
  if ros2 pkg prefix "$pkg" >/dev/null 2>&1; then
    echo "OK  $pkg"
  else
    echo "MISS $pkg"
  fi
done

printf '\n[3/7] Robot reachability\n'
ping -c 1 -W 1 "${JAKA_ROBOT_IP}" >/dev/null 2>&1 && echo "OK  ping ${JAKA_ROBOT_IP}" || echo "WARN robot ${JAKA_ROBOT_IP} is not reachable"

printf '\n[4/7] Gripper port\n'
if [ -e "${GRIPPER_PORT}" ]; then
  ls -lah "${GRIPPER_PORT}"
else
  echo "WARN ${GRIPPER_PORT} not found"
fi

printf '\n[5/7] Camera topics snapshot\n'
ros2 topic list 2>/dev/null | grep -E 'camera|image|depth|point' || true

printf '\n[6/7] GPU\n'
if command -v nvidia-smi >/dev/null 2>&1; then
  nvidia-smi || true
else
  echo 'nvidia-smi not found'
fi
python3 - <<'PY'
try:
    import torch
    print('CUDA available:', torch.cuda.is_available())
    if torch.cuda.is_available():
        print('GPU:', torch.cuda.get_device_name(0))
except Exception as e:
    print('torch CUDA check failed:', e)
PY

printf '\n[7/7] Workspace\n'
echo "ROS_WS=$ROS_WS"
echo "PWD=$(pwd)"
