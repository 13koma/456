// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from jaka_msgs:srv/GetIO.idl
// generated code does not contain a copyright notice

#ifndef JAKA_MSGS__SRV__DETAIL__GET_IO__STRUCT_H_
#define JAKA_MSGS__SRV__DETAIL__GET_IO__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'signal'
#include "rosidl_runtime_c/string.h"

/// Struct defined in srv/GetIO in the package jaka_msgs.
typedef struct jaka_msgs__srv__GetIO_Request
{
  rosidl_runtime_c__String signal;
  int16_t path;
  int16_t type;
  int16_t index;
} jaka_msgs__srv__GetIO_Request;

// Struct for a sequence of jaka_msgs__srv__GetIO_Request.
typedef struct jaka_msgs__srv__GetIO_Request__Sequence
{
  jaka_msgs__srv__GetIO_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} jaka_msgs__srv__GetIO_Request__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'message'
// already included above
// #include "rosidl_runtime_c/string.h"

/// Struct defined in srv/GetIO in the package jaka_msgs.
typedef struct jaka_msgs__srv__GetIO_Response
{
  float value;
  rosidl_runtime_c__String message;
} jaka_msgs__srv__GetIO_Response;

// Struct for a sequence of jaka_msgs__srv__GetIO_Response.
typedef struct jaka_msgs__srv__GetIO_Response__Sequence
{
  jaka_msgs__srv__GetIO_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} jaka_msgs__srv__GetIO_Response__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // JAKA_MSGS__SRV__DETAIL__GET_IO__STRUCT_H_
