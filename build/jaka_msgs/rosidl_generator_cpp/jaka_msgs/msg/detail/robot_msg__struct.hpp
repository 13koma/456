// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from jaka_msgs:msg/RobotMsg.idl
// generated code does not contain a copyright notice

#ifndef JAKA_MSGS__MSG__DETAIL__ROBOT_MSG__STRUCT_HPP_
#define JAKA_MSGS__MSG__DETAIL__ROBOT_MSG__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__jaka_msgs__msg__RobotMsg __attribute__((deprecated))
#else
# define DEPRECATED__jaka_msgs__msg__RobotMsg __declspec(deprecated)
#endif

namespace jaka_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct RobotMsg_
{
  using Type = RobotMsg_<ContainerAllocator>;

  explicit RobotMsg_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->motion_state = 0;
      this->power_state = 0;
      this->servo_state = 0;
      this->collision_state = 0;
    }
  }

  explicit RobotMsg_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->motion_state = 0;
      this->power_state = 0;
      this->servo_state = 0;
      this->collision_state = 0;
    }
  }

  // field types and members
  using _motion_state_type =
    int16_t;
  _motion_state_type motion_state;
  using _power_state_type =
    int16_t;
  _power_state_type power_state;
  using _servo_state_type =
    int16_t;
  _servo_state_type servo_state;
  using _collision_state_type =
    int16_t;
  _collision_state_type collision_state;

  // setters for named parameter idiom
  Type & set__motion_state(
    const int16_t & _arg)
  {
    this->motion_state = _arg;
    return *this;
  }
  Type & set__power_state(
    const int16_t & _arg)
  {
    this->power_state = _arg;
    return *this;
  }
  Type & set__servo_state(
    const int16_t & _arg)
  {
    this->servo_state = _arg;
    return *this;
  }
  Type & set__collision_state(
    const int16_t & _arg)
  {
    this->collision_state = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    jaka_msgs::msg::RobotMsg_<ContainerAllocator> *;
  using ConstRawPtr =
    const jaka_msgs::msg::RobotMsg_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<jaka_msgs::msg::RobotMsg_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<jaka_msgs::msg::RobotMsg_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      jaka_msgs::msg::RobotMsg_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<jaka_msgs::msg::RobotMsg_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      jaka_msgs::msg::RobotMsg_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<jaka_msgs::msg::RobotMsg_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<jaka_msgs::msg::RobotMsg_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<jaka_msgs::msg::RobotMsg_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__jaka_msgs__msg__RobotMsg
    std::shared_ptr<jaka_msgs::msg::RobotMsg_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__jaka_msgs__msg__RobotMsg
    std::shared_ptr<jaka_msgs::msg::RobotMsg_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const RobotMsg_ & other) const
  {
    if (this->motion_state != other.motion_state) {
      return false;
    }
    if (this->power_state != other.power_state) {
      return false;
    }
    if (this->servo_state != other.servo_state) {
      return false;
    }
    if (this->collision_state != other.collision_state) {
      return false;
    }
    return true;
  }
  bool operator!=(const RobotMsg_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct RobotMsg_

// alias to use template instance with default allocator
using RobotMsg =
  jaka_msgs::msg::RobotMsg_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace jaka_msgs

#endif  // JAKA_MSGS__MSG__DETAIL__ROBOT_MSG__STRUCT_HPP_
