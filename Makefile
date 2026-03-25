SHELL := /bin/bash
SERVICE := grasp-dev
COMPOSE_BASE := docker compose -f compose.yaml
COMPOSE_GPU := docker compose -f compose.yaml -f compose.gpu.yaml

.PHONY: init build build-gpu up up-gpu down restart bash tmux doctor deps colcon clean purge robot moveit gripper grasp camera config config-gpu

init:
	@./scripts/init-env.sh

build:
	$(COMPOSE_BASE) build

build-gpu:
	$(COMPOSE_GPU) build

up:
	$(COMPOSE_BASE) up -d

up-gpu:
	$(COMPOSE_GPU) up -d

down:
	$(COMPOSE_GPU) down

restart:
	$(COMPOSE_BASE) restart

bash:
	$(COMPOSE_BASE) exec $(SERVICE) bash

tmux:
	$(COMPOSE_BASE) exec $(SERVICE) bash -lc './scripts/tmux-dev.sh'

doctor:
	$(COMPOSE_BASE) exec $(SERVICE) bash -lc './scripts/doctor.sh'

deps:
	docker compose -f compose.yaml exec --user root grasp-dev bash -lc 'mkdir -p /home/dev/.ros && chown -R dev:dev /home/dev/.ros'
	docker compose -f compose.yaml exec grasp-dev bash -lc 'source /opt/ros/humble/setup.bash && cd $$ROS_WS && rosdep update && sudo rosdep install --from-paths src --ignore-src -r -y'

colcon:
	$(COMPOSE_BASE) exec $(SERVICE) bash -lc 'source /opt/ros/humble/setup.bash && cd $$ROS_WS && colcon build --symlink-install'

clean:
	$(COMPOSE_BASE) exec $(SERVICE) bash -lc 'cd $$ROS_WS && rm -rf build install log'

purge:
	$(COMPOSE_GPU) down -v --remove-orphans

robot:
	$(COMPOSE_BASE) exec $(SERVICE) bash -lc './scripts/launch_robot.sh'

moveit:
	$(COMPOSE_BASE) exec $(SERVICE) bash -lc './scripts/launch_moveit.sh'

gripper:
	$(COMPOSE_BASE) exec $(SERVICE) bash -lc './scripts/launch_gripper.sh'

grasp:
	$(COMPOSE_BASE) exec $(SERVICE) bash -lc './scripts/launch_grasp.sh'

camera:
	$(COMPOSE_BASE) exec $(SERVICE) bash -lc './scripts/launch_camera.sh'

config:
	$(COMPOSE_BASE) config

config-gpu:
	$(COMPOSE_GPU) config
