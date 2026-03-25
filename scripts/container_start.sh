#!/usr/bin/env bash
set -e

cd /workspaces/grasp_jaka_ws

echo "[container_start] pwd=$(pwd)"
echo "[container_start] starting tmux-up..."
./scripts/tmux-up.sh || true

echo "[container_start] tmux sessions:"
tmux ls || true

exec tail -f /dev/null
