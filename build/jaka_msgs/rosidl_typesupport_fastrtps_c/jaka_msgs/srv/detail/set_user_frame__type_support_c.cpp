// generated from rosidl_typesupport_fastrtps_c/resource/idl__type_support_c.cpp.em
// with input from jaka_msgs:srv/SetUserFrame.idl
// generated code does not contain a copyright notice
#include "jaka_msgs/srv/detail/set_user_frame__rosidl_typesupport_fastrtps_c.h"


#include <cassert>
#include <limits>
#include <string>
#include "rosidl_typesupport_fastrtps_c/identifier.h"
#include "rosidl_typesupport_fastrtps_c/wstring_conversion.hpp"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
#include "jaka_msgs/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
#include "jaka_msgs/srv/detail/set_user_frame__struct.h"
#include "jaka_msgs/srv/detail/set_user_frame__functions.h"
#include "fastcdr/Cdr.h"

#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-parameter"
# ifdef __clang__
#  pragma clang diagnostic ignored "-Wdeprecated-register"
#  pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
# endif
#endif
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif

// includes and forward declarations of message dependencies and their conversion functions

#if defined(__cplusplus)
extern "C"
{
#endif

#include "rosidl_runtime_c/primitives_sequence.h"  // pose
#include "rosidl_runtime_c/primitives_sequence_functions.h"  // pose

// forward declare type support functions


using _SetUserFrame_Request__ros_msg_type = jaka_msgs__srv__SetUserFrame_Request;

static bool _SetUserFrame_Request__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  const _SetUserFrame_Request__ros_msg_type * ros_message = static_cast<const _SetUserFrame_Request__ros_msg_type *>(untyped_ros_message);
  // Field name: pose
  {
    size_t size = ros_message->pose.size;
    auto array_ptr = ros_message->pose.data;
    cdr << static_cast<uint32_t>(size);
    cdr.serializeArray(array_ptr, size);
  }

  // Field name: user_num
  {
    cdr << ros_message->user_num;
  }

  return true;
}

static bool _SetUserFrame_Request__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  _SetUserFrame_Request__ros_msg_type * ros_message = static_cast<_SetUserFrame_Request__ros_msg_type *>(untyped_ros_message);
  // Field name: pose
  {
    uint32_t cdrSize;
    cdr >> cdrSize;
    size_t size = static_cast<size_t>(cdrSize);

    // Check there are at least 'size' remaining bytes in the CDR stream before resizing
    auto old_state = cdr.getState();
    bool correct_size = cdr.jump(size);
    cdr.setState(old_state);
    if (!correct_size) {
      fprintf(stderr, "sequence size exceeds remaining buffer\n");
      return false;
    }

    if (ros_message->pose.data) {
      rosidl_runtime_c__float__Sequence__fini(&ros_message->pose);
    }
    if (!rosidl_runtime_c__float__Sequence__init(&ros_message->pose, size)) {
      fprintf(stderr, "failed to create array for field 'pose'");
      return false;
    }
    auto array_ptr = ros_message->pose.data;
    cdr.deserializeArray(array_ptr, size);
  }

  // Field name: user_num
  {
    cdr >> ros_message->user_num;
  }

  return true;
}  // NOLINT(readability/fn_size)

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_jaka_msgs
size_t get_serialized_size_jaka_msgs__srv__SetUserFrame_Request(
  const void * untyped_ros_message,
  size_t current_alignment)
{
  const _SetUserFrame_Request__ros_msg_type * ros_message = static_cast<const _SetUserFrame_Request__ros_msg_type *>(untyped_ros_message);
  (void)ros_message;
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // field.name pose
  {
    size_t array_size = ros_message->pose.size;
    auto array_ptr = ros_message->pose.data;
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);
    (void)array_ptr;
    size_t item_size = sizeof(array_ptr[0]);
    current_alignment += array_size * item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name user_num
  {
    size_t item_size = sizeof(ros_message->user_num);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  return current_alignment - initial_alignment;
}

static uint32_t _SetUserFrame_Request__get_serialized_size(const void * untyped_ros_message)
{
  return static_cast<uint32_t>(
    get_serialized_size_jaka_msgs__srv__SetUserFrame_Request(
      untyped_ros_message, 0));
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_jaka_msgs
size_t max_serialized_size_jaka_msgs__srv__SetUserFrame_Request(
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

  // member: pose
  {
    size_t array_size = 0;
    full_bounded = false;
    is_plain = false;
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }
  // member: user_num
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
    using DataType = jaka_msgs__srv__SetUserFrame_Request;
    is_plain =
      (
      offsetof(DataType, user_num) +
      last_member_size
      ) == ret_val;
  }

  return ret_val;
}

static size_t _SetUserFrame_Request__max_serialized_size(char & bounds_info)
{
  bool full_bounded;
  bool is_plain;
  size_t ret_val;

  ret_val = max_serialized_size_jaka_msgs__srv__SetUserFrame_Request(
    full_bounded, is_plain, 0);

  bounds_info =
    is_plain ? ROSIDL_TYPESUPPORT_FASTRTPS_PLAIN_TYPE :
    full_bounded ? ROSIDL_TYPESUPPORT_FASTRTPS_BOUNDED_TYPE : ROSIDL_TYPESUPPORT_FASTRTPS_UNBOUNDED_TYPE;
  return ret_val;
}


static message_type_support_callbacks_t __callbacks_SetUserFrame_Request = {
  "jaka_msgs::srv",
  "SetUserFrame_Request",
  _SetUserFrame_Request__cdr_serialize,
  _SetUserFrame_Request__cdr_deserialize,
  _SetUserFrame_Request__get_serialized_size,
  _SetUserFrame_Request__max_serialized_size
};

static rosidl_message_type_support_t _SetUserFrame_Request__type_support = {
  rosidl_typesupport_fastrtps_c__identifier,
  &__callbacks_SetUserFrame_Request,
  get_message_typesupport_handle_function,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, jaka_msgs, srv, SetUserFrame_Request)() {
  return &_SetUserFrame_Request__type_support;
}

#if defined(__cplusplus)
}
#endif

