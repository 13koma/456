// generated from rosidl_typesupport_fastrtps_cpp/resource/idl__type_support.cpp.em
// with input from jaka_msgs:msg/RobotMsg.idl
// generated code does not contain a copyright notice
#include "jaka_msgs/msg/detail/robot_msg__rosidl_typesupport_fastrtps_cpp.hpp"
#include "jaka_msgs/msg/detail/robot_msg__struct.hpp"

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

namespace msg
{

namespace typesupport_fastrtps_cpp
{

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_jaka_msgs
cdr_serialize(
  const jaka_msgs::msg::RobotMsg & ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  // Member: motion_state
  cdr << ros_message.motion_state;
  // Member: power_state
  cdr << ros_message.power_state;
  // Member: servo_state
  cdr << ros_message.servo_state;
  // Member: collision_state
  cdr << ros_message.collision_state;
  return true;
}

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_jaka_msgs
cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  jaka_msgs::msg::RobotMsg & ros_message)
{
  // Member: motion_state
  cdr >> ros_message.motion_state;

  // Member: power_state
  cdr >> ros_message.power_state;

  // Member: servo_state
  cdr >> ros_message.servo_state;

  // Member: collision_state
  cdr >> ros_message.collision_state;

  return true;
}  // NOLINT(readability/fn_size)

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_jaka_msgs
get_serialized_size(
  const jaka_msgs::msg::RobotMsg & ros_message,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // Member: motion_state
  {
    size_t item_size = sizeof(ros_message.motion_state);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: power_state
  {
    size_t item_size = sizeof(ros_message.power_state);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: servo_state
  {
    size_t item_size = sizeof(ros_message.servo_state);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: collision_state
  {
    size_t item_size = sizeof(ros_message.collision_state);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  return current_alignment - initial_alignment;
}

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_jaka_msgs
max_serialized_size_RobotMsg(
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


  // Member: motion_state
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint16_t);
    current_alignment += array_size * sizeof(uint16_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint16_t));
  }

  // Member: power_state
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint16_t);
    current_alignment += array_size * sizeof(uint16_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint16_t));
  }

  // Member: servo_state
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint16_t);
    current_alignment += array_size * sizeof(uint16_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint16_t));
  }

  // Member: collision_state
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint16_t);
    current_alignment += array_size * sizeof(uint16_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint16_t));
  }

  size_t ret_val = current_alignment - initial_alignment;
  if (is_plain) {
    // All members are plain, and type is not empty.
    // We still need to check that the in-memory alignment
    // is the same as the CDR mandated alignment.
    using DataType = jaka_msgs::msg::RobotMsg;
    is_plain =
      (
      offsetof(DataType, collision_state) +
      last_member_size
      ) == ret_val;
  }

  return ret_val;
}

static bool _RobotMsg__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  auto typed_message =
    static_cast<const jaka_msgs::msg::RobotMsg *>(
    untyped_ros_message);
  return cdr_serialize(*typed_message, cdr);
}

static bool _RobotMsg__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  auto typed_message =
    static_cast<jaka_msgs::msg::RobotMsg *>(
    untyped_ros_message);
  return cdr_deserialize(cdr, *typed_message);
}

static uint32_t _RobotMsg__get_serialized_size(
  const void * untyped_ros_message)
{
  auto typed_message =
    static_cast<const jaka_msgs::msg::RobotMsg *>(
    untyped_ros_message);
  return static_cast<uint32_t>(get_serialized_size(*typed_message, 0));
}

static size_t _RobotMsg__max_serialized_size(char & bounds_info)
{
  bool full_bounded;
  bool is_plain;
  size_t ret_val;

  ret_val = max_serialized_size_RobotMsg(full_bounded, is_plain, 0);

  bounds_info =
    is_plain ? ROSIDL_TYPESUPPORT_FASTRTPS_PLAIN_TYPE :
    full_bounded ? ROSIDL_TYPESUPPORT_FASTRTPS_BOUNDED_TYPE : ROSIDL_TYPESUPPORT_FASTRTPS_UNBOUNDED_TYPE;
  return ret_val;
}

static message_type_support_callbacks_t _RobotMsg__callbacks = {
  "jaka_msgs::msg",
  "RobotMsg",
  _RobotMsg__cdr_serialize,
  _RobotMsg__cdr_deserialize,
  _RobotMsg__get_serialized_size,
  _RobotMsg__max_serialized_size
};

static rosidl_message_type_support_t _RobotMsg__handle = {
  rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
  &_RobotMsg__callbacks,
  get_message_typesupport_handle_function,
};

}  // namespace typesupport_fastrtps_cpp

}  // namespace msg

}  // namespace jaka_msgs

namespace rosidl_typesupport_fastrtps_cpp
{

template<>
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_EXPORT_jaka_msgs
const rosidl_message_type_support_t *
get_message_type_support_handle<jaka_msgs::msg::RobotMsg>()
{
  return &jaka_msgs::msg::typesupport_fastrtps_cpp::_RobotMsg__handle;
}

}  // namespace rosidl_typesupport_fastrtps_cpp

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, jaka_msgs, msg, RobotMsg)() {
  return &jaka_msgs::msg::typesupport_fastrtps_cpp::_RobotMsg__handle;
}

#ifdef __cplusplus
}
#endif
