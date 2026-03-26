# generated from rosidl_generator_py/resource/_idl.py.em
# with input from jaka_msgs:srv/Move.idl
# generated code does not contain a copyright notice


# Import statements for member types

# Member 'pose'
# Member 'ref_joint'
import array  # noqa: E402, I100

import builtins  # noqa: E402, I100

import math  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_Move_Request(type):
    """Metaclass of message 'Move_Request'."""

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
                'jaka_msgs.srv.Move_Request')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__srv__move__request
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__srv__move__request
            cls._CONVERT_TO_PY = module.convert_to_py_msg__srv__move__request
            cls._TYPE_SUPPORT = module.type_support_msg__srv__move__request
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__srv__move__request

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class Move_Request(metaclass=Metaclass_Move_Request):
    """Message class 'Move_Request'."""

    __slots__ = [
        '_pose',
        '_has_ref',
        '_ref_joint',
        '_mvvelo',
        '_mvacc',
        '_mvtime',
        '_mvradii',
        '_coord_mode',
        '_index',
    ]

    _fields_and_field_types = {
        'pose': 'sequence<float>',
        'has_ref': 'boolean',
        'ref_joint': 'sequence<float>',
        'mvvelo': 'float',
        'mvacc': 'float',
        'mvtime': 'float',
        'mvradii': 'float',
        'coord_mode': 'int16',
        'index': 'int16',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.UnboundedSequence(rosidl_parser.definition.BasicType('float')),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.UnboundedSequence(rosidl_parser.definition.BasicType('float')),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('int16'),  # noqa: E501
        rosidl_parser.definition.BasicType('int16'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.pose = array.array('f', kwargs.get('pose', []))
        self.has_ref = kwargs.get('has_ref', bool())
        self.ref_joint = array.array('f', kwargs.get('ref_joint', []))
        self.mvvelo = kwargs.get('mvvelo', float())
        self.mvacc = kwargs.get('mvacc', float())
        self.mvtime = kwargs.get('mvtime', float())
        self.mvradii = kwargs.get('mvradii', float())
        self.coord_mode = kwargs.get('coord_mode', int())
        self.index = kwargs.get('index', int())

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
        if self.pose != other.pose:
            return False
        if self.has_ref != other.has_ref:
            return False
        if self.ref_joint != other.ref_joint:
            return False
        if self.mvvelo != other.mvvelo:
            return False
        if self.mvacc != other.mvacc:
            return False
        if self.mvtime != other.mvtime:
            return False
        if self.mvradii != other.mvradii:
            return False
        if self.coord_mode != other.coord_mode:
            return False
        if self.index != other.index:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def pose(self):
        """Message field 'pose'."""
        return self._pose

    @pose.setter
    def pose(self, value):
        if isinstance(value, array.array):
            assert value.typecode == 'f', \
                "The 'pose' array.array() must have the type code of 'f'"
            self._pose = value
            return
        if __debug__:
            from collections.abc import Sequence
            from collections.abc import Set
            from collections import UserList
            from collections import UserString
            assert \
                ((isinstance(value, Sequence) or
                  isinstance(value, Set) or
                  isinstance(value, UserList)) and
                 not isinstance(value, str) and
                 not isinstance(value, UserString) and
                 all(isinstance(v, float) for v in value) and
                 all(not (val < -3.402823466e+38 or val > 3.402823466e+38) or math.isinf(val) for val in value)), \
                "The 'pose' field must be a set or sequence and each value of type 'float' and each float in [-340282346600000016151267322115014000640.000000, 340282346600000016151267322115014000640.000000]"
        self._pose = array.array('f', value)

    @builtins.property
    def has_ref(self):
        """Message field 'has_ref'."""
        return self._has_ref

    @has_ref.setter
    def has_ref(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'has_ref' field must be of type 'bool'"
        self._has_ref = value

    @builtins.property
    def ref_joint(self):
        """Message field 'ref_joint'."""
        return self._ref_joint

    @ref_joint.setter
    def ref_joint(self, value):
        if isinstance(value, array.array):
            assert value.typecode == 'f', \
                "The 'ref_joint' array.array() must have the type code of 'f'"
            self._ref_joint = value
            return
        if __debug__:
            from collections.abc import Sequence
            from collections.abc import Set
            from collections import UserList
            from collections import UserString
            assert \
                ((isinstance(value, Sequence) or
                  isinstance(value, Set) or
                  isinstance(value, UserList)) and
                 not isinstance(value, str) and
                 not isinstance(value, UserString) and
                 all(isinstance(v, float) for v in value) and
                 all(not (val < -3.402823466e+38 or val > 3.402823466e+38) or math.isinf(val) for val in value)), \
                "The 'ref_joint' field must be a set or sequence and each value of type 'float' and each float in [-340282346600000016151267322115014000640.000000, 340282346600000016151267322115014000640.000000]"
        self._ref_joint = array.array('f', value)

    @builtins.property
    def mvvelo(self):
        """Message field 'mvvelo'."""
        return self._mvvelo

    @mvvelo.setter
    def mvvelo(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'mvvelo' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'mvvelo' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._mvvelo = value

    @builtins.property
    def mvacc(self):
        """Message field 'mvacc'."""
        return self._mvacc

    @mvacc.setter
    def mvacc(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'mvacc' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'mvacc' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._mvacc = value

    @builtins.property
    def mvtime(self):
        """Message field 'mvtime'."""
        return self._mvtime

    @mvtime.setter
    def mvtime(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'mvtime' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'mvtime' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._mvtime = value

    @builtins.property
    def mvradii(self):
        """Message field 'mvradii'."""
        return self._mvradii

    @mvradii.setter
    def mvradii(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'mvradii' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'mvradii' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._mvradii = value

    @builtins.property
    def coord_mode(self):
        """Message field 'coord_mode'."""
        return self._coord_mode

    @coord_mode.setter
    def coord_mode(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'coord_mode' field must be of type 'int'"
            assert value >= -32768 and value < 32768, \
                "The 'coord_mode' field must be an integer in [-32768, 32767]"
        self._coord_mode = value

    @builtins.property
    def index(self):
        """Message field 'index'."""
        return self._index

    @index.setter
    def index(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'index' field must be of type 'int'"
            assert value >= -32768 and value < 32768, \
                "The 'index' field must be an integer in [-32768, 32767]"
        self._index = value


# Import statements for member types

# already imported above
# import builtins

# already imported above
# import rosidl_parser.definition


class Metaclass_Move_Response(type):
    """Metaclass of message 'Move_Response'."""

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
                'jaka_msgs.srv.Move_Response')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__srv__move__response
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__srv__move__response
            cls._CONVERT_TO_PY = module.convert_to_py_msg__srv__move__response
            cls._TYPE_SUPPORT = module.type_support_msg__srv__move__response
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__srv__move__response

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class Move_Response(metaclass=Metaclass_Move_Response):
    """Message class 'Move_Response'."""

    __slots__ = [
        '_ret',
        '_message',
    ]

    _fields_and_field_types = {
        'ret': 'int16',
        'message': 'string',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('int16'),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.ret = kwargs.get('ret', int())
        self.message = kwargs.get('message', str())

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
        if self.ret != other.ret:
            return False
        if self.message != other.message:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def ret(self):
        """Message field 'ret'."""
        return self._ret

    @ret.setter
    def ret(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'ret' field must be of type 'int'"
            assert value >= -32768 and value < 32768, \
                "The 'ret' field must be an integer in [-32768, 32767]"
        self._ret = value

    @builtins.property
    def message(self):
        """Message field 'message'."""
        return self._message

    @message.setter
    def message(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'message' field must be of type 'str'"
        self._message = value


class Metaclass_Move(type):
    """Metaclass of service 'Move'."""

    _TYPE_SUPPORT = None

    @classmethod
    def __import_type_support__(cls):
        try:
            from rosidl_generator_py import import_type_support
            module = import_type_support('jaka_msgs')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'jaka_msgs.srv.Move')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._TYPE_SUPPORT = module.type_support_srv__srv__move

            from jaka_msgs.srv import _move
            if _move.Metaclass_Move_Request._TYPE_SUPPORT is None:
                _move.Metaclass_Move_Request.__import_type_support__()
            if _move.Metaclass_Move_Response._TYPE_SUPPORT is None:
                _move.Metaclass_Move_Response.__import_type_support__()


class Move(metaclass=Metaclass_Move):
    from jaka_msgs.srv._move import Move_Request as Request
    from jaka_msgs.srv._move import Move_Response as Response

    def __init__(self):
        raise NotImplementedError('Service classes can not be instantiated')
