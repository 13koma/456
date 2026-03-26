// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from jaka_msgs:srv/Move.idl
// generated code does not contain a copyright notice
#include "jaka_msgs/srv/detail/move__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"

// Include directives for member types
// Member `pose`
// Member `ref_joint`
#include "rosidl_runtime_c/primitives_sequence_functions.h"

bool
jaka_msgs__srv__Move_Request__init(jaka_msgs__srv__Move_Request * msg)
{
  if (!msg) {
    return false;
  }
  // pose
  if (!rosidl_runtime_c__float__Sequence__init(&msg->pose, 0)) {
    jaka_msgs__srv__Move_Request__fini(msg);
    return false;
  }
  // has_ref
  // ref_joint
  if (!rosidl_runtime_c__float__Sequence__init(&msg->ref_joint, 0)) {
    jaka_msgs__srv__Move_Request__fini(msg);
    return false;
  }
  // mvvelo
  // mvacc
  // mvtime
  // mvradii
  // coord_mode
  // index
  return true;
}

void
jaka_msgs__srv__Move_Request__fini(jaka_msgs__srv__Move_Request * msg)
{
  if (!msg) {
    return;
  }
  // pose
  rosidl_runtime_c__float__Sequence__fini(&msg->pose);
  // has_ref
  // ref_joint
  rosidl_runtime_c__float__Sequence__fini(&msg->ref_joint);
  // mvvelo
  // mvacc
  // mvtime
  // mvradii
  // coord_mode
  // index
}

bool
jaka_msgs__srv__Move_Request__are_equal(const jaka_msgs__srv__Move_Request * lhs, const jaka_msgs__srv__Move_Request * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // pose
  if (!rosidl_runtime_c__float__Sequence__are_equal(
      &(lhs->pose), &(rhs->pose)))
  {
    return false;
  }
  // has_ref
  if (lhs->has_ref != rhs->has_ref) {
    return false;
  }
  // ref_joint
  if (!rosidl_runtime_c__float__Sequence__are_equal(
      &(lhs->ref_joint), &(rhs->ref_joint)))
  {
    return false;
  }
  // mvvelo
  if (lhs->mvvelo != rhs->mvvelo) {
    return false;
  }
  // mvacc
  if (lhs->mvacc != rhs->mvacc) {
    return false;
  }
  // mvtime
  if (lhs->mvtime != rhs->mvtime) {
    return false;
  }
  // mvradii
  if (lhs->mvradii != rhs->mvradii) {
    return false;
  }
  // coord_mode
  if (lhs->coord_mode != rhs->coord_mode) {
    return false;
  }
  // index
  if (lhs->index != rhs->index) {
    return false;
  }
  return true;
}

bool
jaka_msgs__srv__Move_Request__copy(
  const jaka_msgs__srv__Move_Request * input,
  jaka_msgs__srv__Move_Request * output)
{
  if (!input || !output) {
    return false;
  }
  // pose
  if (!rosidl_runtime_c__float__Sequence__copy(
      &(input->pose), &(output->pose)))
  {
    return false;
  }
  // has_ref
  output->has_ref = input->has_ref;
  // ref_joint
  if (!rosidl_runtime_c__float__Sequence__copy(
      &(input->ref_joint), &(output->ref_joint)))
  {
    return false;
  }
  // mvvelo
  output->mvvelo = input->mvvelo;
  // mvacc
  output->mvacc = input->mvacc;
  // mvtime
  output->mvtime = input->mvtime;
  // mvradii
  output->mvradii = input->mvradii;
  // coord_mode
  output->coord_mode = input->coord_mode;
  // index
  output->index = input->index;
  return true;
}

jaka_msgs__srv__Move_Request *
jaka_msgs__srv__Move_Request__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  jaka_msgs__srv__Move_Request * msg = (jaka_msgs__srv__Move_Request *)allocator.allocate(sizeof(jaka_msgs__srv__Move_Request), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(jaka_msgs__srv__Move_Request));
  bool success = jaka_msgs__srv__Move_Request__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
