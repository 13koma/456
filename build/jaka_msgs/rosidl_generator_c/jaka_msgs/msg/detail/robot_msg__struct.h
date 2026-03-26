// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from jaka_msgs:msg/RobotMsg.idl
// generated code does not contain a copyright notice

#ifndef JAKA_MSGS__MSG__DETAIL__ROBOT_MSG__STRUCT_H_
#define JAKA_MSGS__MSG__DETAIL__ROBOT_MSG__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in msg/RobotMsg in the package jaka_msgs.
typedef struct jaka_msgs__msg__RobotMsg
{
  int16_t motion_state;
  int16_t power_state;
  int16_t servo_state;
  int16_t collision_state;
} jaka_msgs__msg__RobotMsg;

// Struct for a sequence of jaka_msgs__msg__RobotMsg.
typedef struct jaka_msgs__msg__RobotMsg__Sequence
{
  jaka_msgs__msg__RobotMsg * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} jaka_msgs__msg__RobotMsg__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // JAKA_MSGS__MSG__DETAIL__ROBOT_MSG__STRUCT_H_
