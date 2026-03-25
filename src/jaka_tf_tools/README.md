# JAKA TF tools

Минимальный bridge для этапа perception -> base TF.

Что делает:
- публикует TF `base_link -> jaka_tcp` из `/jaka_driver/tool_position`
- публикует статический TF `jaka_tcp -> camera_link`
- репаблишит `/jaka_driver/joint_position -> /joint_states`

## Установка
Скопировать пакет `jaka_tf_tools` в `src/` workspace JAKA и собрать:

```bash
colcon build --packages-select jaka_tf_tools
source install/setup.bash
```

## Настройка
Отредактировать `config/jaka_tf_tools.yaml`:
- `static_camera_tf.ros__parameters.xyz` — смещение камеры относительно TCP, метры
- `static_camera_tf.ros__parameters.rpy` — ориентация камеры относительно TCP, радианы

## Запуск
```bash
ros2 launch jaka_tf_tools jaka_tf_minimal.launch.py
```

## Проверка
```bash
ros2 run tf2_ros tf2_echo base_link camera_link
ros2 run tf2_ros tf2_echo base_link jaka_tcp
ros2 topic echo /joint_states --once
```
