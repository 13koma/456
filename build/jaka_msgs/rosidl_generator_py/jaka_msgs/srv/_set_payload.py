# generated from rosidl_generator_py/resource/_idl.py.em
# with input from jaka_msgs:srv/SetPayload.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import math  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_SetPayload_Request(type):
    """Metaclass of message 'SetPayload_Request'."""

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
                'jaka_msgs.srv.SetPayload_Request')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__srv__set_payload__request
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__srv__set_payload__request
            cls._CONVERT_TO_PY = module.convert_to_py_msg__srv__set_payload__request
            cls._TYPE_SUPPORT = module.type_support_msg__srv__set_payload__request
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__srv__set_payload__request

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class SetPayload_Request(metaclass=Metaclass_SetPayload_Request):
    """Message class 'SetPayload_Request'."""

    __slots__ = [
        '_tool_num',
        '_mass',
        '_xc',
        '_yc',
        '_zc',
    ]

    _fields_and_field_types = {
        'tool_num': 'int16',
        'mass': 'float',
        'xc': 'float',
        'yc': 'float',
        'zc': 'float',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('int16'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.tool_num = kwargs.get('tool_num', int())
        self.mass = kwargs.get('mass', float())
        self.xc = kwargs.get('xc', float())
        self.yc = kwargs.get('yc', float())
        self.zc = kwargs.get('zc', float())

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
        if self.tool_num != other.tool_num:
            return False
        if self.mass != other.mass:
            return False
        if self.xc != other.xc:
            return False
        if self.yc != other.yc:
            return False
        if self.zc != other.zc:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def tool_num(self):
        """Message field 'tool_num'."""
        return self._tool_num

    @tool_num.setter
    def tool_num(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'tool_num' field must be of type 'int'"
            assert value >= -32768 and value < 32768, \
                "The 'tool_num' field must be an integer in [-32768, 32767]"
        self._tool_num = value

    @builtins.property
    def mass(self):
        """Message field 'mass'."""
        return self._mass

    @mass.setter
    def mass(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'mass' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'mass' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._mass = value

    @builtins.property
    def xc(self):
        """Message field 'xc'."""
        return self._xc

    @xc.setter
    def xc(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'xc' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'xc' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._xc = value

    @builtins.property
    def yc(self):
        """Message field 'yc'."""
        return self._yc

    @yc.setter
    def yc(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'yc' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'yc' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._yc = value

    @builtins.property
    def zc(self):
        """Message field 'zc'."""
        return self._zc

    @zc.setter
    def zc(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'zc' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'zc' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._zc = value


# Import statements for member types

# already imported above
# import builtins

# already imported above
# import rosidl_parser.definition


class Metaclass_SetPayload_Response(type):
    """Metaclass of message 'SetPayload_Response'."""

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
                'jaka_msgs.srv.SetPayload_Response')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__srv__set_payload__response
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__srv__set_payload__response
            cls._CONVERT_TO_PY = module.convert_to_py_msg__srv__set_payload__response
            cls._TYPE_SUPPORT = module.type_support_msg__srv__set_payload__response
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__srv__set_payload__response

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class SetPayload_Response(metaclass=Metaclass_SetPayload_Response):
    """Message class 'SetPayload_Response'."""

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


class Metaclass_SetPayload(type):
    """Metaclass of service 'SetPayload'."""

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
                'jaka_msgs.srv.SetPayload')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._TYPE_SUPPORT = module.type_support_srv__srv__set_payload

            from jaka_msgs.srv import _set_payload
            if _set_payload.Metaclass_SetPayload_Request._TYPE_SUPPORT is None:
                _set_payload.Metaclass_SetPayload_Request.__import_type_support__()
            if _set_payload.Metaclass_SetPayload_Response._TYPE_SUPPORT is None:
                _set_payload.Metaclass_SetPayload_Response.__import_type_support__()


class SetPayload(metaclass=Metaclass_SetPayload):
    from jaka_msgs.srv._set_payload import SetPayload_Request as Request
    from jaka_msgs.srv._set_payload import SetPayload_Response as Response

    def __init__(self):
        raise NotImplementedError('Service classes can not be instantiated')
