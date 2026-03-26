// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from jaka_msgs:srv/GetFK.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "jaka_msgs/srv/detail/get_fk__rosidl_typesupport_introspection_c.h"
#include "jaka_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "jaka_msgs/srv/detail/get_fk__functions.h"
#include "jaka_msgs/srv/detail/get_fk__struct.h"


// Include directives for member types
// Member `joint`
#include "rosidl_runtime_c/primitives_sequence_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void jaka_msgs__srv__GetFK_Request__rosidl_typesupport_introspection_c__GetFK_Request_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  jaka_msgs__srv__GetFK_Request__init(message_memory);
}

void jaka_msgs__srv__GetFK_Request__rosidl_typesupport_introspection_c__GetFK_Request_fini_function(void * message_memory)
{
  jaka_msgs__srv__GetFK_Request__fini(message_memory);
}

size_t jaka_msgs__srv__GetFK_Request__rosidl_typesupport_introspection_c__size_function__GetFK_Request__joint(
  const void * untyped_member)
{
  const rosidl_runtime_c__float__Sequence * member =
    (const rosidl_runtime_c__float__Sequence *)(untyped_member);
  return member->size;
}

const void * jaka_msgs__srv__GetFK_Request__rosidl_typesupport_introspection_c__get_const_function__GetFK_Request__joint(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__float__Sequence * member =
    (const rosidl_runtime_c__float__Sequence *)(untyped_member);
  return &member->data[index];
}

void * jaka_msgs__srv__GetFK_Request__rosidl_typesupport_introspection_c__get_function__GetFK_Request__joint(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__float__Sequence * member =
    (rosidl_runtime_c__float__Sequence *)(untyped_member);
  return &member->data[index];
}

void jaka_msgs__srv__GetFK_Request__rosidl_typesupport_introspection_c__fetch_function__GetFK_Request__joint(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const float * item =
    ((const float *)
    jaka_msgs__srv__GetFK_Request__rosidl_typesupport_introspection_c__get_const_function__GetFK_Request__joint(untyped_member, index));
  float * value =
    (float *)(untyped_value);
  *value = *item;
}

void jaka_msgs__srv__GetFK_Request__rosidl_typesupport_introspection_c__assign_function__GetFK_Request__joint(
  void * untyped_member, size_t index, const void * untyped_value)
{
  float * item =
    ((float *)
    jaka_msgs__srv__GetFK_Request__rosidl_typesupport_introspection_c__get_function__GetFK_Request__joint(untyped_member, index));
  const float * value =
    (const float *)(untyped_value);
  *item = *value;
}

