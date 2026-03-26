// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from jaka_msgs:srv/ServoMoveEnable.idl
// generated code does not contain a copyright notice

#ifndef JAKA_MSGS__SRV__DETAIL__SERVO_MOVE_ENABLE__STRUCT_HPP_
#define JAKA_MSGS__SRV__DETAIL__SERVO_MOVE_ENABLE__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__jaka_msgs__srv__ServoMoveEnable_Request __attribute__((deprecated))
#else
# define DEPRECATED__jaka_msgs__srv__ServoMoveEnable_Request __declspec(deprecated)
#endif

namespace jaka_msgs
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct ServoMoveEnable_Request_
{
  using Type = ServoMoveEnable_Request_<ContainerAllocator>;

  explicit ServoMoveEnable_Request_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->enable = false;
    }
  }

  explicit ServoMoveEnable_Request_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->enable = false;
    }
  }

  // field types and members
  using _enable_type =
    bool;
  _enable_type enable;

  // setters for named parameter idiom
  Type & set__enable(
    const bool & _arg)
  {
    this->enable = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    jaka_msgs::srv::ServoMoveEnable_Request_<ContainerAllocator> *;
  using ConstRawPtr =
    const jaka_msgs::srv::ServoMoveEnable_Request_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<jaka_msgs::srv::ServoMoveEnable_Request_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<jaka_msgs::srv::ServoMoveEnable_Request_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      jaka_msgs::srv::ServoMoveEnable_Request_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<jaka_msgs::srv::ServoMoveEnable_Request_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      jaka_msgs::srv::ServoMoveEnable_Request_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<jaka_msgs::srv::ServoMoveEnable_Request_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<jaka_msgs::srv::ServoMoveEnable_Request_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<jaka_msgs::srv::ServoMoveEnable_Request_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__jaka_msgs__srv__ServoMoveEnable_Request
    std::shared_ptr<jaka_msgs::srv::ServoMoveEnable_Request_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__jaka_msgs__srv__ServoMoveEnable_Request
    std::shared_ptr<jaka_msgs::srv::ServoMoveEnable_Request_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const ServoMoveEnable_Request_ & other) const
  {
    if (this->enable != other.enable) {
      return false;
    }
    return true;
  }
  bool operator!=(const ServoMoveEnable_Request_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct ServoMoveEnable_Request_

// alias to use template instance with default allocator
using ServoMoveEnable_Request =
  jaka_msgs::srv::ServoMoveEnable_Request_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace jaka_msgs


#ifndef _WIN32
# define DEPRECATED__jaka_msgs__srv__ServoMoveEnable_Response __attribute__((deprecated))
#else
# define DEPRECATED__jaka_msgs__srv__ServoMoveEnable_Response __declspec(deprecated)
#endif

namespace jaka_msgs
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct ServoMoveEnable_Response_
{
  using Type = ServoMoveEnable_Response_<ContainerAllocator>;

  explicit ServoMoveEnable_Response_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->ret = 0;
      this->message = "";
    }
  }

  explicit ServoMoveEnable_Response_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : message(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->ret = 0;
      this->message = "";
    }
  }

  // field types and members
  using _ret_type =
    int16_t;
  _ret_type ret;
  using _message_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _message_type message;

  // setters for named parameter idiom
  Type & set__ret(
    const int16_t & _arg)
  {
    this->ret = _arg;
    return *this;
  }
  Type & set__message(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->message = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    jaka_msgs::srv::ServoMoveEnable_Response_<ContainerAllocator> *;
  using ConstRawPtr =
    const jaka_msgs::srv::ServoMoveEnable_Response_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<jaka_msgs::srv::ServoMoveEnable_Response_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<jaka_msgs::srv::ServoMoveEnable_Response_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      jaka_msgs::srv::ServoMoveEnable_Response_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<jaka_msgs::srv::ServoMoveEnable_Response_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      jaka_msgs::srv::ServoMoveEnable_Response_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<jaka_msgs::srv::ServoMoveEnable_Response_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<jaka_msgs::srv::ServoMoveEnable_Response_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<jaka_msgs::srv::ServoMoveEnable_Response_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__jaka_msgs__srv__ServoMoveEnable_Response
    std::shared_ptr<jaka_msgs::srv::ServoMoveEnable_Response_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__jaka_msgs__srv__ServoMoveEnable_Response
    std::shared_ptr<jaka_msgs::srv::ServoMoveEnable_Response_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const ServoMoveEnable_Response_ & other) const
  {
    if (this->ret != other.ret) {
      return false;
    }
    if (this->message != other.message) {
      return false;
    }
    return true;
  }
  bool operator!=(const ServoMoveEnable_Response_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct ServoMoveEnable_Response_

// alias to use template instance with default allocator
using ServoMoveEnable_Response =
  jaka_msgs::srv::ServoMoveEnable_Response_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace jaka_msgs

namespace jaka_msgs
{

namespace srv
{

struct ServoMoveEnable
{
  using Request = jaka_msgs::srv::ServoMoveEnable_Request;
  using Response = jaka_msgs::srv::ServoMoveEnable_Response;
};

}  // namespace srv

}  // namespace jaka_msgs

#endif  // JAKA_MSGS__SRV__DETAIL__SERVO_MOVE_ENABLE__STRUCT_HPP_
