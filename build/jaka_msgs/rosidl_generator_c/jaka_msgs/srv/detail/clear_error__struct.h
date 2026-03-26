// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from jaka_msgs:srv/ClearError.idl
// generated code does not contain a copyright notice

#ifndef JAKA_MSGS__SRV__DETAIL__CLEAR_ERROR__STRUCT_H_
#define JAKA_MSGS__SRV__DETAIL__CLEAR_ERROR__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in srv/ClearError in the package jaka_msgs.
typedef struct jaka_msgs__srv__ClearError_Request
{
  bool enable;
} jaka_msgs__srv__ClearError_Request;

// Struct for a sequence of jaka_msgs__srv__ClearError_Request.
typedef struct jaka_msgs__srv__ClearError_Request__Sequence
{
  jaka_msgs__srv__ClearError_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} jaka_msgs__srv__ClearError_Request__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'message'
#include "rosidl_runtime_c/string.h"

/// Struct defined in srv/ClearError in the package jaka_msgs.
typedef struct jaka_msgs__srv__ClearError_Response
{
  int16_t ret;
  rosidl_runtime_c__String message;
} jaka_msgs__srv__ClearError_Response;

// Struct for a sequence of jaka_msgs__srv__ClearError_Response.
typedef struct jaka_msgs__srv__ClearError_Response__Sequence
{
  jaka_msgs__srv__ClearError_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} jaka_msgs__srv__ClearError_Response__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // JAKA_MSGS__SRV__DETAIL__CLEAR_ERROR__STRUCT_H_
