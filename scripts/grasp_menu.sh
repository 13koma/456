#!/usr/bin/env bash
set -euo pipefail

ROOT="$(cd "$(dirname "$0")/.." && pwd)"
CTL="${ROOT}/scripts/grasp_ctl.sh"

show_output_box() {
  local title="$1"
  local output="$2"
  local tmp
  tmp="$(mktemp)"
  printf '%s\n' "${output}" > "${tmp}"
  if command -v whiptail >/dev/null 2>&1; then
    whiptail --title "${title}" --scrolltext --textbox "${tmp}" 24 100
  else
    clear
    cat "${tmp}"
    printf '\nPress Enter to continue...'
    read -r _ </dev/tty
  fi
  rm -f "${tmp}"
}

run_and_pause() {
  local title="Grasp Control"
  local output
  output="$(bash "${CTL}" "$@" 2>&1 || true)"
  case "${1:-}" in
    health) title="Stack Health" ;;
    status) title="Executor Status" ;;
    start) title="Run Grasp Cycle" ;;
    start-dry) title="Run Grasp Dry-Run" ;;
    home) title="Go Home" ;;
    open) title="Open Gripper" ;;
    close) title="Close Gripper" ;;
    reset) title="Reset Executor State" ;;
    restart) title="Restart ${2:-window}" ;;
    nodes) title="ROS Nodes" ;;
  esac
  show_output_box "${title}" "${output}"
}

menu_prompt() {
  if command -v gum >/dev/null 2>&1; then
    gum choose \
      "1  Stack health" \
      "2  Executor status" \
      "3  Run grasp cycle" \
      "4  Go home" \
      "5  Open gripper" \
      "6  Close gripper" \
      "7  Reset executor state" \
      "8  Restart grasp window" \
      "9  Restart gripper window" \
      "10 Restart tf window" \
      "11 List ROS nodes" \
      "q  Quit menu" | awk '{print $1}'
  elif command -v whiptail >/dev/null 2>&1; then
    whiptail \
      --title "Grasp Control" \
      --menu "Choose action" 22 78 12 \
      "1" "Stack health" \
      "2" "Executor status" \
      "3" "Run grasp cycle" \
      "4" "Run grasp dry-run" \
      "5" "Go home" \
      "6" "Open gripper" \
      "7" "Close gripper" \
      "8" "Reset executor state" \
      "9" "Restart grasp window" \
      "10" "Restart gripper window" \
      "11" "Restart tf window" \
      "12" "List ROS nodes" \
      "q" "Quit menu" \
      3>&1 1>&2 2>&3
  else
    {
      echo "Grasp Control"
      echo "1) Stack health"
      echo "2) Executor status"
      echo "3) Run grasp cycle"
      echo "4) Run grasp dry-run"
      echo "5) Go home"
      echo "6) Open gripper"
      echo "7) Close gripper"
      echo "8) Reset executor state"
      echo "9) Restart grasp window"
      echo "10) Restart gripper window"
      echo "11) Restart tf window"
      echo "12) List ROS nodes"
      echo "q) Quit menu"
      printf "> "
    } >/dev/tty
    read -r choice </dev/tty
    echo "${choice}"
  fi
}

while true; do
  choice="$(menu_prompt || true)"
  case "${choice}" in
    1) run_and_pause health ;;
    2) run_and_pause status ;;
    3) run_and_pause start ;;
    4) run_and_pause start-dry ;;
    5) run_and_pause home ;;
    6) run_and_pause open ;;
    7) run_and_pause close ;;
    8) run_and_pause reset ;;
    9) run_and_pause restart grasp ;;
    10) run_and_pause restart gripper ;;
    11) run_and_pause restart tf ;;
    12) run_and_pause nodes ;;
    q|Q) exit 0 ;;
    *) ;;
  esac
done
