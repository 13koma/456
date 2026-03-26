// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from jaka_msgs:srv/SetPayload.idl
// generated code does not contain a copyright notice

#ifndef JAKA_MSGS__SRV__DETAIL__SET_PAYLOAD__STRUCT_HPP_
#define JAKA_MSGS__SRV__DETAIL__SET_PAYLOAD__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__jaka_msgs__srv__SetPayload_Request __attribute__((deprecated))
#else
# define DEPRECATED__jaka_msgs__srv__SetPayload_Request __declspec(deprecated)
#endif

namespace jaka_msgs
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct SetPayload_Request_
{
  using Type = SetPayload_Request_<ContainerAllocator>;

  explicit SetPayload_Request_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->tool_num = 0;
      this->mass = 0.0f;
      this->xc = 0.0f;
      this->yc = 0.0f;
      this->zc = 0.0f;
    }
  }

  explicit SetPayload_Request_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->tool_num = 0;
      this->mass = 0.0f;
      this->xc = 0.0f;
      this->yc = 0.0f;
      this->zc = 0.0f;
    }
  }

  // field types and members
  using _tool_num_type =
    int16_t;
  _tool_num_type tool_num;
  using _mass_type =
    float;
  _mass_type mass;
  using _xc_type =
    float;
  _xc_type xc;
  using _yc_type =
    float;
  _yc_type yc;
  using _zc_type =
    float;
  _zc_type zc;

  // setters for named parameter idiom
  Type & set__tool_num(
    const int16_t & _arg)
  {
    this->tool_num = _arg;
    return *this;
  }
  Type & set__mass(
    const float & _arg)
  {
    this->mass = _arg;
    return *this;
  }
  Type & set__xc(
    const float & _arg)
  {
    this->xc = _arg;
    return *this;
  }
  Type & set__yc(
    const float & _arg)
  {
    this->yc = _arg;
    return *this;
  }
  Type & set__zc(
    const float & _arg)
  {
    this->zc = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    jaka_msgs::srv::SetPayload_Request_<ContainerAllocator> *;
  using ConstRawPtr =
    const jaka_msgs::srv::SetPayload_Request_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<jaka_msgs::srv::SetPayload_Request_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<jaka_msgs::srv::SetPayload_Request_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      jaka_msgs::srv::SetPayload_Request_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<jaka_msgs::srv::SetPayload_Request_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      jaka_msgs::srv::SetPayload_Request_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<jaka_msgs::srv::SetPayload_Request_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<jaka_msgs::srv::SetPayload_Request_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<jaka_msgs::srv::SetPayload_Request_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__jaka_msgs__srv__SetPayload_Request
    std::shared_ptr<jaka_msgs::srv::SetPayload_Request_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__jaka_msgs__srv__SetPayload_Request
    std::shared_ptr<jaka_msgs::srv::SetPayload_Request_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const SetPayload_Request_ & other) const
  {
    if (this->tool_num != other.tool_num) {
      return false;
    }
    if (this->mass != other.mass) {
      return false;
    }
    if (this->xc != other.xc) {
      return false;
    }
    if (this->yc != other.yc) {
      return false;
    }
    if (this->zc != other.zc) {
      return false;
    }
    return true;
  }
  bool operator!=(const SetPayload_Request_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct SetPayload_Request_

// alias to use template instance with default allocator
using SetPayload_Request =
  jaka_msgs::srv::SetPayload_Request_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace jaka_msgs


#ifndef _WIN32
# define DEPRECATED__jaka_msgs__srv__SetPayload_Response __attribute__((deprecated))
#else
# define DEPRECATED__jaka_msgs__srv__SetPayload_Response __declspec(deprecated)
#endif

namespace jaka_msgs
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct SetPayload_Response_
{
  using Type = SetPayload_Response_<ContainerAllocator>;

  explicit SetPayload_Response_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->ret = 0;
      this->message = "";
    }
  }

  explicit SetPayload_Response_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
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
    jaka_msgs::srv::SetPayload_Response_<ContainerAllocator> *;
  using ConstRawPtr =
    const jaka_msgs::srv::SetPayload_Response_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<jaka_msgs::srv::SetPayload_Response_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<jaka_msgs::srv::SetPayload_Response_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      jaka_msgs::srv::SetPayload_Response_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<jaka_msgs::srv::SetPayload_Response_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      jaka_msgs::srv::SetPayload_Response_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<jaka_msgs::srv::SetPayload_Response_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<jaka_msgs::srv::SetPayload_Response_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<jaka_msgs::srv::SetPayload_Response_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__jaka_msgs__srv__SetPayload_Response
    std::shared_ptr<jaka_msgs::srv::SetPayload_Response_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__jaka_msgs__srv__SetPayload_Response
    std::shared_ptr<jaka_msgs::srv::SetPayload_Response_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const SetPayload_Response_ & other) const
  {
    if (this->ret != other.ret) {
      return false;
    }
    if (this->message != other.message) {
      return false;
    }
    return true;
  }
  bool operator!=(const SetPayload_Response_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct SetPayload_Response_

// alias to use template instance with default allocator
using SetPayload_Response =
  jaka_msgs::srv::SetPayload_Response_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace jaka_msgs

namespace jaka_msgs
{

namespace srv
{

struct SetPayload
{
  using Request = jaka_msgs::srv::SetPayload_Request;
  using Response = jaka_msgs::srv::SetPayload_Response;
};

}  // namespace srv

}  // namespace jaka_msgs

#endif  // JAKA_MSGS__SRV__DETAIL__SET_PAYLOAD__STRUCT_HPP_
