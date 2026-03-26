# generated from rosidl_generator_py/resource/_idl.py.em
# with input from jaka_msgs:msg/RobotMsg.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_RobotMsg(type):
    """Metaclass of message 'RobotMsg'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
    }

    @classmethod
    def __import_type_support__(cls):
        try:
            from rosidl_generator_py import import_type_support
            module = import_type_support('jaka_msgs')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'jaka_msgs.msg.RobotMsg')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__robot_msg
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__robot_msg
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__robot_msg
            cls._TYPE_SUPPORT = module.type_support_msg__msg__robot_msg
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__robot_msg

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class RobotMsg(metaclass=Metaclass_RobotMsg):
    """Message class 'RobotMsg'."""

    __slots__ = [
        '_motion_state',
        '_power_state',
        '_servo_state',
        '_collision_state',
    ]

    _fields_and_field_types = {
        'motion_state': 'int16',
        'power_state': 'int16',
        'servo_state': 'int16',
        'collision_state': 'int16',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('int16'),  # noqa: E501
        rosidl_parser.definition.BasicType('int16'),  # noqa: E501
        rosidl_parser.definition.BasicType('int16'),  # noqa: E501
        rosidl_parser.definition.BasicType('int16'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.motion_state = kwargs.get('motion_state', int())
        self.power_state = kwargs.get('power_state', int())
        self.servo_state = kwargs.get('servo_state', int())
        self.collision_state = kwargs.get('collision_state', int())

    def __repr__(self):
        typename = self.__class__.__module__.split('.')
        typename.pop()
        typename.append(self.__class__.__name__)
        args = []
        for s, t in zip(self.__slots__, self.SLOT_TYPES):
            field = getattr(self, s)
            fieldstr = repr(field)
            # We use Python array type for fields that can be directly stored
            # in them, and "normal" sequences for everything else.  If it is
            # a type that we store in an array, strip off the 'array' portion.
            if (
                isinstance(t, rosidl_parser.definition.AbstractSequence) and
                isinstance(t.value_type, rosidl_parser.definition.BasicType) and
                t.value_type.typename in ['float', 'double', 'int8', 'uint8', 'int16', 'uint16', 'int32', 'uint32', 'int64', 'uint64']
            ):
                if len(field) == 0:
                    fieldstr = '[]'
                else:
                    assert fieldstr.startswith('array(')
                    prefix = "array('X', "
                    suffix = ')'
                    fieldstr = fieldstr[len(prefix):-len(suffix)]
            args.append(s[1:] + '=' + fieldstr)
        return '%s(%s)' % ('.'.join(typename), ', '.join(args))

    def __eq__(self, other):
        if not isinstance(other, self.__class__):
            return False
        if self.motion_state != other.motion_state:
            return False
        if self.power_state != other.power_state:
            return False
        if self.servo_state != other.servo_state:
            return False
        if self.collision_state != other.collision_state:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def motion_state(self):
        """Message field 'motion_state'."""
        return self._motion_state

    @motion_state.setter
    def motion_state(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'motion_state' field must be of type 'int'"
            assert value >= -32768 and value < 32768, \
                "The 'motion_state' field must be an integer in [-32768, 32767]"
        self._motion_state = value

    @builtins.property
    def power_state(self):
        """Message field 'power_state'."""
        return self._power_state

    @power_state.setter
    def power_state(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'power_state' field must be of type 'int'"
            assert value >= -32768 and value < 32768, \
                "The 'power_state' field must be an integer in [-32768, 32767]"
        self._power_state = value

    @builtins.property
    def servo_state(self):
        """Message field 'servo_state'."""
        return self._servo_state

    @servo_state.setter
    def servo_state(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'servo_state' field must be of type 'int'"
            assert value >= -32768 and value < 32768, \
                "The 'servo_state' field must be an integer in [-32768, 32767]"
        self._servo_state = value

    @builtins.property
    def collision_state(self):
        """Message field 'collision_state'."""
        return self._collision_state

    @collision_state.setter
    def collision_state(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'collision_state' field must be of type 'int'"
            assert value >= -32768 and value < 32768, \
                "The 'collision_state' field must be an integer in [-32768, 32767]"
        self._collision_state = value
