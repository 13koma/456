// generated from rosidl_typesupport_fastrtps_cpp/resource/idl__type_support.cpp.em
// with input from jaka_msgs:srv/ServoMoveEnable.idl
// generated code does not contain a copyright notice
#include "jaka_msgs/srv/detail/servo_move_enable__rosidl_typesupport_fastrtps_cpp.hpp"
#include "jaka_msgs/srv/detail/servo_move_enable__struct.hpp"

#include <limits>
#include <stdexcept>
#include <string>
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_fastrtps_cpp/identifier.hpp"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support_decl.hpp"
#include "rosidl_typesupport_fastrtps_cpp/wstring_conversion.hpp"
#include "fastcdr/Cdr.h"


// forward declaration of message dependencies and their conversion functions

namespace jaka_msgs
{

namespace srv
{

namespace typesupport_fastrtps_cpp
{

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_jaka_msgs
cdr_serialize(
  const jaka_msgs::srv::ServoMoveEnable_Request & ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  // Member: enable
  cdr << (ros_message.enable ? true : false);
  return true;
}

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_jaka_msgs
cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  jaka_msgs::srv::ServoMoveEnable_Request & ros_message)
{
  // Member: enable
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message.enable = tmp ? true : false;
  }

  return true;
}  // NOLINT(readability/fn_size)

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_jaka_msgs
get_serialized_size(
  const jaka_msgs::srv::ServoMoveEnable_Request & ros_message,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // Member: enable
  {
    size_t item_size = sizeof(ros_message.enable);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  return current_alignment - initial_alignment;
}

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_jaka_msgs
max_serialized_size_ServoMoveEnable_Request(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  size_t last_member_size = 0;
  (void)last_member_size;
  (void)padding;
  (void)wchar_size;

  full_bounded = true;
  is_plain = true;


  // Member: enable
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }

  size_t ret_val = current_alignment - initial_alignment;
  if (is_plain) {
    // All members are plain, and type is not empty.
    // We still need to check that the in-memory alignment
    // is the same as the CDR mandated alignment.
    using DataType = jaka_msgs::srv::ServoMoveEnable_Request;
    is_plain =
      (
      offsetof(DataType, enable) +
      last_member_size
      ) == ret_val;
  }

  return ret_val;
}

static bool _ServoMoveEnable_Request__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  auto typed_message =
    static_cast<const jaka_msgs::srv::ServoMoveEnable_Request *>(
    untyped_ros_message);
  return cdr_serialize(*typed_message, cdr);
}

static bool _ServoMoveEnable_Request__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  auto typed_message =
    static_cast<jaka_msgs::srv::ServoMoveEnable_Request *>(
    untyped_ros_message);
  return cdr_deserialize(cdr, *typed_message);
}

static uint32_t _ServoMoveEnable_Request__get_serialized_size(
  const void * untyped_ros_message)
{
  auto typed_message =
    static_cast<const jaka_msgs::srv::ServoMoveEnable_Request *>(
    untyped_ros_message);
  return static_cast<uint32_t>(get_serialized_size(*typed_message, 0));
}

static size_t _ServoMoveEnable_Request__max_serialized_size(char & bounds_info)
{
  bool full_bounded;
  bool is_plain;
  size_t ret_val;

  ret_val = max_serialized_size_ServoMoveEnable_Request(full_bounded, is_plain, 0);

  bounds_info =
    is_plain ? ROSIDL_TYPESUPPORT_FASTRTPS_PLAIN_TYPE :
    full_bounded ? ROSIDL_TYPESUPPORT_FASTRTPS_BOUNDED_TYPE : ROSIDL_TYPESUPPORT_FASTRTPS_UNBOUNDED_TYPE;
  return ret_val;
}

static message_type_support_callbacks_t _ServoMoveEnable_Request__callbacks = {
  "jaka_msgs::srv",
  "ServoMoveEnable_Request",
  _ServoMoveEnable_Request__cdr_serialize,
  _ServoMoveEnable_Request__cdr_deserialize,
  _ServoMoveEnable_Request__get_serialized_size,
  _ServoMoveEnable_Request__max_serialized_size
};

