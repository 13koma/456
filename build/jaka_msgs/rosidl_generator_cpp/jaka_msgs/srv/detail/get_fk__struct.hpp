// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from jaka_msgs:srv/GetFK.idl
// generated code does not contain a copyright notice

#ifndef JAKA_MSGS__SRV__DETAIL__GET_FK__STRUCT_HPP_
#define JAKA_MSGS__SRV__DETAIL__GET_FK__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__jaka_msgs__srv__GetFK_Request __attribute__((deprecated))
#else
# define DEPRECATED__jaka_msgs__srv__GetFK_Request __declspec(deprecated)
#endif

namespace jaka_msgs
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct GetFK_Request_
{
  using Type = GetFK_Request_<ContainerAllocator>;

  explicit GetFK_Request_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_init;
  }

  explicit GetFK_Request_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_init;
    (void)_alloc;
  }

  // field types and members
  using _joint_type =
    std::vector<float, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<float>>;
  _joint_type joint;

  // setters for named parameter idiom
  Type & set__joint(
    const std::vector<float, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<float>> & _arg)
  {
    this->joint = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    jaka_msgs::srv::GetFK_Request_<ContainerAllocator> *;
  using ConstRawPtr =
    const jaka_msgs::srv::GetFK_Request_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<jaka_msgs::srv::GetFK_Request_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<jaka_msgs::srv::GetFK_Request_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      jaka_msgs::srv::GetFK_Request_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<jaka_msgs::srv::GetFK_Request_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      jaka_msgs::srv::GetFK_Request_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<jaka_msgs::srv::GetFK_Request_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<jaka_msgs::srv::GetFK_Request_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<jaka_msgs::srv::GetFK_Request_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__jaka_msgs__srv__GetFK_Request
    std::shared_ptr<jaka_msgs::srv::GetFK_Request_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__jaka_msgs__srv__GetFK_Request
    std::shared_ptr<jaka_msgs::srv::GetFK_Request_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const GetFK_Request_ & other) const
  {
    if (this->joint != other.joint) {
      return false;
    }
    return true;
  }
  bool operator!=(const GetFK_Request_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct GetFK_Request_

// alias to use template instance with default allocator
using GetFK_Request =
  jaka_msgs::srv::GetFK_Request_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace jaka_msgs


#ifndef _WIN32
# define DEPRECATED__jaka_msgs__srv__GetFK_Response __attribute__((deprecated))
#else
# define DEPRECATED__jaka_msgs__srv__GetFK_Response __declspec(deprecated)
#endif

namespace jaka_msgs
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct GetFK_Response_
{
  using Type = GetFK_Response_<ContainerAllocator>;

  explicit GetFK_Response_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->message = "";
    }
  }

  explicit GetFK_Response_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : message(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->message = "";
    }
  }

  // field types and members
  using _cartesian_pose_type =
    std::vector<float, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<float>>;
  _cartesian_pose_type cartesian_pose;
  using _message_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _message_type message;

  // setters for named parameter idiom
  Type & set__cartesian_pose(
    const std::vector<float, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<float>> & _arg)
  {
    this->cartesian_pose = _arg;
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
    jaka_msgs::srv::GetFK_Response_<ContainerAllocator> *;
  using ConstRawPtr =
    const jaka_msgs::srv::GetFK_Response_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<jaka_msgs::srv::GetFK_Response_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<jaka_msgs::srv::GetFK_Response_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      jaka_msgs::srv::GetFK_Response_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<jaka_msgs::srv::GetFK_Response_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      jaka_msgs::srv::GetFK_Response_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<jaka_msgs::srv::GetFK_Response_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<jaka_msgs::srv::GetFK_Response_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<jaka_msgs::srv::GetFK_Response_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__jaka_msgs__srv__GetFK_Response
    std::shared_ptr<jaka_msgs::srv::GetFK_Response_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__jaka_msgs__srv__GetFK_Response
    std::shared_ptr<jaka_msgs::srv::GetFK_Response_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const GetFK_Response_ & other) const
  {
    if (this->cartesian_pose != other.cartesian_pose) {
      return false;
    }
    if (this->message != other.message) {
      return false;
    }
    return true;
  }
  bool operator!=(const GetFK_Response_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct GetFK_Response_

// alias to use template instance with default allocator
using GetFK_Response =
  jaka_msgs::srv::GetFK_Response_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace jaka_msgs

namespace jaka_msgs
{

namespace srv
{

struct GetFK
{
  using Request = jaka_msgs::srv::GetFK_Request;
  using Response = jaka_msgs::srv::GetFK_Response;
};

}  // namespace srv

}  // namespace jaka_msgs

#endif  // JAKA_MSGS__SRV__DETAIL__GET_FK__STRUCT_HPP_
