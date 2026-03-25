#!/usr/bin/env python3
"""
AG-95 Gripper CLI Test Tool
============================

Standalone test script for verifying gripper communication.
No ROS2 required - uses Modbus RTU directly.

Usage:
    python3 test_gripper_cli.py                    # Interactive mode
    python3 test_gripper_cli.py --port /dev/ttyUSB0 --init
    python3 test_gripper_cli.py --open
    python3 test_gripper_cli.py --close --force 80
    python3 test_gripper_cli.py --position 500
    python3 test_gripper_cli.py --status
"""

import sys
import os
import argparse
import time

# Add parent to path for imports
sys.path.insert(0, os.path.join(os.path.dirname(__file__), '..'))

from dh_gripper_driver.ag95_modbus import AG95ModbusDriver, GripperState, InitState


def print_status(driver: AG95ModbusDriver):
    """Print full gripper status."""
    status = driver.get_status()
    if status is None:
        print("❌ Failed to read status")
        return

    print("\n╔═══════════════════════════════════════╗")
    print("║        AG-95 Gripper Status           ║")
    print("╠═══════════════════════════════════════╣")
    print(f"║  Initialized:  {'✅ Yes' if status.is_initialized else '❌ No':>20s} ║")
    print(f"║  State:        {status.gripper_state.name:>20s} ║")
    print(f"║  Position:     {status.current_position:>16d} ‰  ║")
    print(f"║  Position mm:  {status.current_position_mm:>17.1f} mm ║")
    print(f"║  Force:        {status.force_setting:>17d} %  ║")
    print(f"║  Target:       {status.position_setting:>16d} ‰  ║")
    print(f"║  Moving:       {'✅ Yes' if status.is_moving else '⬜ No':>20s} ║")
    print(f"║  Object:       {'🟢 Caught' if status.object_caught else '⬜ None':>20s} ║")
    print("╚═══════════════════════════════════════╝\n")


def interactive_mode(driver: AG95ModbusDriver):
    """Interactive control menu."""
    print("\n🤖 AG-95 Interactive Control")
    print("=" * 40)

    while True:
        print("\nCommands:")
        print("  i  - Initialize (full)")
        print("  o  - Open (fully)")
        print("  c  - Close (fully)")
        print("  p  - Set position (0-1000)")
        print("  f  - Set force (20-100)")
        print("  m  - Move to (position + force)")
        print("  s  - Read status")
        print("  q  - Quit")

        try:
            cmd = input("\n> ").strip().lower()
        except (EOFError, KeyboardInterrupt):
            break

        if cmd == 'q':
            break
        elif cmd == 'i':
            print("Initializing (full)...")
            success = driver.initialize(full=True, timeout=15.0)
            print("✅ Done" if success else "❌ Failed")
        elif cmd == 'o':
            force = int(input("Force % [50]: ").strip() or "50")
            driver.open(force)
            print("Opening...")
        elif cmd == 'c':
            force = int(input("Force % [50]: ").strip() or "50")
            driver.close(force)
            print("Closing...")
        elif cmd == 'p':
            pos = int(input("Position (0-1000): ").strip())
            driver.set_position(pos)
            print(f"Moving to {pos}‰...")
        elif cmd == 'f':
            force = int(input("Force (20-100): ").strip())
            driver.set_force(force)
            print(f"Force set to {force}%")
        elif cmd == 'm':
            pos = int(input("Position (0-1000): ").strip())
            force = int(input("Force (20-100) [50]: ").strip() or "50")
            print(f"Moving to {pos}‰ at {force}%...")
            driver.move_to(pos, force, wait=True, timeout=5.0)
            print_status(driver)
        elif cmd == 's':
            print_status(driver)
        else:
            print("Unknown command")