bool jaka_msgs__srv__GetFK_Request__rosidl_typesupport_introspection_c__resize_function__GetFK_Request__joint(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__float__Sequence * member =
    (rosidl_runtime_c__float__Sequence *)(untyped_member);
  rosidl_runtime_c__float__Sequence__fini(member);
  return rosidl_runtime_c__float__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember jaka_msgs__srv__GetFK_Request__rosidl_typesupport_introspection_c__GetFK_Request_message_member_array[1] = {
  {
    "joint",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(jaka_msgs__srv__GetFK_Request, joint),  // bytes offset in struct
    NULL,  // default value
    jaka_msgs__srv__GetFK_Request__rosidl_typesupport_introspection_c__size_function__GetFK_Request__joint,  // size() function pointer
    jaka_msgs__srv__GetFK_Request__rosidl_typesupport_introspection_c__get_const_function__GetFK_Request__joint,  // get_const(index) function pointer
    jaka_msgs__srv__GetFK_Request__rosidl_typesupport_introspection_c__get_function__GetFK_Request__joint,  // get(index) function pointer
    jaka_msgs__srv__GetFK_Request__rosidl_typesupport_introspection_c__fetch_function__GetFK_Request__joint,  // fetch(index, &value) function pointer
    jaka_msgs__srv__GetFK_Request__rosidl_typesupport_introspection_c__assign_function__GetFK_Request__joint,  // assign(index, value) function pointer
    jaka_msgs__srv__GetFK_Request__rosidl_typesupport_introspection_c__resize_function__GetFK_Request__joint  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers jaka_msgs__srv__GetFK_Request__rosidl_typesupport_introspection_c__GetFK_Request_message_members = {
  "jaka_msgs__srv",  // message namespace
  "GetFK_Request",  // message name
  1,  // number of fields
  sizeof(jaka_msgs__srv__GetFK_Request),
  jaka_msgs__srv__GetFK_Request__rosidl_typesupport_introspection_c__GetFK_Request_message_member_array,  // message members
  jaka_msgs__srv__GetFK_Request__rosidl_typesupport_introspection_c__GetFK_Request_init_function,  // function to initialize message memory (memory has to be allocated)
  jaka_msgs__srv__GetFK_Request__rosidl_typesupport_introspection_c__GetFK_Request_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t jaka_msgs__srv__GetFK_Request__rosidl_typesupport_introspection_c__GetFK_Request_message_type_support_handle = {
  0,
  &jaka_msgs__srv__GetFK_Request__rosidl_typesupport_introspection_c__GetFK_Request_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_jaka_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, jaka_msgs, srv, GetFK_Request)() {
  if (!jaka_msgs__srv__GetFK_Request__rosidl_typesupport_introspection_c__GetFK_Request_message_type_support_handle.typesupport_identifier) {
    jaka_msgs__srv__GetFK_Request__rosidl_typesupport_introspection_c__GetFK_Request_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &jaka_msgs__srv__GetFK_Request__rosidl_typesupport_introspection_c__GetFK_Request_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include <stddef.h>
// already included above
// #include "jaka_msgs/srv/detail/get_fk__rosidl_typesupport_introspection_c.h"
// already included above
// #include "jaka_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "jaka_msgs/srv/detail/get_fk__functions.h"
// already included above
// #include "jaka_msgs/srv/detail/get_fk__struct.h"


// Include directives for member types
// Member `cartesian_pose`
// already included above
// #include "rosidl_runtime_c/primitives_sequence_functions.h"
// Member `message`
#include "rosidl_runtime_c/string_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void jaka_msgs__srv__GetFK_Response__rosidl_typesupport_introspection_c__GetFK_Response_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  jaka_msgs__srv__GetFK_Response__init(message_memory);
}

void jaka_msgs__srv__GetFK_Response__rosidl_typesupport_introspection_c__GetFK_Response_fini_function(void * message_memory)
{
  jaka_msgs__srv__GetFK_Response__fini(message_memory);
}

size_t jaka_msgs__srv__GetFK_Response__rosidl_typesupport_introspection_c__size_function__GetFK_Response__cartesian_pose(
  const void * untyped_member)
{
  const rosidl_runtime_c__float__Sequence * member =
    (const rosidl_runtime_c__float__Sequence *)(untyped_member);
  return member->size;
}

const void * jaka_msgs__srv__GetFK_Response__rosidl_typesupport_introspection_c__get_const_function__GetFK_Response__cartesian_pose(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__float__Sequence * member =
    (const rosidl_runtime_c__float__Sequence *)(untyped_member);
  return &member->data[index];
}

void * jaka_msgs__srv__GetFK_Response__rosidl_typesupport_introspection_c__get_function__GetFK_Response__cartesian_pose(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__float__Sequence * member =
    (rosidl_runtime_c__float__Sequence *)(untyped_member);
  return &member->data[index];
}

void jaka_msgs__srv__GetFK_Response__rosidl_typesupport_introspection_c__fetch_function__GetFK_Response__cartesian_pose(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const float * item =
    ((const float *)
    jaka_msgs__srv__GetFK_Response__rosidl_typesupport_introspection_c__get_const_function__GetFK_Response__cartesian_pose(untyped_member, index));
  float * value =
    (float *)(untyped_value);
  *value = *item;
}

void jaka_msgs__srv__GetFK_Response__rosidl_typesupport_introspection_c__assign_function__GetFK_Response__cartesian_pose(
  void * untyped_member, size_t index, const void * untyped_value)
{
  float * item =
    ((float *)
    jaka_msgs__srv__GetFK_Response__rosidl_typesupport_introspection_c__get_function__GetFK_Response__cartesian_pose(untyped_member, index));
  const float * value =
    (const float *)(untyped_value);
  *item = *value;
}

bool jaka_msgs__srv__GetFK_Response__rosidl_typesupport_introspection_c__resize_function__GetFK_Response__cartesian_pose(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__float__Sequence * member =
    (rosidl_runtime_c__float__Sequence *)(untyped_member);
  rosidl_runtime_c__float__Sequence__fini(member);
  return rosidl_runtime_c__float__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember jaka_msgs__srv__GetFK_Response__rosidl_typesupport_introspection_c__GetFK_Response_message_member_array[2] = {
  {
    "cartesian_pose",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(jaka_msgs__srv__GetFK_Response, cartesian_pose),  // bytes offset in struct
    NULL,  // default value
    jaka_msgs__srv__GetFK_Response__rosidl_typesupport_introspection_c__size_function__GetFK_Response__cartesian_pose,  // size() function pointer
    jaka_msgs__srv__GetFK_Response__rosidl_typesupport_introspection_c__get_const_function__GetFK_Response__cartesian_pose,  // get_const(index) function pointer
    jaka_msgs__srv__GetFK_Response__rosidl_typesupport_introspection_c__get_function__GetFK_Response__cartesian_pose,  // get(index) function pointer
    jaka_msgs__srv__GetFK_Response__rosidl_typesupport_introspection_c__fetch_function__GetFK_Response__cartesian_pose,  // fetch(index, &value) function pointer
    jaka_msgs__srv__GetFK_Response__rosidl_typesupport_introspection_c__assign_function__GetFK_Response__cartesian_pose,  // assign(index, value) function pointer
    jaka_msgs__srv__GetFK_Response__rosidl_typesupport_introspection_c__resize_function__GetFK_Response__cartesian_pose  // resize(index) function pointer
  },
  {
    "message",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(jaka_msgs__srv__GetFK_Response, message),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers jaka_msgs__srv__GetFK_Response__rosidl_typesupport_introspection_c__GetFK_Response_message_members = {
  "jaka_msgs__srv",  // message namespace
  "GetFK_Response",  // message name
  2,  // number of fields
  sizeof(jaka_msgs__srv__GetFK_Response),
  jaka_msgs__srv__GetFK_Response__rosidl_typesupport_introspection_c__GetFK_Response_message_member_array,  // message members
  jaka_msgs__srv__GetFK_Response__rosidl_typesupport_introspection_c__GetFK_Response_init_function,  // function to initialize message memory (memory has to be allocated)
  jaka_msgs__srv__GetFK_Response__rosidl_typesupport_introspection_c__GetFK_Response_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t jaka_msgs__srv__GetFK_Response__rosidl_typesupport_introspection_c__GetFK_Response_message_type_support_handle = {
  0,
  &jaka_msgs__srv__GetFK_Response__rosidl_typesupport_introspection_c__GetFK_Response_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_jaka_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, jaka_msgs, srv, GetFK_Response)() {
  if (!jaka_msgs__srv__GetFK_Response__rosidl_typesupport_introspection_c__GetFK_Response_message_type_support_handle.typesupport_identifier) {
    jaka_msgs__srv__GetFK_Response__rosidl_typesupport_introspection_c__GetFK_Response_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &jaka_msgs__srv__GetFK_Response__rosidl_typesupport_introspection_c__GetFK_Response_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

#include "rosidl_runtime_c/service_type_support_struct.h"
// already included above
// #include "jaka_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "jaka_msgs/srv/detail/get_fk__rosidl_typesupport_introspection_c.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/service_introspection.h"

// this is intentionally not const to allow initialization later to prevent an initialization race
static rosidl_typesupport_introspection_c__ServiceMembers jaka_msgs__srv__detail__get_fk__rosidl_typesupport_introspection_c__GetFK_service_members = {
  "jaka_msgs__srv",  // service namespace
  "GetFK",  // service name
  // these two fields are initialized below on the first access
  NULL,  // request message
  // jaka_msgs__srv__detail__get_fk__rosidl_typesupport_introspection_c__GetFK_Request_message_type_support_handle,
  NULL  // response message
  // jaka_msgs__srv__detail__get_fk__rosidl_typesupport_introspection_c__GetFK_Response_message_type_support_handle
};

static rosidl_service_type_support_t jaka_msgs__srv__detail__get_fk__rosidl_typesupport_introspection_c__GetFK_service_type_support_handle = {
  0,
  &jaka_msgs__srv__detail__get_fk__rosidl_typesupport_introspection_c__GetFK_service_members,
  get_service_typesupport_handle_function,
};

// Forward declaration of request/response type support functions
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, jaka_msgs, srv, GetFK_Request)();

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, jaka_msgs, srv, GetFK_Response)();

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_jaka_msgs
const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_c, jaka_msgs, srv, GetFK)() {
  if (!jaka_msgs__srv__detail__get_fk__rosidl_typesupport_introspection_c__GetFK_service_type_support_handle.typesupport_identifier) {
    jaka_msgs__srv__detail__get_fk__rosidl_typesupport_introspection_c__GetFK_service_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  rosidl_typesupport_introspection_c__ServiceMembers * service_members =
    (rosidl_typesupport_introspection_c__ServiceMembers *)jaka_msgs__srv__detail__get_fk__rosidl_typesupport_introspection_c__GetFK_service_type_support_handle.data;

  if (!service_members->request_members_) {
    service_members->request_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, jaka_msgs, srv, GetFK_Request)()->data;
  }
  if (!service_members->response_members_) {
    service_members->response_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, jaka_msgs, srv, GetFK_Response)()->data;
  }

  return &jaka_msgs__srv__detail__get_fk__rosidl_typesupport_introspection_c__GetFK_service_type_support_handle;
}