static rosidl_message_type_support_t _ServoMoveEnable_Request__handle = {
  rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
  &_ServoMoveEnable_Request__callbacks,
  get_message_typesupport_handle_function,
};

}  // namespace typesupport_fastrtps_cpp

}  // namespace srv

}  // namespace jaka_msgs

namespace rosidl_typesupport_fastrtps_cpp
{

template<>
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_EXPORT_jaka_msgs
const rosidl_message_type_support_t *
get_message_type_support_handle<jaka_msgs::srv::ServoMoveEnable_Request>()
{
  return &jaka_msgs::srv::typesupport_fastrtps_cpp::_ServoMoveEnable_Request__handle;
}

}  // namespace rosidl_typesupport_fastrtps_cpp

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, jaka_msgs, srv, ServoMoveEnable_Request)() {
  return &jaka_msgs::srv::typesupport_fastrtps_cpp::_ServoMoveEnable_Request__handle;
}

#ifdef __cplusplus
}
#endif

// already included above
// #include <limits>
// already included above
// #include <stdexcept>
// already included above
// #include <string>
// already included above
// #include "rosidl_typesupport_cpp/message_type_support.hpp"
// already included above
// #include "rosidl_typesupport_fastrtps_cpp/identifier.hpp"
// already included above
// #include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
// already included above
// #include "rosidl_typesupport_fastrtps_cpp/message_type_support_decl.hpp"
// already included above
// #include "rosidl_typesupport_fastrtps_cpp/wstring_conversion.hpp"
// already included above
// #include "fastcdr/Cdr.h"


// forward declaration of message dependencies and their conversion functions

namespace jaka_msgs
{

namespace srv
{

namespace typesupport_fastrtps_cpp
{

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_jaka_msgs
cdr_serialize(
  const jaka_msgs::srv::ServoMoveEnable_Response & ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  // Member: ret
  cdr << ros_message.ret;
  // Member: message
  cdr << ros_message.message;
  return true;
}

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_jaka_msgs
cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  jaka_msgs::srv::ServoMoveEnable_Response & ros_message)
{
  // Member: ret
  cdr >> ros_message.ret;

  // Member: message
  cdr >> ros_message.message;

  return true;
}  // NOLINT(readability/fn_size)

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_jaka_msgs
get_serialized_size(
  const jaka_msgs::srv::ServoMoveEnable_Response & ros_message,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // Member: ret
  {
    size_t item_size = sizeof(ros_message.ret);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: message
  current_alignment += padding +
    eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
    (ros_message.message.size() + 1);

  return current_alignment - initial_alignment;
}

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_jaka_msgs
max_serialized_size_ServoMoveEnable_Response(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  size_t last_member_size = 0;
  (void)last_member_size;
  (void)padding;
  (void)wchar_size;

  full_bounded = true;
  is_plain = true;


  // Member: ret
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint16_t);
    current_alignment += array_size * sizeof(uint16_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint16_t));
  }

  // Member: message
  {
    size_t array_size = 1;

    full_bounded = false;
    is_plain = false;
    for (size_t index = 0; index < array_size; ++index) {
      current_alignment += padding +
        eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
        1;
    }
  }

  size_t ret_val = current_alignment - initial_alignment;
  if (is_plain) {
    // All members are plain, and type is not empty.
    // We still need to check that the in-memory alignment
    // is the same as the CDR mandated alignment.
    using DataType = jaka_msgs::srv::ServoMoveEnable_Response;
    is_plain =
      (
      offsetof(DataType, message) +
      last_member_size
      ) == ret_val;
  }

  return ret_val;
}

static bool _ServoMoveEnable_Response__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  auto typed_message =
    static_cast<const jaka_msgs::srv::ServoMoveEnable_Response *>(
    untyped_ros_message);
  return cdr_serialize(*typed_message, cdr);
}

static bool _ServoMoveEnable_Response__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  auto typed_message =
    static_cast<jaka_msgs::srv::ServoMoveEnable_Response *>(
    untyped_ros_message);
  return cdr_deserialize(cdr, *typed_message);
}