def detect_serial_ports():
    """List available serial ports."""
    import glob
    patterns = ['/dev/ttyUSB*', '/dev/ttyACM*', '/dev/serial/by-id/*']
    ports = []
    for pattern in patterns:
        ports.extend(glob.glob(pattern))
    return sorted(ports)


def main():
    parser = argparse.ArgumentParser(
        description='AG-95 Gripper CLI Test Tool',
        formatter_class=argparse.RawDescriptionHelpFormatter,
        epilog="""
Examples:
  %(prog)s                              # Interactive mode
  %(prog)s --port /dev/ttyUSB0 --init   # Initialize
  %(prog)s --open                       # Open gripper  
  %(prog)s --close --force 80           # Close with 80%% force
  %(prog)s --position 500               # Move to 50%% open
  %(prog)s --status                     # Read status
  %(prog)s --scan                       # Scan serial ports
        """,
    )
    parser.add_argument('--port', default='/dev/ttyUSB0', help='Serial port')
    parser.add_argument('--slave-id', type=int, default=1, help='Modbus slave ID')
    parser.add_argument('--baudrate', type=int, default=115200, help='Baud rate')
    parser.add_argument('--scan', action='store_true', help='Scan for serial ports')
    parser.add_argument('--init', action='store_true', help='Initialize gripper')
    parser.add_argument('--open', action='store_true', help='Open gripper')
    parser.add_argument('--close', action='store_true', help='Close gripper')
    parser.add_argument('--position', type=int, help='Set position (0-1000)')
    parser.add_argument('--force', type=int, default=50, help='Force %% (20-100)')
    parser.add_argument('--status', action='store_true', help='Print status')
    parser.add_argument('--interactive', '-I', action='store_true', help='Interactive mode')

    args = parser.parse_args()

    if args.scan:
        ports = detect_serial_ports()
        if ports:
            print("Found serial ports:")
            for p in ports:
                print(f"  {p}")
        else:
            print("No serial ports found.")
            print("Tip: Check USB-to-RS485 adapter is connected and driver loaded.")
            print("     Try: ls /dev/ttyUSB* /dev/ttyACM*")
        return

    # Default to interactive if no action specified
    is_action = any([args.init, args.open, args.close, args.position is not None, args.status])
    if not is_action:
        args.interactive = True

    print(f"Connecting to AG-95 on {args.port} (slave={args.slave_id}, baud={args.baudrate})...")

    try:
        driver = AG95ModbusDriver(
            port=args.port,
            slave_id=args.slave_id,
            baudrate=args.baudrate,
        )
        driver.connect()
        print("✅ Connected!")

        if args.init:
            print("Initializing...")
            success = driver.initialize(full=True)
            print("✅ Initialized" if success else "❌ Init failed")

        if args.force != 50 or args.close or args.open:
            driver.set_force(args.force)

        if args.open:
            driver.open(args.force)
            print("Opening...")
            driver.wait_for_motion()

        if args.close:
            driver.close(args.force)
            print("Closing...")
            driver.wait_for_motion()

        if args.position is not None:
            driver.set_position(args.position)
            print(f"Moving to {args.position}‰...")
            driver.wait_for_motion()

        if args.status or is_action:
            print_status(driver)

        if args.interactive:
            interactive_mode(driver)

        driver.disconnect()
        print("Disconnected.")

    except ConnectionError as e:
        print(f"❌ Connection failed: {e}")
        print("\nTroubleshooting:")
        print("  1. Check USB-to-RS485 adapter is connected")
        print("  2. Check wiring: 24V(grey), GND(red), 485_A(white), 485_B(brown)")
        print("  3. Check gripper has power (LED should be blinking red)")
        print("  4. Try: sudo chmod 666 /dev/ttyUSB0")
        print("  5. Try: --scan to find available ports")
        sys.exit(1)
    except KeyboardInterrupt:
        print("\nInterrupted")
    except Exception as e:
        print(f"❌ Error: {e}")
        sys.exit(1)


if __name__ == '__main__':
    main()
