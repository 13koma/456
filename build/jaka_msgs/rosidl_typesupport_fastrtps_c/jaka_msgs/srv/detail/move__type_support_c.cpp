// generated from rosidl_typesupport_fastrtps_c/resource/idl__type_support_c.cpp.em
// with input from jaka_msgs:srv/Move.idl
// generated code does not contain a copyright notice
#include "jaka_msgs/srv/detail/move__rosidl_typesupport_fastrtps_c.h"


#include <cassert>
#include <limits>
#include <string>
#include "rosidl_typesupport_fastrtps_c/identifier.h"
#include "rosidl_typesupport_fastrtps_c/wstring_conversion.hpp"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
#include "jaka_msgs/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
#include "jaka_msgs/srv/detail/move__struct.h"
#include "jaka_msgs/srv/detail/move__functions.h"
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

#include "rosidl_runtime_c/primitives_sequence.h"  // pose, ref_joint
#include "rosidl_runtime_c/primitives_sequence_functions.h"  // pose, ref_joint

// forward declare type support functions


using _Move_Request__ros_msg_type = jaka_msgs__srv__Move_Request;

static bool _Move_Request__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  const _Move_Request__ros_msg_type * ros_message = static_cast<const _Move_Request__ros_msg_type *>(untyped_ros_message);
  // Field name: pose
  {
    size_t size = ros_message->pose.size;
    auto array_ptr = ros_message->pose.data;
    cdr << static_cast<uint32_t>(size);
    cdr.serializeArray(array_ptr, size);
  }

  // Field name: has_ref
  {
    cdr << (ros_message->has_ref ? true : false);
  }

  // Field name: ref_joint
  {
    size_t size = ros_message->ref_joint.size;
    auto array_ptr = ros_message->ref_joint.data;
    cdr << static_cast<uint32_t>(size);
    cdr.serializeArray(array_ptr, size);
  }

  // Field name: mvvelo
  {
    cdr << ros_message->mvvelo;
  }

  // Field name: mvacc
  {
    cdr << ros_message->mvacc;
  }

  // Field name: mvtime
  {
    cdr << ros_message->mvtime;
  }

  // Field name: mvradii
  {
    cdr << ros_message->mvradii;
  }

  // Field name: coord_mode
  {
    cdr << ros_message->coord_mode;
  }

  // Field name: index
  {
    cdr << ros_message->index;
  }

  return true;
}

static bool _Move_Request__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  _Move_Request__ros_msg_type * ros_message = static_cast<_Move_Request__ros_msg_type *>(untyped_ros_message);
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

  // Field name: has_ref
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message->has_ref = tmp ? true : false;
  }

  // Field name: ref_joint
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

    if (ros_message->ref_joint.data) {
      rosidl_runtime_c__float__Sequence__fini(&ros_message->ref_joint);
    }
    if (!rosidl_runtime_c__float__Sequence__init(&ros_message->ref_joint, size)) {
      fprintf(stderr, "failed to create array for field 'ref_joint'");
      return false;
    }
    auto array_ptr = ros_message->ref_joint.data;
    cdr.deserializeArray(array_ptr, size);
  }

  // Field name: mvvelo
  {
    cdr >> ros_message->mvvelo;
  }

  // Field name: mvacc
  {
    cdr >> ros_message->mvacc;
  }

  // Field name: mvtime
  {
    cdr >> ros_message->mvtime;
  }

  // Field name: mvradii
  {
    cdr >> ros_message->mvradii;
  }

  // Field name: coord_mode
  {
    cdr >> ros_message->coord_mode;
  }

  // Field name: index
  {
    cdr >> ros_message->index;
  }

  return true;
}  // NOLINT(readability/fn_size)

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_jaka_msgs
size_t get_serialized_size_jaka_msgs__srv__Move_Request(
  const void * untyped_ros_message,
  size_t current_alignment)
{
  const _Move_Request__ros_msg_type * ros_message = static_cast<const _Move_Request__ros_msg_type *>(untyped_ros_message);
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
  // field.name has_ref
  {
    size_t item_size = sizeof(ros_message->has_ref);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name ref_joint
  {
    size_t array_size = ros_message->ref_joint.size;
    auto array_ptr = ros_message->ref_joint.data;
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);
    (void)array_ptr;
    size_t item_size = sizeof(array_ptr[0]);
    current_alignment += array_size * item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name mvvelo
  {
    size_t item_size = sizeof(ros_message->mvvelo);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name mvacc
  {
    size_t item_size = sizeof(ros_message->mvacc);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name mvtime
  {
    size_t item_size = sizeof(ros_message->mvtime);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name mvradii
  {
    size_t item_size = sizeof(ros_message->mvradii);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name coord_mode
  {
    size_t item_size = sizeof(ros_message->coord_mode);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name index
  {
    size_t item_size = sizeof(ros_message->index);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  return current_alignment - initial_alignment;
}

static uint32_t _Move_Request__get_serialized_size(const void * untyped_ros_message)
{
  return static_cast<uint32_t>(
    get_serialized_size_jaka_msgs__srv__Move_Request(
      untyped_ros_message, 0));
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_jaka_msgs
size_t max_serialized_size_jaka_msgs__srv__Move_Request(
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
  // member: has_ref
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }
  // member: ref_joint
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
  // member: mvvelo
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }
  // member: mvacc
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }
  // member: mvtime
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }
  // member: mvradii
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }
  // member: coord_mode
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint16_t);
    current_alignment += array_size * sizeof(uint16_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint16_t));
  }
  // member: index
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
    using DataType = jaka_msgs__srv__Move_Request;
    is_plain =
      (
      offsetof(DataType, index) +
      last_member_size
      ) == ret_val;
  }

  return ret_val;
}

