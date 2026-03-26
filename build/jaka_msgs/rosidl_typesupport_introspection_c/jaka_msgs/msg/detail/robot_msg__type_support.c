// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from jaka_msgs:msg/RobotMsg.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "jaka_msgs/msg/detail/robot_msg__rosidl_typesupport_introspection_c.h"
#include "jaka_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "jaka_msgs/msg/detail/robot_msg__functions.h"
#include "jaka_msgs/msg/detail/robot_msg__struct.h"


#ifdef __cplusplus
extern "C"
{
#endif

void jaka_msgs__msg__RobotMsg__rosidl_typesupport_introspection_c__RobotMsg_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  jaka_msgs__msg__RobotMsg__init(message_memory);
}

void jaka_msgs__msg__RobotMsg__rosidl_typesupport_introspection_c__RobotMsg_fini_function(void * message_memory)
{
  jaka_msgs__msg__RobotMsg__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember jaka_msgs__msg__RobotMsg__rosidl_typesupport_introspection_c__RobotMsg_message_member_array[4] = {
  {
    "motion_state",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT16,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(jaka_msgs__msg__RobotMsg, motion_state),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "power_state",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT16,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(jaka_msgs__msg__RobotMsg, power_state),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "servo_state",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT16,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(jaka_msgs__msg__RobotMsg, servo_state),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "collision_state",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT16,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(jaka_msgs__msg__RobotMsg, collision_state),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers jaka_msgs__msg__RobotMsg__rosidl_typesupport_introspection_c__RobotMsg_message_members = {
  "jaka_msgs__msg",  // message namespace
  "RobotMsg",  // message name
  4,  // number of fields
  sizeof(jaka_msgs__msg__RobotMsg),
  jaka_msgs__msg__RobotMsg__rosidl_typesupport_introspection_c__RobotMsg_message_member_array,  // message members
  jaka_msgs__msg__RobotMsg__rosidl_typesupport_introspection_c__RobotMsg_init_function,  // function to initialize message memory (memory has to be allocated)
  jaka_msgs__msg__RobotMsg__rosidl_typesupport_introspection_c__RobotMsg_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t jaka_msgs__msg__RobotMsg__rosidl_typesupport_introspection_c__RobotMsg_message_type_support_handle = {
  0,
  &jaka_msgs__msg__RobotMsg__rosidl_typesupport_introspection_c__RobotMsg_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_jaka_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, jaka_msgs, msg, RobotMsg)() {
  if (!jaka_msgs__msg__RobotMsg__rosidl_typesupport_introspection_c__RobotMsg_message_type_support_handle.typesupport_identifier) {
    jaka_msgs__msg__RobotMsg__rosidl_typesupport_introspection_c__RobotMsg_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &jaka_msgs__msg__RobotMsg__rosidl_typesupport_introspection_c__RobotMsg_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