// already included above
// #include <cassert>
// already included above
// #include <limits>
// already included above
// #include <string>
// already included above
// #include "rosidl_typesupport_fastrtps_c/identifier.h"
// already included above
// #include "rosidl_typesupport_fastrtps_c/wstring_conversion.hpp"
// already included above
// #include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
// already included above
// #include "jaka_msgs/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
// already included above
// #include "jaka_msgs/srv/detail/set_user_frame__struct.h"
// already included above
// #include "jaka_msgs/srv/detail/set_user_frame__functions.h"
// already included above
// #include "fastcdr/Cdr.h"

#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-parameter"
# ifdef __clang__
#  pragma clang diagnostic ignored "-Wdeprecated-register"
#  pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
# endif
#endif
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif

// includes and forward declarations of message dependencies and their conversion functions

#if defined(__cplusplus)
extern "C"
{
#endif

#include "rosidl_runtime_c/string.h"  // message
#include "rosidl_runtime_c/string_functions.h"  // message

// forward declare type support functions


using _SetUserFrame_Response__ros_msg_type = jaka_msgs__srv__SetUserFrame_Response;

static bool _SetUserFrame_Response__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  const _SetUserFrame_Response__ros_msg_type * ros_message = static_cast<const _SetUserFrame_Response__ros_msg_type *>(untyped_ros_message);
  // Field name: ret
  {
    cdr << ros_message->ret;
  }

  // Field name: message
  {
    const rosidl_runtime_c__String * str = &ros_message->message;
    if (str->capacity == 0 || str->capacity <= str->size) {
      fprintf(stderr, "string capacity not greater than size\n");
      return false;
    }
    if (str->data[str->size] != '\0') {
      fprintf(stderr, "string not null-terminated\n");
      return false;
    }
    cdr << str->data;
  }

  return true;
}

