// generated from rosidl_typesupport_fastrtps_c/resource/idl__type_support_c.cpp.em
// with input from jaka_msgs:srv/GetFK.idl
// generated code does not contain a copyright notice
#include "jaka_msgs/srv/detail/get_fk__rosidl_typesupport_fastrtps_c.h"


#include <cassert>
#include <limits>
#include <string>
#include "rosidl_typesupport_fastrtps_c/identifier.h"
#include "rosidl_typesupport_fastrtps_c/wstring_conversion.hpp"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
#include "jaka_msgs/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
#include "jaka_msgs/srv/detail/get_fk__struct.h"
#include "jaka_msgs/srv/detail/get_fk__functions.h"
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

#include "rosidl_runtime_c/primitives_sequence.h"  // joint
#include "rosidl_runtime_c/primitives_sequence_functions.h"  // joint

// forward declare type support functions


using _GetFK_Request__ros_msg_type = jaka_msgs__srv__GetFK_Request;

static bool _GetFK_Request__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  const _GetFK_Request__ros_msg_type * ros_message = static_cast<const _GetFK_Request__ros_msg_type *>(untyped_ros_message);
  // Field name: joint
  {
    size_t size = ros_message->joint.size;
    auto array_ptr = ros_message->joint.data;
    cdr << static_cast<uint32_t>(size);
    cdr.serializeArray(array_ptr, size);
  }

  return true;
}

static bool _GetFK_Request__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  _GetFK_Request__ros_msg_type * ros_message = static_cast<_GetFK_Request__ros_msg_type *>(untyped_ros_message);
  // Field name: joint
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

    if (ros_message->joint.data) {
      rosidl_runtime_c__float__Sequence__fini(&ros_message->joint);
    }
    if (!rosidl_runtime_c__float__Sequence__init(&ros_message->joint, size)) {
      fprintf(stderr, "failed to create array for field 'joint'");
      return false;
    }
    auto array_ptr = ros_message->joint.data;
    cdr.deserializeArray(array_ptr, size);
  }

  return true;
}  // NOLINT(readability/fn_size)

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_jaka_msgs
size_t get_serialized_size_jaka_msgs__srv__GetFK_Request(
  const void * untyped_ros_message,
  size_t current_alignment)
{
  const _GetFK_Request__ros_msg_type * ros_message = static_cast<const _GetFK_Request__ros_msg_type *>(untyped_ros_message);
  (void)ros_message;
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // field.name joint
  {
    size_t array_size = ros_message->joint.size;
    auto array_ptr = ros_message->joint.data;
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);
    (void)array_ptr;
    size_t item_size = sizeof(array_ptr[0]);
    current_alignment += array_size * item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  return current_alignment - initial_alignment;
}

