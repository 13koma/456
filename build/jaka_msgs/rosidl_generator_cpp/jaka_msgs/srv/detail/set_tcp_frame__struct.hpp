// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from jaka_msgs:srv/SetTcpFrame.idl
// generated code does not contain a copyright notice

#ifndef JAKA_MSGS__SRV__DETAIL__SET_TCP_FRAME__STRUCT_HPP_
#define JAKA_MSGS__SRV__DETAIL__SET_TCP_FRAME__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__jaka_msgs__srv__SetTcpFrame_Request __attribute__((deprecated))
#else
# define DEPRECATED__jaka_msgs__srv__SetTcpFrame_Request __declspec(deprecated)
#endif

namespace jaka_msgs
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct SetTcpFrame_Request_
{
  using Type = SetTcpFrame_Request_<ContainerAllocator>;

  explicit SetTcpFrame_Request_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->tool_num = 0;
    }
  }

  explicit SetTcpFrame_Request_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->tool_num = 0;
    }
  }

  // field types and members
  using _pose_type =
    std::vector<float, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<float>>;
  _pose_type pose;
  using _tool_num_type =
    int16_t;
  _tool_num_type tool_num;

  // setters for named parameter idiom
  Type & set__pose(
    const std::vector<float, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<float>> & _arg)
  {
    this->pose = _arg;
    return *this;
  }
  Type & set__tool_num(
    const int16_t & _arg)
  {
    this->tool_num = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    jaka_msgs::srv::SetTcpFrame_Request_<ContainerAllocator> *;
  using ConstRawPtr =
    const jaka_msgs::srv::SetTcpFrame_Request_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<jaka_msgs::srv::SetTcpFrame_Request_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<jaka_msgs::srv::SetTcpFrame_Request_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      jaka_msgs::srv::SetTcpFrame_Request_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<jaka_msgs::srv::SetTcpFrame_Request_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      jaka_msgs::srv::SetTcpFrame_Request_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<jaka_msgs::srv::SetTcpFrame_Request_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<jaka_msgs::srv::SetTcpFrame_Request_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<jaka_msgs::srv::SetTcpFrame_Request_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__jaka_msgs__srv__SetTcpFrame_Request
    std::shared_ptr<jaka_msgs::srv::SetTcpFrame_Request_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__jaka_msgs__srv__SetTcpFrame_Request
    std::shared_ptr<jaka_msgs::srv::SetTcpFrame_Request_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const SetTcpFrame_Request_ & other) const
  {
    if (this->pose != other.pose) {
      return false;
    }
    if (this->tool_num != other.tool_num) {
      return false;
    }
    return true;
  }
  bool operator!=(const SetTcpFrame_Request_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct SetTcpFrame_Request_

// alias to use template instance with default allocator
using SetTcpFrame_Request =
  jaka_msgs::srv::SetTcpFrame_Request_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace jaka_msgs


#ifndef _WIN32
# define DEPRECATED__jaka_msgs__srv__SetTcpFrame_Response __attribute__((deprecated))
#else
# define DEPRECATED__jaka_msgs__srv__SetTcpFrame_Response __declspec(deprecated)
#endif

namespace jaka_msgs
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct SetTcpFrame_Response_
{
  using Type = SetTcpFrame_Response_<ContainerAllocator>;

  explicit SetTcpFrame_Response_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->ret = 0;
      this->message = "";
    }
  }

  explicit SetTcpFrame_Response_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
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
    jaka_msgs::srv::SetTcpFrame_Response_<ContainerAllocator> *;
  using ConstRawPtr =
    const jaka_msgs::srv::SetTcpFrame_Response_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<jaka_msgs::srv::SetTcpFrame_Response_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<jaka_msgs::srv::SetTcpFrame_Response_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      jaka_msgs::srv::SetTcpFrame_Response_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<jaka_msgs::srv::SetTcpFrame_Response_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      jaka_msgs::srv::SetTcpFrame_Response_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<jaka_msgs::srv::SetTcpFrame_Response_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<jaka_msgs::srv::SetTcpFrame_Response_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<jaka_msgs::srv::SetTcpFrame_Response_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__jaka_msgs__srv__SetTcpFrame_Response
    std::shared_ptr<jaka_msgs::srv::SetTcpFrame_Response_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__jaka_msgs__srv__SetTcpFrame_Response
    std::shared_ptr<jaka_msgs::srv::SetTcpFrame_Response_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const SetTcpFrame_Response_ & other) const
  {
    if (this->ret != other.ret) {
      return false;
    }
    if (this->message != other.message) {
      return false;
    }
    return true;
  }
  bool operator!=(const SetTcpFrame_Response_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct SetTcpFrame_Response_

// alias to use template instance with default allocator
using SetTcpFrame_Response =
  jaka_msgs::srv::SetTcpFrame_Response_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace jaka_msgs

namespace jaka_msgs
{

namespace srv
{

struct SetTcpFrame
{
  using Request = jaka_msgs::srv::SetTcpFrame_Request;
  using Response = jaka_msgs::srv::SetTcpFrame_Response;
};

}  // namespace srv

}  // namespace jaka_msgs

#endif  // JAKA_MSGS__SRV__DETAIL__SET_TCP_FRAME__STRUCT_HPP_
