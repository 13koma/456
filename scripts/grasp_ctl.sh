#!/usr/bin/env bash
set -euo pipefail

ROOT="$(cd "$(dirname "$0")/.." && pwd)"
source "${ROOT}/scripts/ros_env.sh"

SERVICE_TYPE="std_srvs/srv/Trigger"
EXEC_NODE="/gripper_exec_node"
TMUX_SESSION="${TMUX_SESSION_NAME:-grasp-dev}"

call_trigger() {
  local service_name="$1"
  ros2 service call "${service_name}" "${SERVICE_TYPE}" "{}"
}

print_health() {
  local missing=0
  local required_nodes=(
    "/heightmap_node"
    "/grasp_inference_node"
    "/gripper_exec_node"
    "/dh_gripper_node"
  )

  local current_nodes
  current_nodes="$(ros2 node list 2>/dev/null || true)"

  echo "Required nodes:"
  for node in "${required_nodes[@]}"; do
    if grep -qx "${node}" <<<"${current_nodes}"; then
      echo "  [ok] ${node}"
    else
      echo "  [missing] ${node}"
      missing=1
    fi
  done
  echo
  echo "Executor status:"
  call_trigger "${EXEC_NODE}/status" || true

  return "${missing}"
}

restart_window() {
  local window="$1"
  local cmd=""
  case "${window}" in
    robot)   cmd="cd ${ROOT}; ./scripts/launch_robot.sh; bash" ;;
    tf)      cmd="cd ${ROOT}; ./scripts/launch_tf.sh; bash" ;;
    gripper) cmd="cd ${ROOT}; ./scripts/launch_gripper.sh; bash" ;;
    camera)  cmd="cd ${ROOT}; ./scripts/launch_camera.sh; bash" ;;
    grasp)   cmd="cd ${ROOT}; ./scripts/launch_grasp.sh; bash" ;;
    debug)   cmd="cd ${ROOT}; source ./scripts/ros_env.sh; ros2 topic list; bash" ;;
    exec)    cmd="cd ${ROOT}; source ./scripts/ros_env.sh; bash" ;;
    menu)    cmd="cd ${ROOT}; bash ./scripts/grasp_menu.sh; bash" ;;
    *)
      echo "Unknown window: ${window}" >&2
      return 1
      ;;
  esac

  tmux respawn-window -k -t "${TMUX_SESSION}:${window}" "bash -lc '${cmd}'" >/dev/null 2>&1
  echo "Restarted tmux window: ${window}"
}

usage() {
  cat <<'EOF'
Usage: grasp_ctl.sh <command>

Commands:
  status          Print executor status
  start           Trigger one grasp cycle
  start-dry       Trigger one dry-run grasp cycle (debug/visualization only)
  home            Send robot home
  open            Open gripper
  close           Close gripper
  reset           Reset local executor state
  nodes           List ROS nodes
  health          Check required nodes and executor status
  restart <name>  Respawn a tmux window: robot|tf|gripper|camera|grasp|exec|debug|menu
EOF
}

cmd="${1:-}"
case "${cmd}" in
  status)  call_trigger "${EXEC_NODE}/status" ;;
  start)   call_trigger "${EXEC_NODE}/start" ;;
  start-dry) call_trigger "${EXEC_NODE}/start_dry_run" ;;
  home)    call_trigger "${EXEC_NODE}/go_home" ;;
  open)    call_trigger "${EXEC_NODE}/open_gripper" ;;
  close)   call_trigger "${EXEC_NODE}/close_gripper" ;;
  reset)   call_trigger "${EXEC_NODE}/reset" ;;
  nodes)   ros2 node list ;;
  health)  print_health ;;
  restart)
    restart_window "${2:-}"
    ;;
  ""|-h|--help|help)
    usage
    ;;
  *)
    echo "Unknown command: ${cmd}" >&2
    usage
    exit 1
    ;;
esac
