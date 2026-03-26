# JAKA Zu12 TF integration bundle

This bundle adds a clean TF chain:

base_link -> Link_0 -> ... -> Link_6 -> tool0 -> jaka_tcp -> camera_link

## Dependency

You also need the vendor package `jaka_description` from `jaka_ros2-main.zip` in your workspace,
because meshes are referenced as `package://jaka_description/...`.

## Minimal integration steps

1. Copy `jaka_description` into `$ROS_WS/src/` if it is not already there.
2. Copy `jaka_zu12_tf_tools/` from this bundle into `$ROS_WS/src/`.
3. Edit `config/jaka_zu12_tf.yaml` and set camera offsets.
4. Build:
   ```bash
   colcon build --symlink-install --packages-select jaka_description jaka_zu12_tf_tools
   source install/setup.bash
   ```
5. Launch TF stack:
   ```bash
   ros2 launch jaka_zu12_tf_tools jaka_zu12_rsp.launch.py
   ```

## What to disable from old scheme

After this launch is up, disable old TF publishers for:
- `base_link -> jaka_tcp` from `tcp_tf_broadcaster.py`
- `jaka_tcp -> camera_link` from `static_camera_tf.py`

Otherwise you will get duplicate / conflicting TF.

## Recommended validation

```bash
ros2 topic echo /joint_states --once
ros2 run tf2_ros tf2_echo base_link tool0
ros2 run tf2_ros tf2_echo base_link camera_link
ros2 run tf2_tools view_frames
```

## Notes

- `tool0` is zero-offset from `Link_6` by default. Keep it that way first.
- `jaka_tcp` is kept as a legacy alias frame for compatibility.
- Start by tuning only `camera_xyz` and `camera_rpy`.
