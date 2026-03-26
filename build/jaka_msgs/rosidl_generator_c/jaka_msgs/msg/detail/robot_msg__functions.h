// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from jaka_msgs:msg/RobotMsg.idl
// generated code does not contain a copyright notice

#ifndef JAKA_MSGS__MSG__DETAIL__ROBOT_MSG__FUNCTIONS_H_
#define JAKA_MSGS__MSG__DETAIL__ROBOT_MSG__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/visibility_control.h"
#include "jaka_msgs/msg/rosidl_generator_c__visibility_control.h"

#include "jaka_msgs/msg/detail/robot_msg__struct.h"

/// Initialize msg/RobotMsg message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * jaka_msgs__msg__RobotMsg
 * )) before or use
 * jaka_msgs__msg__RobotMsg__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_jaka_msgs
bool
jaka_msgs__msg__RobotMsg__init(jaka_msgs__msg__RobotMsg * msg);

/// Finalize msg/RobotMsg message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_jaka_msgs
void
jaka_msgs__msg__RobotMsg__fini(jaka_msgs__msg__RobotMsg * msg);

/// Create msg/RobotMsg message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * jaka_msgs__msg__RobotMsg__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_jaka_msgs
jaka_msgs__msg__RobotMsg *
jaka_msgs__msg__RobotMsg__create();

/// Destroy msg/RobotMsg message.
/**
 * It calls
 * jaka_msgs__msg__RobotMsg__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_jaka_msgs
void
jaka_msgs__msg__RobotMsg__destroy(jaka_msgs__msg__RobotMsg * msg);

/// Check for msg/RobotMsg message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_jaka_msgs
bool
jaka_msgs__msg__RobotMsg__are_equal(const jaka_msgs__msg__RobotMsg * lhs, const jaka_msgs__msg__RobotMsg * rhs);

/// Copy a msg/RobotMsg message.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source message pointer.
 * \param[out] output The target message pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer is null
 *   or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_jaka_msgs
bool
jaka_msgs__msg__RobotMsg__copy(
  const jaka_msgs__msg__RobotMsg * input,
  jaka_msgs__msg__RobotMsg * output);

/// Initialize array of msg/RobotMsg messages.
/**
 * It allocates the memory for the number of elements and calls
 * jaka_msgs__msg__RobotMsg__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_jaka_msgs
bool
jaka_msgs__msg__RobotMsg__Sequence__init(jaka_msgs__msg__RobotMsg__Sequence * array, size_t size);

/// Finalize array of msg/RobotMsg messages.
/**
 * It calls
 * jaka_msgs__msg__RobotMsg__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_jaka_msgs
void
jaka_msgs__msg__RobotMsg__Sequence__fini(jaka_msgs__msg__RobotMsg__Sequence * array);

/// Create array of msg/RobotMsg messages.
/**
 * It allocates the memory for the array and calls
 * jaka_msgs__msg__RobotMsg__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_jaka_msgs
jaka_msgs__msg__RobotMsg__Sequence *
jaka_msgs__msg__RobotMsg__Sequence__create(size_t size);

/// Destroy array of msg/RobotMsg messages.
/**
 * It calls
 * jaka_msgs__msg__RobotMsg__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_jaka_msgs
void
jaka_msgs__msg__RobotMsg__Sequence__destroy(jaka_msgs__msg__RobotMsg__Sequence * array);

/// Check for msg/RobotMsg message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_jaka_msgs
bool
jaka_msgs__msg__RobotMsg__Sequence__are_equal(const jaka_msgs__msg__RobotMsg__Sequence * lhs, const jaka_msgs__msg__RobotMsg__Sequence * rhs);

/// Copy an array of msg/RobotMsg messages.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source array pointer.
 * \param[out] output The target array pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer
 *   is null or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_jaka_msgs
bool
jaka_msgs__msg__RobotMsg__Sequence__copy(
  const jaka_msgs__msg__RobotMsg__Sequence * input,
  jaka_msgs__msg__RobotMsg__Sequence * output);

#ifdef __cplusplus
}
#endif

#endif  // JAKA_MSGS__MSG__DETAIL__ROBOT_MSG__FUNCTIONS_H_