static bool _SetUserFrame_Response__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  _SetUserFrame_Response__ros_msg_type * ros_message = static_cast<_SetUserFrame_Response__ros_msg_type *>(untyped_ros_message);
  // Field name: ret
  {
    cdr >> ros_message->ret;
  }

  // Field name: message
  {
    std::string tmp;
    cdr >> tmp;
    if (!ros_message->message.data) {
      rosidl_runtime_c__String__init(&ros_message->message);
    }
    bool succeeded = rosidl_runtime_c__String__assign(
      &ros_message->message,
      tmp.c_str());
    if (!succeeded) {
      fprintf(stderr, "failed to assign string into field 'message'\n");
      return false;
    }
  }

  return true;
}  // NOLINT(readability/fn_size)

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_jaka_msgs
size_t get_serialized_size_jaka_msgs__srv__SetUserFrame_Response(
  const void * untyped_ros_message,
  size_t current_alignment)
{
  const _SetUserFrame_Response__ros_msg_type * ros_message = static_cast<const _SetUserFrame_Response__ros_msg_type *>(untyped_ros_message);
  (void)ros_message;
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // field.name ret
  {
    size_t item_size = sizeof(ros_message->ret);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name message
  current_alignment += padding +
    eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
    (ros_message->message.size + 1);

  return current_alignment - initial_alignment;
}

static uint32_t _SetUserFrame_Response__get_serialized_size(const void * untyped_ros_message)
{
  return static_cast<uint32_t>(
    get_serialized_size_jaka_msgs__srv__SetUserFrame_Response(
      untyped_ros_message, 0));
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_jaka_msgs
size_t max_serialized_size_jaka_msgs__srv__SetUserFrame_Response(
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

  // member: ret
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint16_t);
    current_alignment += array_size * sizeof(uint16_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint16_t));
  }
  // member: message
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
    using DataType = jaka_msgs__srv__SetUserFrame_Response;
    is_plain =
      (
      offsetof(DataType, message) +
      last_member_size
      ) == ret_val;
  }

  return ret_val;
}

static size_t _SetUserFrame_Response__max_serialized_size(char & bounds_info)
{
  bool full_bounded;
  bool is_plain;
  size_t ret_val;

  ret_val = max_serialized_size_jaka_msgs__srv__SetUserFrame_Response(
    full_bounded, is_plain, 0);

  bounds_info =
    is_plain ? ROSIDL_TYPESUPPORT_FASTRTPS_PLAIN_TYPE :
    full_bounded ? ROSIDL_TYPESUPPORT_FASTRTPS_BOUNDED_TYPE : ROSIDL_TYPESUPPORT_FASTRTPS_UNBOUNDED_TYPE;
  return ret_val;
}


static message_type_support_callbacks_t __callbacks_SetUserFrame_Response = {
  "jaka_msgs::srv",
  "SetUserFrame_Response",
  _SetUserFrame_Response__cdr_serialize,
  _SetUserFrame_Response__cdr_deserialize,
  _SetUserFrame_Response__get_serialized_size,
  _SetUserFrame_Response__max_serialized_size
};

static rosidl_message_type_support_t _SetUserFrame_Response__type_support = {
  rosidl_typesupport_fastrtps_c__identifier,
  &__callbacks_SetUserFrame_Response,
  get_message_typesupport_handle_function,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, jaka_msgs, srv, SetUserFrame_Response)() {
  return &_SetUserFrame_Response__type_support;
}

#if defined(__cplusplus)
}
#endif

#include "rosidl_typesupport_fastrtps_cpp/service_type_support.h"
#include "rosidl_typesupport_cpp/service_type_support.hpp"
// already included above
// #include "rosidl_typesupport_fastrtps_c/identifier.h"
// already included above
// #include "jaka_msgs/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
#include "jaka_msgs/srv/set_user_frame.h"

#if defined(__cplusplus)
extern "C"
{
#endif

static service_type_support_callbacks_t SetUserFrame__callbacks = {
  "jaka_msgs::srv",
  "SetUserFrame",
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, jaka_msgs, srv, SetUserFrame_Request)(),
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, jaka_msgs, srv, SetUserFrame_Response)(),
};

static rosidl_service_type_support_t SetUserFrame__handle = {
  rosidl_typesupport_fastrtps_c__identifier,
  &SetUserFrame__callbacks,
  get_service_typesupport_handle_function,
};

const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, jaka_msgs, srv, SetUserFrame)() {
  return &SetUserFrame__handle;
}

#if defined(__cplusplus)
}
#endif
