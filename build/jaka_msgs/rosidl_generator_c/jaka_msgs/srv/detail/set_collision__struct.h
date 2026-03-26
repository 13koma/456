// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from jaka_msgs:srv/SetCollision.idl
// generated code does not contain a copyright notice

#ifndef JAKA_MSGS__SRV__DETAIL__SET_COLLISION__STRUCT_H_
#define JAKA_MSGS__SRV__DETAIL__SET_COLLISION__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in srv/SetCollision in the package jaka_msgs.
typedef struct jaka_msgs__srv__SetCollision_Request
{
  bool is_enable;
  int16_t value;
} jaka_msgs__srv__SetCollision_Request;

// Struct for a sequence of jaka_msgs__srv__SetCollision_Request.
typedef struct jaka_msgs__srv__SetCollision_Request__Sequence
{
  jaka_msgs__srv__SetCollision_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} jaka_msgs__srv__SetCollision_Request__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'message'
#include "rosidl_runtime_c/string.h"

/// Struct defined in srv/SetCollision in the package jaka_msgs.
typedef struct jaka_msgs__srv__SetCollision_Response
{
  int16_t ret;
  rosidl_runtime_c__String message;
} jaka_msgs__srv__SetCollision_Response;

// Struct for a sequence of jaka_msgs__srv__SetCollision_Response.
typedef struct jaka_msgs__srv__SetCollision_Response__Sequence
{
  jaka_msgs__srv__SetCollision_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} jaka_msgs__srv__SetCollision_Response__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // JAKA_MSGS__SRV__DETAIL__SET_COLLISION__STRUCT_H_
