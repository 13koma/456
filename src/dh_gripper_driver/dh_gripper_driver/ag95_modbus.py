"""
DH Robotics AG-95 Gripper - Modbus RTU Driver
==============================================

Low-level driver for communicating with the AG-95 gripper via Modbus RTU (RS485).

Based on: AG-95 Short Manual (Modbus-RTU) V2.1

Register Map:
    Control:
        0x0100 - Initialization (write: 0x01=init, 0xA5=full init)
        0x0101 - Force (20-100 %)
        0x0103 - Position (0-1000 permille)
    Feedback:
        0x0200 - Initialization state (0=not init, 1=initialized)
        0x0201 - Gripper state (0=moving, 1=reached, 2=caught, 3=dropped)
        0x0202 - Current position (0-1000 permille)
    Config:
        0x0300 - Save parameters
        0x0301 - Init direction (0=open, 1=close)
        0x0302 - Slave address
        0x0303 - Baud rate
        0x0402 - I/O mode switch

Default serial config: 115200, 8N1, slave_id=1
"""

import time
import struct
import logging
from enum import IntEnum
from typing import Optional, Tuple, NamedTuple
from dataclasses import dataclass

logger = logging.getLogger(__name__)


class GripperState(IntEnum):
    """Gripper motion state."""
    MOVING = 0
    REACHED_POSITION = 1
    OBJECT_CAUGHT = 2
    OBJECT_DROPPED = 3


class InitState(IntEnum):
    """Initialization state."""
    NOT_INITIALIZED = 0
    INITIALIZED = 1


@dataclass
class GripperStatus:
    """Full gripper status snapshot."""
    init_state: InitState
    gripper_state: GripperState
    current_position: int  # 0-1000 permille
    current_position_mm: float  # 0-98 mm (for AG-95)
    force_setting: int  # 20-100 %
    position_setting: int  # 0-1000 permille
    is_initialized: bool
    is_moving: bool
    object_caught: bool
    object_dropped: bool