jaka_msgs__srv__Move_Request__destroy(jaka_msgs__srv__Move_Request * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    jaka_msgs__srv__Move_Request__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
jaka_msgs__srv__Move_Request__Sequence__init(jaka_msgs__srv__Move_Request__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  jaka_msgs__srv__Move_Request * data = NULL;

  if (size) {
    data = (jaka_msgs__srv__Move_Request *)allocator.zero_allocate(size, sizeof(jaka_msgs__srv__Move_Request), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = jaka_msgs__srv__Move_Request__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        jaka_msgs__srv__Move_Request__fini(&data[i - 1]);
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
jaka_msgs__srv__Move_Request__Sequence__fini(jaka_msgs__srv__Move_Request__Sequence * array)
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
      jaka_msgs__srv__Move_Request__fini(&array->data[i]);
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

jaka_msgs__srv__Move_Request__Sequence *
jaka_msgs__srv__Move_Request__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  jaka_msgs__srv__Move_Request__Sequence * array = (jaka_msgs__srv__Move_Request__Sequence *)allocator.allocate(sizeof(jaka_msgs__srv__Move_Request__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = jaka_msgs__srv__Move_Request__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
jaka_msgs__srv__Move_Request__Sequence__destroy(jaka_msgs__srv__Move_Request__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    jaka_msgs__srv__Move_Request__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
jaka_msgs__srv__Move_Request__Sequence__are_equal(const jaka_msgs__srv__Move_Request__Sequence * lhs, const jaka_msgs__srv__Move_Request__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!jaka_msgs__srv__Move_Request__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
jaka_msgs__srv__Move_Request__Sequence__copy(
  const jaka_msgs__srv__Move_Request__Sequence * input,
  jaka_msgs__srv__Move_Request__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(jaka_msgs__srv__Move_Request);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    jaka_msgs__srv__Move_Request * data =
      (jaka_msgs__srv__Move_Request *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!jaka_msgs__srv__Move_Request__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          jaka_msgs__srv__Move_Request__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!jaka_msgs__srv__Move_Request__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `message`
#include "rosidl_runtime_c/string_functions.h"

bool
jaka_msgs__srv__Move_Response__init(jaka_msgs__srv__Move_Response * msg)
{
  if (!msg) {
    return false;
  }
  // ret
  // message
  if (!rosidl_runtime_c__String__init(&msg->message)) {
    jaka_msgs__srv__Move_Response__fini(msg);
    return false;
  }
  return true;
}

void
jaka_msgs__srv__Move_Response__fini(jaka_msgs__srv__Move_Response * msg)
{
  if (!msg) {
    return;
  }
  // ret
  // message
  rosidl_runtime_c__String__fini(&msg->message);
}

bool
jaka_msgs__srv__Move_Response__are_equal(const jaka_msgs__srv__Move_Response * lhs, const jaka_msgs__srv__Move_Response * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // ret
  if (lhs->ret != rhs->ret) {
    return false;
  }
  // message
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->message), &(rhs->message)))
  {
    return false;
  }
  return true;
}

bool
jaka_msgs__srv__Move_Response__copy(
  const jaka_msgs__srv__Move_Response * input,
  jaka_msgs__srv__Move_Response * output)
{
  if (!input || !output) {
    return false;
  }
  // ret
  output->ret = input->ret;
  // message
  if (!rosidl_runtime_c__String__copy(
      &(input->message), &(output->message)))
  {
    return false;
  }
  return true;
}

jaka_msgs__srv__Move_Response *
jaka_msgs__srv__Move_Response__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  jaka_msgs__srv__Move_Response * msg = (jaka_msgs__srv__Move_Response *)allocator.allocate(sizeof(jaka_msgs__srv__Move_Response), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(jaka_msgs__srv__Move_Response));
  bool success = jaka_msgs__srv__Move_Response__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
jaka_msgs__srv__Move_Response__destroy(jaka_msgs__srv__Move_Response * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    jaka_msgs__srv__Move_Response__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
jaka_msgs__srv__Move_Response__Sequence__init(jaka_msgs__srv__Move_Response__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  jaka_msgs__srv__Move_Response * data = NULL;

  if (size) {
    data = (jaka_msgs__srv__Move_Response *)allocator.zero_allocate(size, sizeof(jaka_msgs__srv__Move_Response), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = jaka_msgs__srv__Move_Response__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        jaka_msgs__srv__Move_Response__fini(&data[i - 1]);
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
jaka_msgs__srv__Move_Response__Sequence__fini(jaka_msgs__srv__Move_Response__Sequence * array)
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
      jaka_msgs__srv__Move_Response__fini(&array->data[i]);
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

jaka_msgs__srv__Move_Response__Sequence *
jaka_msgs__srv__Move_Response__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  jaka_msgs__srv__Move_Response__Sequence * array = (jaka_msgs__srv__Move_Response__Sequence *)allocator.allocate(sizeof(jaka_msgs__srv__Move_Response__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = jaka_msgs__srv__Move_Response__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
jaka_msgs__srv__Move_Response__Sequence__destroy(jaka_msgs__srv__Move_Response__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    jaka_msgs__srv__Move_Response__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
jaka_msgs__srv__Move_Response__Sequence__are_equal(const jaka_msgs__srv__Move_Response__Sequence * lhs, const jaka_msgs__srv__Move_Response__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!jaka_msgs__srv__Move_Response__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
jaka_msgs__srv__Move_Response__Sequence__copy(
  const jaka_msgs__srv__Move_Response__Sequence * input,
  jaka_msgs__srv__Move_Response__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(jaka_msgs__srv__Move_Response);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    jaka_msgs__srv__Move_Response * data =
      (jaka_msgs__srv__Move_Response *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!jaka_msgs__srv__Move_Response__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          jaka_msgs__srv__Move_Response__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!jaka_msgs__srv__Move_Response__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
