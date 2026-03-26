// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from jaka_msgs:srv/Move.idl
// generated code does not contain a copyright notice

#ifndef JAKA_MSGS__SRV__DETAIL__MOVE__STRUCT_H_
#define JAKA_MSGS__SRV__DETAIL__MOVE__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'pose'
// Member 'ref_joint'
#include "rosidl_runtime_c/primitives_sequence.h"

/// Struct defined in srv/Move in the package jaka_msgs.
typedef struct jaka_msgs__srv__Move_Request
{
  rosidl_runtime_c__float__Sequence pose;
  bool has_ref;
  rosidl_runtime_c__float__Sequence ref_joint;
  float mvvelo;
  float mvacc;
  float mvtime;
  float mvradii;
  int16_t coord_mode;
  int16_t index;
} jaka_msgs__srv__Move_Request;

// Struct for a sequence of jaka_msgs__srv__Move_Request.
typedef struct jaka_msgs__srv__Move_Request__Sequence
{
  jaka_msgs__srv__Move_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} jaka_msgs__srv__Move_Request__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'message'
#include "rosidl_runtime_c/string.h"

/// Struct defined in srv/Move in the package jaka_msgs.
typedef struct jaka_msgs__srv__Move_Response
{
  int16_t ret;
  rosidl_runtime_c__String message;
} jaka_msgs__srv__Move_Response;

// Struct for a sequence of jaka_msgs__srv__Move_Response.
typedef struct jaka_msgs__srv__Move_Response__Sequence
{
  jaka_msgs__srv__Move_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} jaka_msgs__srv__Move_Response__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // JAKA_MSGS__SRV__DETAIL__MOVE__STRUCT_H_
