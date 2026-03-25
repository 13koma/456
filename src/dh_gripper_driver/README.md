# DH Robotics AG-95 Gripper Driver (ROS2)

ROS2 driver for the DH Robotics AG-95 adaptive electric gripper, communicating via Modbus RTU over RS485.

## Hardware Setup

### For First Tests (USB-to-RS485)

```
[Jetson/PC] --USB--> [USB-to-RS485 adapter] --RS485--> [AG-95 Gripper]
                                              + 24V PSU
```

**Wiring (4 wires needed):**

| Wire # | Color  | Signal | Connect to           |
|--------|--------|--------|----------------------|
| 1      | White  | 485_A  | RS485 adapter T/R+   |
| 2      | Brown  | 485_B  | RS485 adapter T/R-   |
| 5      | Grey   | 24V    | 24V DC power supply  |
| 8      | Red    | GND    | Power supply GND     |

**Steps:**
1. Connect 24V power supply to grey (24V) and red (GND) wires
2. Connect white (485_A) to RS485 adapter's A/T+/R+ terminal
3. Connect brown (485_B) to RS485 adapter's B/T-/R- terminal
4. Plug USB end into Jetson/PC
5. Gripper LED should blink red (uninitialized state)

**Check serial port:**
```bash
ls /dev/ttyUSB*
# If permission denied:
sudo chmod 666 /dev/ttyUSB0
# Or add user to dialout group (permanent):
sudo usermod -aG dialout $USER
```

### For Production (via JAKA Zu12)

**Option A: JAKA Tool RS485 (recommended)**
- Route RS485 (485_A, 485_B) through JAKA's end-effector connector
- Power from JAKA's 24V tool output
- Keeps full Modbus RTU control with position/force feedback

**Option B: JAKA Tool Digital IO (limited)**
- Use JAKA's digital IO to control gripper in I/O mode (4 preset groups)
- Use jaka_driver's `set_io` / `get_io` services
- Simpler wiring but limited to 4 preset position/force combinations

## Quick Test (No ROS2)

```bash
cd src/dh_gripper_driver

# Scan for serial ports
python3 scripts/test_gripper_cli.py --scan

# Interactive mode
python3 scripts/test_gripper_cli.py --port /dev/ttyUSB0

# Commands
python3 scripts/test_gripper_cli.py --init              # Initialize
python3 scripts/test_gripper_cli.py --open               # Open
python3 scripts/test_gripper_cli.py --close --force 80   # Close with 80% force
python3 scripts/test_gripper_cli.py --position 500       # Half open
python3 scripts/test_gripper_cli.py --status             # Read status
```

## ROS2 Usage

### Build
```bash
cd ~/ros2_ws
colcon build --packages-select dh_gripper_driver
source install/setup.bash
```

### Launch

```bash
# Real hardware:
ros2 launch dh_gripper_driver gripper.launch.py port:=/dev/ttyUSB0

# With auto-initialization:
ros2 launch dh_gripper_driver gripper.launch.py auto_init:=true

# Simulation (no hardware):
ros2 launch dh_gripper_driver gripper.launch.py simulation:=true
```

### Control via CLI

```bash
# Initialize (required before first use!)
ros2 service call /dh_gripper_node/initialize std_srvs/srv/Trigger

# Open gripper
ros2 service call /dh_gripper_node/open std_srvs/srv/Trigger

# Close gripper
ros2 service call /dh_gripper_node/close std_srvs/srv/Trigger

# Set position (0=closed, 1000=open)
ros2 topic pub --once /dh_gripper_node/position_cmd std_msgs/msg/Float32 "{data: 500.0}"

# Set position + force [position_permille, force_percent]
ros2 topic pub --once /dh_gripper_node/command std_msgs/msg/Float32MultiArray "{data: [300.0, 80.0]}"

# Monitor state
ros2 topic echo /dh_gripper_node/state

# Monitor position
ros2 topic echo /dh_gripper_node/current_position
```

## Topics & Services

### Published Topics
| Topic                              | Type                    | Description                    |
|------------------------------------|-------------------------|--------------------------------|
| `~/state`                          | `std_msgs/String`       | JSON state (all fields)        |
| `~/current_position`               | `std_msgs/Float32`      | Current position (0-1000 ‰)   |
| `~/joint_states`                   | `sensor_msgs/JointState`| For URDF/MoveIt integration    |

### Subscribed Topics
| Topic                              | Type                          | Description                          |
|------------------------------------|-------------------------------|--------------------------------------|
| `~/command`                        | `std_msgs/Float32MultiArray`  | [position_permille, force_percent]   |
| `~/position_cmd`                   | `std_msgs/Float32`            | Position only (uses default force)   |

### Services
| Service          | Type               | Description                  |
|------------------|--------------------|------------------------------|
| `~/initialize`   | `std_srvs/Trigger` | Initialize gripper (full)    |
| `~/open`         | `std_srvs/Trigger` | Fully open                   |
| `~/close`        | `std_srvs/Trigger` | Fully close                  |

## State JSON Format
```json
{
  "initialized": true,
  "state": "OBJECT_CAUGHT",
  "state_code": 2,
  "position_permille": 342,
  "position_mm": 33.52,
  "force_percent": 50,
  "target_permille": 0,
  "is_moving": false,
  "object_caught": true,
  "object_dropped": false
}
```

## AG-95 Key Specs
- Stroke: 0-98mm (both jaws combined)
- Force: 45-160N per jaw (mapped to 20-100%)
- Open/close time: 0.7s
- Position repeatability: ±0.03mm
- Communication: Modbus RTU @ 115200, 8N1
- Power: 24V DC, 0.8A nominal / 1.5A peak

## LED Indicators
- **Red blinking** — Not initialized
- **Blue solid** — Initialized, ready
- **Purple flash** — Command received
- **Green solid** — Object caught
- **Green blinking** — Object dropped

## Modbus Register Reference

| Register | Function           | R/W  | Values                               |
|----------|--------------------|------|--------------------------------------|
| 0x0100   | Initialize         | R/W  | 0x01=init, 0xA5=full init            |
| 0x0101   | Force              | R/W  | 20-100 (%)                           |
| 0x0103   | Position           | R/W  | 0-1000 (‰)                          |
| 0x0200   | Init state         | R    | 0=not init, 1=initialized            |
| 0x0201   | Gripper state      | R    | 0=moving, 1=reached, 2=caught, 3=dropped |
| 0x0202   | Current position   | R    | 0-1000 (‰)                          |

## Dependencies
- Python 3.8+
- pymodbus (`pip install pymodbus`)
- ROS2 Humble
