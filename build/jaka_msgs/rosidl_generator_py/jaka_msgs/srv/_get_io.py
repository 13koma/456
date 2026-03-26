# generated from rosidl_generator_py/resource/_idl.py.em
# with input from jaka_msgs:srv/GetIO.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_GetIO_Request(type):
    """Metaclass of message 'GetIO_Request'."""

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
                'jaka_msgs.srv.GetIO_Request')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__srv__get_io__request
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__srv__get_io__request
            cls._CONVERT_TO_PY = module.convert_to_py_msg__srv__get_io__request
            cls._TYPE_SUPPORT = module.type_support_msg__srv__get_io__request
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__srv__get_io__request

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class GetIO_Request(metaclass=Metaclass_GetIO_Request):
    """Message class 'GetIO_Request'."""

    __slots__ = [
        '_signal',
        '_path',
        '_type',
        '_index',
    ]

    _fields_and_field_types = {
        'signal': 'string',
        'path': 'int16',
        'type': 'int16',
        'index': 'int16',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.BasicType('int16'),  # noqa: E501
        rosidl_parser.definition.BasicType('int16'),  # noqa: E501
        rosidl_parser.definition.BasicType('int16'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.signal = kwargs.get('signal', str())
        self.path = kwargs.get('path', int())
        self.type = kwargs.get('type', int())
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
        if self.signal != other.signal:
            return False
        if self.path != other.path:
            return False
        if self.type != other.type:
            return False
        if self.index != other.index:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def signal(self):
        """Message field 'signal'."""
        return self._signal

    @signal.setter
    def signal(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'signal' field must be of type 'str'"
        self._signal = value

    @builtins.property
    def path(self):
        """Message field 'path'."""
        return self._path

    @path.setter
    def path(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'path' field must be of type 'int'"
            assert value >= -32768 and value < 32768, \
                "The 'path' field must be an integer in [-32768, 32767]"
        self._path = value

    @builtins.property  # noqa: A003
    def type(self):  # noqa: A003
        """Message field 'type'."""
        return self._type

    @type.setter  # noqa: A003
    def type(self, value):  # noqa: A003
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'type' field must be of type 'int'"
            assert value >= -32768 and value < 32768, \
                "The 'type' field must be an integer in [-32768, 32767]"
        self._type = value

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

import math  # noqa: E402, I100

# already imported above
# import rosidl_parser.definition


class Metaclass_GetIO_Response(type):
    """Metaclass of message 'GetIO_Response'."""

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
                'jaka_msgs.srv.GetIO_Response')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__srv__get_io__response
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__srv__get_io__response
            cls._CONVERT_TO_PY = module.convert_to_py_msg__srv__get_io__response
            cls._TYPE_SUPPORT = module.type_support_msg__srv__get_io__response
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__srv__get_io__response

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class GetIO_Response(metaclass=Metaclass_GetIO_Response):
    """Message class 'GetIO_Response'."""

    __slots__ = [
        '_value',
        '_message',
    ]

    _fields_and_field_types = {
        'value': 'float',
        'message': 'string',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.value = kwargs.get('value', float())
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
        if self.value != other.value:
            return False
        if self.message != other.message:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def value(self):
        """Message field 'value'."""
        return self._value

    @value.setter
    def value(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'value' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'value' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._value = value

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


class Metaclass_GetIO(type):
    """Metaclass of service 'GetIO'."""

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
                'jaka_msgs.srv.GetIO')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._TYPE_SUPPORT = module.type_support_srv__srv__get_io

            from jaka_msgs.srv import _get_io
            if _get_io.Metaclass_GetIO_Request._TYPE_SUPPORT is None:
                _get_io.Metaclass_GetIO_Request.__import_type_support__()
            if _get_io.Metaclass_GetIO_Response._TYPE_SUPPORT is None:
                _get_io.Metaclass_GetIO_Response.__import_type_support__()


class GetIO(metaclass=Metaclass_GetIO):
    from jaka_msgs.srv._get_io import GetIO_Request as Request
    from jaka_msgs.srv._get_io import GetIO_Response as Response

    def __init__(self):
        raise NotImplementedError('Service classes can not be instantiated')