static size_t _Move_Request__max_serialized_size(char & bounds_info)
{
  bool full_bounded;
  bool is_plain;
  size_t ret_val;

  ret_val = max_serialized_size_jaka_msgs__srv__Move_Request(
    full_bounded, is_plain, 0);

  bounds_info =
    is_plain ? ROSIDL_TYPESUPPORT_FASTRTPS_PLAIN_TYPE :
    full_bounded ? ROSIDL_TYPESUPPORT_FASTRTPS_BOUNDED_TYPE : ROSIDL_TYPESUPPORT_FASTRTPS_UNBOUNDED_TYPE;
  return ret_val;
}


static message_type_support_callbacks_t __callbacks_Move_Request = {
  "jaka_msgs::srv",
  "Move_Request",
  _Move_Request__cdr_serialize,
  _Move_Request__cdr_deserialize,
  _Move_Request__get_serialized_size,
  _Move_Request__max_serialized_size
};

static rosidl_message_type_support_t _Move_Request__type_support = {
  rosidl_typesupport_fastrtps_c__identifier,
  &__callbacks_Move_Request,
  get_message_typesupport_handle_function,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, jaka_msgs, srv, Move_Request)() {
  return &_Move_Request__type_support;
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
// #include "jaka_msgs/srv/detail/move__struct.h"
// already included above
// #include "jaka_msgs/srv/detail/move__functions.h"
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


using _Move_Response__ros_msg_type = jaka_msgs__srv__Move_Response;

static bool _Move_Response__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  const _Move_Response__ros_msg_type * ros_message = static_cast<const _Move_Response__ros_msg_type *>(untyped_ros_message);
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

static bool _Move_Response__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  _Move_Response__ros_msg_type * ros_message = static_cast<_Move_Response__ros_msg_type *>(untyped_ros_message);
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
size_t get_serialized_size_jaka_msgs__srv__Move_Response(
  const void * untyped_ros_message,
  size_t current_alignment)
{
  const _Move_Response__ros_msg_type * ros_message = static_cast<const _Move_Response__ros_msg_type *>(untyped_ros_message);
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

static uint32_t _Move_Response__get_serialized_size(const void * untyped_ros_message)
{
  return static_cast<uint32_t>(
    get_serialized_size_jaka_msgs__srv__Move_Response(
      untyped_ros_message, 0));
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_jaka_msgs
size_t max_serialized_size_jaka_msgs__srv__Move_Response(
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
    using DataType = jaka_msgs__srv__Move_Response;
    is_plain =
      (
      offsetof(DataType, message) +
      last_member_size
      ) == ret_val;
  }

  return ret_val;
}

static size_t _Move_Response__max_serialized_size(char & bounds_info)
{
  bool full_bounded;
  bool is_plain;
  size_t ret_val;

  ret_val = max_serialized_size_jaka_msgs__srv__Move_Response(
    full_bounded, is_plain, 0);

  bounds_info =
    is_plain ? ROSIDL_TYPESUPPORT_FASTRTPS_PLAIN_TYPE :
    full_bounded ? ROSIDL_TYPESUPPORT_FASTRTPS_BOUNDED_TYPE : ROSIDL_TYPESUPPORT_FASTRTPS_UNBOUNDED_TYPE;
  return ret_val;
}


static message_type_support_callbacks_t __callbacks_Move_Response = {
  "jaka_msgs::srv",
  "Move_Response",
  _Move_Response__cdr_serialize,
  _Move_Response__cdr_deserialize,
  _Move_Response__get_serialized_size,
  _Move_Response__max_serialized_size
};

static rosidl_message_type_support_t _Move_Response__type_support = {
  rosidl_typesupport_fastrtps_c__identifier,
  &__callbacks_Move_Response,
  get_message_typesupport_handle_function,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, jaka_msgs, srv, Move_Response)() {
  return &_Move_Response__type_support;
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
#include "jaka_msgs/srv/move.h"

#if defined(__cplusplus)
extern "C"
{
#endif

static service_type_support_callbacks_t Move__callbacks = {
  "jaka_msgs::srv",
  "Move",
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, jaka_msgs, srv, Move_Request)(),
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, jaka_msgs, srv, Move_Response)(),
};

static rosidl_service_type_support_t Move__handle = {
  rosidl_typesupport_fastrtps_c__identifier,
  &Move__callbacks,
  get_service_typesupport_handle_function,
};

const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, jaka_msgs, srv, Move)() {
  return &Move__handle;
}

#if defined(__cplusplus)
}
#endif