class AG95ModbusDriver:
    """
    Low-level Modbus RTU driver for DH Robotics AG-95 gripper.
    
    Uses pymodbus for serial communication. Handles initialization,
    position/force control, and state reading.
    
    Usage:
        driver = AG95ModbusDriver('/dev/ttyUSB0')
        driver.connect()
        driver.initialize()
        driver.set_force(50)
        driver.set_position(500)  # 50% open
        status = driver.get_status()
        driver.disconnect()
    """
    
    # --- Register addresses ---
    # Control registers (high byte 0x01)
    REG_INIT = 0x0100
    REG_FORCE = 0x0101
    REG_POSITION = 0x0103
    
    # Feedback registers (high byte 0x02)
    REG_INIT_STATE = 0x0200
    REG_GRIPPER_STATE = 0x0201
    REG_CURRENT_POSITION = 0x0202
    
    # Configuration registers (high byte 0x03)
    REG_SAVE_PARAMS = 0x0300
    REG_INIT_DIRECTION = 0x0301
    REG_SLAVE_ADDRESS = 0x0302
    REG_BAUD_RATE = 0x0303
    REG_STOP_BITS = 0x0304
    REG_PARITY = 0x0305
    
    # I/O registers (high byte 0x04)
    REG_IO_TEST = 0x0400
    REG_IO_MODE = 0x0402
    
    # --- Constants ---
    STROKE_MM = 98.0  # AG-95 max stroke in mm
    POSITION_MIN = 0
    POSITION_MAX = 1000
    FORCE_MIN = 20
    FORCE_MAX = 100
    
    # Init commands
    INIT_NORMAL = 0x01
    INIT_FULL = 0xA5
    
    def __init__(
        self,
        port: str = '/dev/ttyUSB0',
        slave_id: int = 1,
        baudrate: int = 115200,
        timeout: float = 1.0,
    ):
        """
        Initialize the AG-95 Modbus RTU driver.
        
        Args:
            port: Serial port (e.g., '/dev/ttyUSB0')
            slave_id: Modbus slave address (default: 1)
            baudrate: Baud rate (default: 115200)
            timeout: Communication timeout in seconds
        """
        self.port = port
        self.slave_id = slave_id
        self.baudrate = baudrate
        self.timeout = timeout
        self._client = None
        self._connected = False
        
    def connect(self) -> bool:
        """
        Open serial connection to the gripper.
        
        Returns:
            True if connection successful.
            
        Raises:
            ConnectionError: If connection fails.
        """
        try:
            from pymodbus.client import ModbusSerialClient
            
            self._client = ModbusSerialClient(
                port=self.port,
                baudrate=self.baudrate,
                bytesize=8,
                parity='N',
                stopbits=1,
                timeout=self.timeout,
            )
            
            self._connected = self._client.connect()
            if not self._connected:
                raise ConnectionError(
                    f"Failed to connect to AG-95 on {self.port} "
                    f"(baudrate={self.baudrate}, slave={self.slave_id})"
                )
            
            logger.info(
                f"Connected to AG-95 on {self.port} "
                f"(baudrate={self.baudrate}, slave={self.slave_id})"
            )
            return True
            
        except ImportError:
            raise ImportError(
                "pymodbus is required: pip install pymodbus"
            )
        except Exception as e:
            self._connected = False
            raise ConnectionError(f"AG-95 connection error: {e}")
    
    def disconnect(self):
        """Close the serial connection."""
        if self._client:
            self._client.close()
            self._connected = False
            logger.info("Disconnected from AG-95")
    
    @property
    def is_connected(self) -> bool:
        return self._connected and self._client is not None
    
    def _write_register(self, address: int, value: int) -> bool:
        """Write a single register."""
        if not self.is_connected:
            raise ConnectionError("Not connected to gripper")
        
        # result = self._client.write_register(
        #     address=address, value=value, slave=self.slave_id
        # )
        result = self._client.write_register(
            address=address, value=value, device_id=self.slave_id
        )        
        if result.isError():
            logger.error(f"Write error at 0x{address:04X} = {value}: {result}")
            return False
        return True
    
    def _read_register(self, address: int, count: int = 1) -> Optional[list]:
        """Read holding register(s)."""
        if not self.is_connected:
            raise ConnectionError("Not connected to gripper")
        
        # result = self._client.read_holding_registers(
        #     address=address, count=count, slave=self.slave_id
        # )
        result = self._client.read_holding_registers(
            address=address, count=count, device_id=self.slave_id
        )
        
        if result.isError():
            logger.error(f"Read error at 0x{address:04X}: {result}")
            return None
        return result.registers
    
    # =========================================================================
    # Control Methods
    # =========================================================================
    
    def initialize(self, full: bool = False, timeout: float = 10.0) -> bool:
        """
        Initialize the gripper (required before any movement).
        
        Args:
            full: If True, performs full initialization (finds min AND max).
                  If False, performs normal init (finds one end based on direction).
            timeout: Max wait time for initialization to complete.
            
        Returns:
            True if initialization completed successfully.
        """
        cmd = self.INIT_FULL if full else self.INIT_NORMAL
        logger.info(f"Initializing AG-95 ({'full' if full else 'normal'})...")
        
        if not self._write_register(self.REG_INIT, cmd):
            return False
        
        # Wait for initialization to complete
        start = time.time()
        while time.time() - start < timeout:
            state = self.get_init_state()
            if state == InitState.INITIALIZED:
                logger.info("AG-95 initialization complete")
                return True
            time.sleep(0.1)
        
        logger.error(f"AG-95 initialization timeout ({timeout}s)")
        return False
    
    def set_force(self, force_percent: int) -> bool:
        """
        Set the gripper closing force.
        
        Args:
            force_percent: Force as percentage (20-100%).
                          Higher force = faster speed.
                          
        Returns:
            True if command was accepted.
        """
        force_percent = max(self.FORCE_MIN, min(self.FORCE_MAX, int(force_percent)))
        logger.debug(f"Setting force to {force_percent}%")
        return self._write_register(self.REG_FORCE, force_percent)
    
    def set_position(self, position_permille: int) -> bool:
        """
        Set the gripper target position. Movement starts immediately.
        
        Args:
            position_permille: Position in permille (0-1000).
                              0 = fully closed, 1000 = fully open.
                              500 = half open (~49mm for AG-95).
                              
        Returns:
            True if command was accepted.
        """
        position_permille = max(
            self.POSITION_MIN, min(self.POSITION_MAX, int(position_permille))
        )
        logger.debug(f"Setting position to {position_permille}‰")
        return self._write_register(self.REG_POSITION, position_permille)
    
    def set_position_mm(self, opening_mm: float) -> bool:
        """
        Set the gripper target position in millimeters.
        
        Args:
            opening_mm: Opening width in mm (0-98 for AG-95).
            
        Returns:
            True if command was accepted.
        """
        permille = int((opening_mm / self.STROKE_MM) * 1000.0)
        return self.set_position(permille)
    
    def open(self, force_percent: int = 50) -> bool:
        """Fully open the gripper."""
        self.set_force(force_percent)
        return self.set_position(self.POSITION_MAX)
    
    def close(self, force_percent: int = 50) -> bool:
        """Fully close the gripper (will stop on object detection)."""
        self.set_force(force_percent)
        return self.set_position(self.POSITION_MIN)
    
    def move_to(
        self,
        position_permille: int,
        force_percent: int = 50,
        wait: bool = False,
        timeout: float = 5.0,
    ) -> bool:
        """
        Move gripper to position with specified force.
        
        Args:
            position_permille: Target position (0-1000).
            force_percent: Grip force (20-100%).
            wait: If True, blocks until movement completes.
            timeout: Max wait time if blocking.
            
        Returns:
            True if command sent (or movement completed if wait=True).
        """
        self.set_force(force_percent)
        if not self.set_position(position_permille):
            return False
        
        if wait:
            return self.wait_for_motion(timeout)
        return True
    
    def wait_for_motion(self, timeout: float = 5.0) -> bool:
        """
        Block until gripper stops moving.
        
        Returns:
            True if motion completed (reached, caught, or dropped).
        """
        start = time.time()
        time.sleep(0.05)  # Small delay for motion to start
        
        while time.time() - start < timeout:
            state = self.get_gripper_state()
            if state is not None and state != GripperState.MOVING:
                return True
            time.sleep(0.02)
        
        logger.warning(f"Wait for motion timeout ({timeout}s)")
        return False
    
    # =========================================================================
    # Feedback Methods
    # =========================================================================
    
    def get_init_state(self) -> Optional[InitState]:
        """Read initialization state."""
        regs = self._read_register(self.REG_INIT_STATE)
        if regs is None:
            return None
        return InitState(regs[0])
    
    def get_gripper_state(self) -> Optional[GripperState]:
        """Read current gripper state."""
        regs = self._read_register(self.REG_GRIPPER_STATE)
        if regs is None:
            return None
        try:
            return GripperState(regs[0])
        except ValueError:
            logger.warning(f"Unknown gripper state: {regs[0]}")
            return None
    
    def get_current_position(self) -> Optional[int]:
        """Read current position in permille (0-1000)."""
        regs = self._read_register(self.REG_CURRENT_POSITION)
        if regs is None:
            return None
        return regs[0]
    
    def get_current_position_mm(self) -> Optional[float]:
        """Read current position in mm."""
        pos = self.get_current_position()
        if pos is None:
            return None
        return (pos / 1000.0) * self.STROKE_MM
    
    def get_force_setting(self) -> Optional[int]:
        """Read currently set force (%)."""
        regs = self._read_register(self.REG_FORCE)
        if regs is None:
            return None
        return regs[0]
    
    def get_position_setting(self) -> Optional[int]:
        """Read currently set target position (permille)."""
        regs = self._read_register(self.REG_POSITION)
        if regs is None:
            return None
        return regs[0]
    
    def get_status(self) -> Optional[GripperStatus]:
        """
        Read full gripper status (multiple register reads).
        
        Returns:
            GripperStatus with all current values, or None on error.
        """
        init = self.get_init_state()
        state = self.get_gripper_state()
        pos = self.get_current_position()
        force = self.get_force_setting()
        target = self.get_position_setting()
        
        if any(v is None for v in [init, state, pos]):
            return None
        
        return GripperStatus(
            init_state=init,
            gripper_state=state,
            current_position=pos,
            current_position_mm=(pos / 1000.0) * self.STROKE_MM,
            force_setting=force or 0,
            position_setting=target or 0,
            is_initialized=(init == InitState.INITIALIZED),
            is_moving=(state == GripperState.MOVING),
            object_caught=(state == GripperState.OBJECT_CAUGHT),
            object_dropped=(state == GripperState.OBJECT_DROPPED),
        )
    
    # =========================================================================
    # Configuration Methods
    # =========================================================================
    
    def set_init_direction(self, close_first: bool = False) -> bool:
        """Set initialization direction (0=open first, 1=close first)."""
        return self._write_register(self.REG_INIT_DIRECTION, 1 if close_first else 0)
    
    def save_parameters(self) -> bool:
        """
        Save all parameters to flash. Takes 1-2 seconds.
        Gripper won't respond during save process.
        """
        logger.info("Saving parameters to flash (1-2s)...")
        result = self._write_register(self.REG_SAVE_PARAMS, 1)
        if result:
            time.sleep(2.0)  # Wait for flash write
        return result
    
    def set_io_mode(self, enabled: bool) -> bool:
        """Enable/disable I/O control mode."""
        return self._write_register(self.REG_IO_MODE, 1 if enabled else 0)
    
    def __enter__(self):
        self.connect()
        return self
    
    def __exit__(self, *args):
        self.disconnect()
    
    def __repr__(self):
        return (
            f"AG95ModbusDriver(port={self.port!r}, slave={self.slave_id}, "
            f"connected={self.is_connected})"
        )
