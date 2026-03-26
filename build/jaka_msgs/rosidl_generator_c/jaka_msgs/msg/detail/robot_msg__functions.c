// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from jaka_msgs:msg/RobotMsg.idl
// generated code does not contain a copyright notice
#include "jaka_msgs/msg/detail/robot_msg__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


bool
jaka_msgs__msg__RobotMsg__init(jaka_msgs__msg__RobotMsg * msg)
{
  if (!msg) {
    return false;
  }
  // motion_state
  // power_state
  // servo_state
  // collision_state
  return true;
}

void
jaka_msgs__msg__RobotMsg__fini(jaka_msgs__msg__RobotMsg * msg)
{
  if (!msg) {
    return;
  }
  // motion_state
  // power_state
  // servo_state
  // collision_state
}

bool
jaka_msgs__msg__RobotMsg__are_equal(const jaka_msgs__msg__RobotMsg * lhs, const jaka_msgs__msg__RobotMsg * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // motion_state
  if (lhs->motion_state != rhs->motion_state) {
    return false;
  }
  // power_state
  if (lhs->power_state != rhs->power_state) {
    return false;
  }
  // servo_state
  if (lhs->servo_state != rhs->servo_state) {
    return false;
  }
  // collision_state
  if (lhs->collision_state != rhs->collision_state) {
    return false;
  }
  return true;
}

bool
jaka_msgs__msg__RobotMsg__copy(
  const jaka_msgs__msg__RobotMsg * input,
  jaka_msgs__msg__RobotMsg * output)
{
  if (!input || !output) {
    return false;
  }
  // motion_state
  output->motion_state = input->motion_state;
  // power_state
  output->power_state = input->power_state;
  // servo_state
  output->servo_state = input->servo_state;
  // collision_state
  output->collision_state = input->collision_state;
  return true;
}

jaka_msgs__msg__RobotMsg *
jaka_msgs__msg__RobotMsg__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  jaka_msgs__msg__RobotMsg * msg = (jaka_msgs__msg__RobotMsg *)allocator.allocate(sizeof(jaka_msgs__msg__RobotMsg), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(jaka_msgs__msg__RobotMsg));
  bool success = jaka_msgs__msg__RobotMsg__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
jaka_msgs__msg__RobotMsg__destroy(jaka_msgs__msg__RobotMsg * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    jaka_msgs__msg__RobotMsg__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
jaka_msgs__msg__RobotMsg__Sequence__init(jaka_msgs__msg__RobotMsg__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  jaka_msgs__msg__RobotMsg * data = NULL;

  if (size) {
    data = (jaka_msgs__msg__RobotMsg *)allocator.zero_allocate(size, sizeof(jaka_msgs__msg__RobotMsg), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = jaka_msgs__msg__RobotMsg__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        jaka_msgs__msg__RobotMsg__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
jaka_msgs__msg__RobotMsg__Sequence__fini(jaka_msgs__msg__RobotMsg__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      jaka_msgs__msg__RobotMsg__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

jaka_msgs__msg__RobotMsg__Sequence *
jaka_msgs__msg__RobotMsg__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  jaka_msgs__msg__RobotMsg__Sequence * array = (jaka_msgs__msg__RobotMsg__Sequence *)allocator.allocate(sizeof(jaka_msgs__msg__RobotMsg__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = jaka_msgs__msg__RobotMsg__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
jaka_msgs__msg__RobotMsg__Sequence__destroy(jaka_msgs__msg__RobotMsg__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    jaka_msgs__msg__RobotMsg__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
jaka_msgs__msg__RobotMsg__Sequence__are_equal(const jaka_msgs__msg__RobotMsg__Sequence * lhs, const jaka_msgs__msg__RobotMsg__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!jaka_msgs__msg__RobotMsg__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
jaka_msgs__msg__RobotMsg__Sequence__copy(
  const jaka_msgs__msg__RobotMsg__Sequence * input,
  jaka_msgs__msg__RobotMsg__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(jaka_msgs__msg__RobotMsg);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    jaka_msgs__msg__RobotMsg * data =
      (jaka_msgs__msg__RobotMsg *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!jaka_msgs__msg__RobotMsg__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          jaka_msgs__msg__RobotMsg__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!jaka_msgs__msg__RobotMsg__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