static uint32_t _ServoMoveEnable_Response__get_serialized_size(
  const void * untyped_ros_message)
{
  auto typed_message =
    static_cast<const jaka_msgs::srv::ServoMoveEnable_Response *>(
    untyped_ros_message);
  return static_cast<uint32_t>(get_serialized_size(*typed_message, 0));
}

static size_t _ServoMoveEnable_Response__max_serialized_size(char & bounds_info)
{
  bool full_bounded;
  bool is_plain;
  size_t ret_val;

  ret_val = max_serialized_size_ServoMoveEnable_Response(full_bounded, is_plain, 0);

  bounds_info =
    is_plain ? ROSIDL_TYPESUPPORT_FASTRTPS_PLAIN_TYPE :
    full_bounded ? ROSIDL_TYPESUPPORT_FASTRTPS_BOUNDED_TYPE : ROSIDL_TYPESUPPORT_FASTRTPS_UNBOUNDED_TYPE;
  return ret_val;
}

static message_type_support_callbacks_t _ServoMoveEnable_Response__callbacks = {
  "jaka_msgs::srv",
  "ServoMoveEnable_Response",
  _ServoMoveEnable_Response__cdr_serialize,
  _ServoMoveEnable_Response__cdr_deserialize,
  _ServoMoveEnable_Response__get_serialized_size,
  _ServoMoveEnable_Response__max_serialized_size
};

static rosidl_message_type_support_t _ServoMoveEnable_Response__handle = {
  rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
  &_ServoMoveEnable_Response__callbacks,
  get_message_typesupport_handle_function,
};

}  // namespace typesupport_fastrtps_cpp

}  // namespace srv

}  // namespace jaka_msgs

namespace rosidl_typesupport_fastrtps_cpp
{

template<>
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_EXPORT_jaka_msgs
const rosidl_message_type_support_t *
get_message_type_support_handle<jaka_msgs::srv::ServoMoveEnable_Response>()
{
  return &jaka_msgs::srv::typesupport_fastrtps_cpp::_ServoMoveEnable_Response__handle;
}

}  // namespace rosidl_typesupport_fastrtps_cpp

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, jaka_msgs, srv, ServoMoveEnable_Response)() {
  return &jaka_msgs::srv::typesupport_fastrtps_cpp::_ServoMoveEnable_Response__handle;
}

#ifdef __cplusplus
}
#endif

#include "rmw/error_handling.h"
// already included above
// #include "rosidl_typesupport_fastrtps_cpp/identifier.hpp"
#include "rosidl_typesupport_fastrtps_cpp/service_type_support.h"
#include "rosidl_typesupport_fastrtps_cpp/service_type_support_decl.hpp"

namespace jaka_msgs
{

namespace srv
{

namespace typesupport_fastrtps_cpp
{

static service_type_support_callbacks_t _ServoMoveEnable__callbacks = {
  "jaka_msgs::srv",
  "ServoMoveEnable",
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, jaka_msgs, srv, ServoMoveEnable_Request)(),
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, jaka_msgs, srv, ServoMoveEnable_Response)(),
};

static rosidl_service_type_support_t _ServoMoveEnable__handle = {
  rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
  &_ServoMoveEnable__callbacks,
  get_service_typesupport_handle_function,
};

}  // namespace typesupport_fastrtps_cpp

}  // namespace srv

}  // namespace jaka_msgs

namespace rosidl_typesupport_fastrtps_cpp
{

template<>
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_EXPORT_jaka_msgs
const rosidl_service_type_support_t *
get_service_type_support_handle<jaka_msgs::srv::ServoMoveEnable>()
{
  return &jaka_msgs::srv::typesupport_fastrtps_cpp::_ServoMoveEnable__handle;
}

}  // namespace rosidl_typesupport_fastrtps_cpp

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, jaka_msgs, srv, ServoMoveEnable)() {
  return &jaka_msgs::srv::typesupport_fastrtps_cpp::_ServoMoveEnable__handle;
}

#ifdef __cplusplus
}
#endif
