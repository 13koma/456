// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from jaka_msgs:srv/GetIO.idl
// generated code does not contain a copyright notice

#ifndef JAKA_MSGS__SRV__DETAIL__GET_IO__STRUCT_HPP_
#define JAKA_MSGS__SRV__DETAIL__GET_IO__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__jaka_msgs__srv__GetIO_Request __attribute__((deprecated))
#else
# define DEPRECATED__jaka_msgs__srv__GetIO_Request __declspec(deprecated)
#endif

namespace jaka_msgs
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct GetIO_Request_
{
  using Type = GetIO_Request_<ContainerAllocator>;

  explicit GetIO_Request_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->signal = "";
      this->path = 0;
      this->type = 0;
      this->index = 0;
    }
  }

  explicit GetIO_Request_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : signal(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->signal = "";
      this->path = 0;
      this->type = 0;
      this->index = 0;
    }
  }

  // field types and members
  using _signal_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _signal_type signal;
  using _path_type =
    int16_t;
  _path_type path;
  using _type_type =
    int16_t;
  _type_type type;
  using _index_type =
    int16_t;
  _index_type index;

  // setters for named parameter idiom
  Type & set__signal(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->signal = _arg;
    return *this;
  }
  Type & set__path(
    const int16_t & _arg)
  {
    this->path = _arg;
    return *this;
  }
  Type & set__type(
    const int16_t & _arg)
  {
    this->type = _arg;
    return *this;
  }
  Type & set__index(
    const int16_t & _arg)
  {
    this->index = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    jaka_msgs::srv::GetIO_Request_<ContainerAllocator> *;
  using ConstRawPtr =
    const jaka_msgs::srv::GetIO_Request_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<jaka_msgs::srv::GetIO_Request_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<jaka_msgs::srv::GetIO_Request_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      jaka_msgs::srv::GetIO_Request_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<jaka_msgs::srv::GetIO_Request_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      jaka_msgs::srv::GetIO_Request_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<jaka_msgs::srv::GetIO_Request_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<jaka_msgs::srv::GetIO_Request_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<jaka_msgs::srv::GetIO_Request_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__jaka_msgs__srv__GetIO_Request
    std::shared_ptr<jaka_msgs::srv::GetIO_Request_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__jaka_msgs__srv__GetIO_Request
    std::shared_ptr<jaka_msgs::srv::GetIO_Request_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const GetIO_Request_ & other) const
  {
    if (this->signal != other.signal) {
      return false;
    }
    if (this->path != other.path) {
      return false;
    }
    if (this->type != other.type) {
      return false;
    }
    if (this->index != other.index) {
      return false;
    }
    return true;
  }
  bool operator!=(const GetIO_Request_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct GetIO_Request_

// alias to use template instance with default allocator
using GetIO_Request =
  jaka_msgs::srv::GetIO_Request_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace jaka_msgs


#ifndef _WIN32
# define DEPRECATED__jaka_msgs__srv__GetIO_Response __attribute__((deprecated))
#else
# define DEPRECATED__jaka_msgs__srv__GetIO_Response __declspec(deprecated)
#endif

namespace jaka_msgs
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct GetIO_Response_
{
  using Type = GetIO_Response_<ContainerAllocator>;

  explicit GetIO_Response_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->value = 0.0f;
      this->message = "";
    }
  }

  explicit GetIO_Response_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : message(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->value = 0.0f;
      this->message = "";
    }
  }

  // field types and members
  using _value_type =
    float;
  _value_type value;
  using _message_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _message_type message;

  // setters for named parameter idiom
  Type & set__value(
    const float & _arg)
  {
    this->value = _arg;
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
    jaka_msgs::srv::GetIO_Response_<ContainerAllocator> *;
  using ConstRawPtr =
    const jaka_msgs::srv::GetIO_Response_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<jaka_msgs::srv::GetIO_Response_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<jaka_msgs::srv::GetIO_Response_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      jaka_msgs::srv::GetIO_Response_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<jaka_msgs::srv::GetIO_Response_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      jaka_msgs::srv::GetIO_Response_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<jaka_msgs::srv::GetIO_Response_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<jaka_msgs::srv::GetIO_Response_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<jaka_msgs::srv::GetIO_Response_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__jaka_msgs__srv__GetIO_Response
    std::shared_ptr<jaka_msgs::srv::GetIO_Response_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__jaka_msgs__srv__GetIO_Response
    std::shared_ptr<jaka_msgs::srv::GetIO_Response_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const GetIO_Response_ & other) const
  {
    if (this->value != other.value) {
      return false;
    }
    if (this->message != other.message) {
      return false;
    }
    return true;
  }
  bool operator!=(const GetIO_Response_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct GetIO_Response_

// alias to use template instance with default allocator
using GetIO_Response =
  jaka_msgs::srv::GetIO_Response_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace jaka_msgs

namespace jaka_msgs
{

namespace srv
{

struct GetIO
{
  using Request = jaka_msgs::srv::GetIO_Request;
  using Response = jaka_msgs::srv::GetIO_Response;
};

}  // namespace srv

}  // namespace jaka_msgs

#endif  // JAKA_MSGS__SRV__DETAIL__GET_IO__STRUCT_HPP_
