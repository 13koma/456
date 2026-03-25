# grasp-jaka Docker dev environment

Это базовое **CPU-safe** окружение для ноутбука без NVIDIA и отдельный **GPU override** для сервера.

## Что важно

- `compose.yaml` — обычный режим, без обязательной NVIDIA-зависимости.
- `compose.gpu.yaml` — добавляет `gpus: all` для сервера с NVIDIA.
- `.env.example` — скрытый файл. Его видно через `ls -a`.

## Ожидаемая структура workspace

```text
.
├── compose.yaml
├── compose.gpu.yaml
├── Dockerfile
├── Makefile
├── src/
│   ├── jaka_driver/
│   ├── jaka_msgs/
│   ├── jaka_planner/
│   ├── jaka_rl_*/
│   ├── grasp_inference_pkg/
│   └── dh_gripper_driver/
└── scripts/
```

## Быстрый старт на ноутбуке без NVIDIA

```bash
ls -a
cp .env.example .env
make init
make build
make up
make deps
make colcon
make doctor
make tmux
```

## Быстрый старт на сервере с NVIDIA

Перед этим на хосте должны быть установлены драйвер NVIDIA и NVIDIA Container Toolkit.

```bash
cp .env.example .env
make init
make build-gpu
make up-gpu
make deps
make colcon
make doctor
```

## Ежедневный workflow

```bash
make up
make bash
make colcon
make robot
make gripper
make camera
make grasp
```

Для сервера вместо `build/up` использовать `build-gpu/up-gpu`.

## tmux

```bash
make tmux
```

Это один dev-контейнер. Внутри него удобно держать несколько процессов через tmux: `robot / gripper / camera / grasp / debug`.

## Замечание по 5090

По умолчанию GPU override пробрасывает все доступные GPU. Если захочется ограничить видимость, укажи в `.env`, например:

```env
NVIDIA_VISIBLE_DEVICES=0,1
```
