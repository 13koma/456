# Jetson Runtime

This project has a separate headless Docker runtime for Jetson Orin devices.

## Assumptions

- Jetson Orin Nano / Orin NX class device.
- JetPack 6.x with Ubuntu 22.04, so ROS 2 Humble apt packages are available.
- NVIDIA container runtime is installed and Docker can access the Jetson GPU.
- RViz/RQT are run from a laptop on the same ROS network, not inside the Jetson runtime container.

## Files

- `Dockerfile.jetson` - Jetson headless runtime image.
- `compose.jetson.yaml` - Jetson runtime Compose service.
- `requirements.jetson.txt` - Python dependencies that do not replace the Jetson PyTorch/OpenCV stack.

## Base Image

The default base image is:

```bash
nvcr.io/nvidia/l4t-pytorch:r36.2.0-pth2.1-py3
```

This must match the JetPack/L4T version installed on the Jetson. Override it with:

```bash
export JETSON_BASE_IMAGE=<your-compatible-l4t-pytorch-image>
```

## Build On Jetson

```bash
cd ~/grasp_dev_env_v2
docker compose -f compose.jetson.yaml build
```

## Start Runtime

```bash
docker compose -f compose.jetson.yaml up -d
```

## Enter Container

```bash
docker exec -it grasp-jetson bash
```

Inside the container:

```bash
cd /workspaces/grasp_jaka_ws
source /opt/ros/humble/setup.bash
source install/setup.bash
```

## Build ROS Workspace

```bash
cd /workspaces/grasp_jaka_ws
colcon build --symlink-install
source install/setup.bash
```

## Start Pipeline

The container starts `scripts/container_start.sh`, which launches the tmux layout.
If needed, start it manually:

```bash
./scripts/tmux-up.sh
```

Use the control menu:

```bash
bash ./scripts/grasp_menu.sh
```

Or direct commands:

```bash
bash ./scripts/grasp_ctl.sh health
bash ./scripts/grasp_ctl.sh status
bash ./scripts/grasp_ctl.sh start-dry
```

## Smoke Tests

Check CUDA/PyTorch:

```bash
python3 - <<'PY'
import torch
print(torch.__version__)
print(torch.cuda.is_available())
print(torch.cuda.get_device_name(0) if torch.cuda.is_available() else "no cuda")
PY
```

Check YOLO import:

```bash
python3 - <<'PY'
from ultralytics import YOLO
print("ultralytics ok")
PY
```

Check camera topics:

```bash
ros2 topic list | grep camera
ros2 topic hz /camera/camera/depth/color/points
```

Check robot network from the container:

```bash
ping -c 3 ${JAKA_ROBOT_IP:-10.5.5.100}
```

## Notes

- Do not install CPU-only `torch` in the Jetson image.
- `ultralytics` is installed with `--no-deps` so it does not replace Jetson-compatible PyTorch/OpenCV packages.
- Do not rely on local GUI inside the container.
- Keep `network_mode: host` for ROS 2 discovery and robot communication.
- Keep `/dev:/dev` and `privileged: true` while validating RealSense and gripper access.
