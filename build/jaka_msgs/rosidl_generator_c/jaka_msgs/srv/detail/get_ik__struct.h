// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from jaka_msgs:srv/GetIK.idl
// generated code does not contain a copyright notice

#ifndef JAKA_MSGS__SRV__DETAIL__GET_IK__STRUCT_H_
#define JAKA_MSGS__SRV__DETAIL__GET_IK__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'ref_joint'
// Member 'cartesian_pose'
#include "rosidl_runtime_c/primitives_sequence.h"

/// Struct defined in srv/GetIK in the package jaka_msgs.
typedef struct jaka_msgs__srv__GetIK_Request
{
  rosidl_runtime_c__float__Sequence ref_joint;
  rosidl_runtime_c__float__Sequence cartesian_pose;
} jaka_msgs__srv__GetIK_Request;

// Struct for a sequence of jaka_msgs__srv__GetIK_Request.
typedef struct jaka_msgs__srv__GetIK_Request__Sequence
{
  jaka_msgs__srv__GetIK_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} jaka_msgs__srv__GetIK_Request__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'joint'
// already included above
// #include "rosidl_runtime_c/primitives_sequence.h"
// Member 'message'
#include "rosidl_runtime_c/string.h"

/// Struct defined in srv/GetIK in the package jaka_msgs.
typedef struct jaka_msgs__srv__GetIK_Response
{
  rosidl_runtime_c__float__Sequence joint;
  rosidl_runtime_c__String message;
} jaka_msgs__srv__GetIK_Response;

// Struct for a sequence of jaka_msgs__srv__GetIK_Response.
typedef struct jaka_msgs__srv__GetIK_Response__Sequence
{
  jaka_msgs__srv__GetIK_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} jaka_msgs__srv__GetIK_Response__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // JAKA_MSGS__SRV__DETAIL__GET_IK__STRUCT_H_