static uint32_t _GetFK_Request__get_serialized_size(const void * untyped_ros_message)
{
  return static_cast<uint32_t>(
    get_serialized_size_jaka_msgs__srv__GetFK_Request(
      untyped_ros_message, 0));
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_jaka_msgs
size_t max_serialized_size_jaka_msgs__srv__GetFK_Request(
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

  // member: joint
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

  size_t ret_val = current_alignment - initial_alignment;
  if (is_plain) {
    // All members are plain, and type is not empty.
    // We still need to check that the in-memory alignment
    // is the same as the CDR mandated alignment.
    using DataType = jaka_msgs__srv__GetFK_Request;
    is_plain =
      (
      offsetof(DataType, joint) +
      last_member_size
      ) == ret_val;
  }

  return ret_val;
}

static size_t _GetFK_Request__max_serialized_size(char & bounds_info)
{
  bool full_bounded;
  bool is_plain;
  size_t ret_val;

  ret_val = max_serialized_size_jaka_msgs__srv__GetFK_Request(
    full_bounded, is_plain, 0);

  bounds_info =
    is_plain ? ROSIDL_TYPESUPPORT_FASTRTPS_PLAIN_TYPE :
    full_bounded ? ROSIDL_TYPESUPPORT_FASTRTPS_BOUNDED_TYPE : ROSIDL_TYPESUPPORT_FASTRTPS_UNBOUNDED_TYPE;
  return ret_val;
}


static message_type_support_callbacks_t __callbacks_GetFK_Request = {
  "jaka_msgs::srv",
  "GetFK_Request",
  _GetFK_Request__cdr_serialize,
  _GetFK_Request__cdr_deserialize,
  _GetFK_Request__get_serialized_size,
  _GetFK_Request__max_serialized_size
};

static rosidl_message_type_support_t _GetFK_Request__type_support = {
  rosidl_typesupport_fastrtps_c__identifier,
  &__callbacks_GetFK_Request,
  get_message_typesupport_handle_function,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, jaka_msgs, srv, GetFK_Request)() {
  return &_GetFK_Request__type_support;
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
// #include "jaka_msgs/srv/detail/get_fk__struct.h"
// already included above
// #include "jaka_msgs/srv/detail/get_fk__functions.h"
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

// already included above
// #include "rosidl_runtime_c/primitives_sequence.h"  // cartesian_pose
// already included above
// #include "rosidl_runtime_c/primitives_sequence_functions.h"  // cartesian_pose
#include "rosidl_runtime_c/string.h"  // message
#include "rosidl_runtime_c/string_functions.h"  // message

// forward declare type support functions


using _GetFK_Response__ros_msg_type = jaka_msgs__srv__GetFK_Response;

static bool _GetFK_Response__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  const _GetFK_Response__ros_msg_type * ros_message = static_cast<const _GetFK_Response__ros_msg_type *>(untyped_ros_message);
  // Field name: cartesian_pose
  {
    size_t size = ros_message->cartesian_pose.size;
    auto array_ptr = ros_message->cartesian_pose.data;
    cdr << static_cast<uint32_t>(size);
    cdr.serializeArray(array_ptr, size);
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

static bool _GetFK_Response__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  _GetFK_Response__ros_msg_type * ros_message = static_cast<_GetFK_Response__ros_msg_type *>(untyped_ros_message);
  // Field name: cartesian_pose
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

    if (ros_message->cartesian_pose.data) {
      rosidl_runtime_c__float__Sequence__fini(&ros_message->cartesian_pose);
    }
    if (!rosidl_runtime_c__float__Sequence__init(&ros_message->cartesian_pose, size)) {
      fprintf(stderr, "failed to create array for field 'cartesian_pose'");
      return false;
    }
    auto array_ptr = ros_message->cartesian_pose.data;
    cdr.deserializeArray(array_ptr, size);
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
size_t get_serialized_size_jaka_msgs__srv__GetFK_Response(
  const void * untyped_ros_message,
  size_t current_alignment)
{
  const _GetFK_Response__ros_msg_type * ros_message = static_cast<const _GetFK_Response__ros_msg_type *>(untyped_ros_message);
  (void)ros_message;
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // field.name cartesian_pose
  {
    size_t array_size = ros_message->cartesian_pose.size;
    auto array_ptr = ros_message->cartesian_pose.data;
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);
    (void)array_ptr;
    size_t item_size = sizeof(array_ptr[0]);
    current_alignment += array_size * item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name message
  current_alignment += padding +
    eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
    (ros_message->message.size + 1);

  return current_alignment - initial_alignment;
}

static uint32_t _GetFK_Response__get_serialized_size(const void * untyped_ros_message)
{
  return static_cast<uint32_t>(
    get_serialized_size_jaka_msgs__srv__GetFK_Response(
      untyped_ros_message, 0));
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_jaka_msgs
size_t max_serialized_size_jaka_msgs__srv__GetFK_Response(
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

  // member: cartesian_pose
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
    using DataType = jaka_msgs__srv__GetFK_Response;
    is_plain =
      (
      offsetof(DataType, message) +
      last_member_size
      ) == ret_val;
  }

  return ret_val;
}

static size_t _GetFK_Response__max_serialized_size(char & bounds_info)
{
  bool full_bounded;
  bool is_plain;
  size_t ret_val;

  ret_val = max_serialized_size_jaka_msgs__srv__GetFK_Response(
    full_bounded, is_plain, 0);

  bounds_info =
    is_plain ? ROSIDL_TYPESUPPORT_FASTRTPS_PLAIN_TYPE :
    full_bounded ? ROSIDL_TYPESUPPORT_FASTRTPS_BOUNDED_TYPE : ROSIDL_TYPESUPPORT_FASTRTPS_UNBOUNDED_TYPE;
  return ret_val;
}


static message_type_support_callbacks_t __callbacks_GetFK_Response = {
  "jaka_msgs::srv",
  "GetFK_Response",
  _GetFK_Response__cdr_serialize,
  _GetFK_Response__cdr_deserialize,
  _GetFK_Response__get_serialized_size,
  _GetFK_Response__max_serialized_size
};

static rosidl_message_type_support_t _GetFK_Response__type_support = {
  rosidl_typesupport_fastrtps_c__identifier,
  &__callbacks_GetFK_Response,
  get_message_typesupport_handle_function,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, jaka_msgs, srv, GetFK_Response)() {
  return &_GetFK_Response__type_support;
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
#include "jaka_msgs/srv/get_fk.h"

#if defined(__cplusplus)
extern "C"
{
#endif

static service_type_support_callbacks_t GetFK__callbacks = {
  "jaka_msgs::srv",
  "GetFK",
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, jaka_msgs, srv, GetFK_Request)(),
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, jaka_msgs, srv, GetFK_Response)(),
};

static rosidl_service_type_support_t GetFK__handle = {
  rosidl_typesupport_fastrtps_c__identifier,
  &GetFK__callbacks,
  get_service_typesupport_handle_function,
};

const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, jaka_msgs, srv, GetFK)() {
  return &GetFK__handle;
}

#if defined(__cplusplus)
}
#endif
