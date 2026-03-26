// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from jaka_msgs:srv/Move.idl
// generated code does not contain a copyright notice

#ifndef JAKA_MSGS__SRV__DETAIL__MOVE__STRUCT_HPP_
#define JAKA_MSGS__SRV__DETAIL__MOVE__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__jaka_msgs__srv__Move_Request __attribute__((deprecated))
#else
# define DEPRECATED__jaka_msgs__srv__Move_Request __declspec(deprecated)
#endif

namespace jaka_msgs
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct Move_Request_
{
  using Type = Move_Request_<ContainerAllocator>;

  explicit Move_Request_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->has_ref = false;
      this->mvvelo = 0.0f;
      this->mvacc = 0.0f;
      this->mvtime = 0.0f;
      this->mvradii = 0.0f;
      this->coord_mode = 0;
      this->index = 0;
    }
  }

  explicit Move_Request_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->has_ref = false;
      this->mvvelo = 0.0f;
      this->mvacc = 0.0f;
      this->mvtime = 0.0f;
      this->mvradii = 0.0f;
      this->coord_mode = 0;
      this->index = 0;
    }
  }

  // field types and members
  using _pose_type =
    std::vector<float, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<float>>;
  _pose_type pose;
  using _has_ref_type =
    bool;
  _has_ref_type has_ref;
  using _ref_joint_type =
    std::vector<float, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<float>>;
  _ref_joint_type ref_joint;
  using _mvvelo_type =
    float;
  _mvvelo_type mvvelo;
  using _mvacc_type =
    float;
  _mvacc_type mvacc;
  using _mvtime_type =
    float;
  _mvtime_type mvtime;
  using _mvradii_type =
    float;
  _mvradii_type mvradii;
  using _coord_mode_type =
    int16_t;
  _coord_mode_type coord_mode;
  using _index_type =
    int16_t;
  _index_type index;

  // setters for named parameter idiom
  Type & set__pose(
    const std::vector<float, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<float>> & _arg)
  {
    this->pose = _arg;
    return *this;
  }
  Type & set__has_ref(
    const bool & _arg)
  {
    this->has_ref = _arg;
    return *this;
  }
  Type & set__ref_joint(
    const std::vector<float, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<float>> & _arg)
  {
    this->ref_joint = _arg;
    return *this;
  }
  Type & set__mvvelo(
    const float & _arg)
  {
    this->mvvelo = _arg;
    return *this;
  }
  Type & set__mvacc(
    const float & _arg)
  {
    this->mvacc = _arg;
    return *this;
  }
  Type & set__mvtime(
    const float & _arg)
  {
    this->mvtime = _arg;
    return *this;
  }
  Type & set__mvradii(
    const float & _arg)
  {
    this->mvradii = _arg;
    return *this;
  }
  Type & set__coord_mode(
    const int16_t & _arg)
  {
    this->coord_mode = _arg;
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
    jaka_msgs::srv::Move_Request_<ContainerAllocator> *;
  using ConstRawPtr =
    const jaka_msgs::srv::Move_Request_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<jaka_msgs::srv::Move_Request_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<jaka_msgs::srv::Move_Request_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      jaka_msgs::srv::Move_Request_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<jaka_msgs::srv::Move_Request_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      jaka_msgs::srv::Move_Request_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<jaka_msgs::srv::Move_Request_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<jaka_msgs::srv::Move_Request_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<jaka_msgs::srv::Move_Request_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__jaka_msgs__srv__Move_Request
    std::shared_ptr<jaka_msgs::srv::Move_Request_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__jaka_msgs__srv__Move_Request
    std::shared_ptr<jaka_msgs::srv::Move_Request_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const Move_Request_ & other) const
  {
    if (this->pose != other.pose) {
      return false;
    }
    if (this->has_ref != other.has_ref) {
      return false;
    }
    if (this->ref_joint != other.ref_joint) {
      return false;
    }
    if (this->mvvelo != other.mvvelo) {
      return false;
    }
    if (this->mvacc != other.mvacc) {
      return false;
    }
    if (this->mvtime != other.mvtime) {
      return false;
    }
    if (this->mvradii != other.mvradii) {
      return false;
    }
    if (this->coord_mode != other.coord_mode) {
      return false;
    }
    if (this->index != other.index) {
      return false;
    }
    return true;
  }
  bool operator!=(const Move_Request_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct Move_Request_

// alias to use template instance with default allocator
using Move_Request =
  jaka_msgs::srv::Move_Request_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace jaka_msgs


#ifndef _WIN32
# define DEPRECATED__jaka_msgs__srv__Move_Response __attribute__((deprecated))
#else
# define DEPRECATED__jaka_msgs__srv__Move_Response __declspec(deprecated)
#endif

namespace jaka_msgs
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct Move_Response_
{
  using Type = Move_Response_<ContainerAllocator>;

  explicit Move_Response_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->ret = 0;
      this->message = "";
    }
  }

  explicit Move_Response_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
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
    jaka_msgs::srv::Move_Response_<ContainerAllocator> *;
  using ConstRawPtr =
    const jaka_msgs::srv::Move_Response_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<jaka_msgs::srv::Move_Response_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<jaka_msgs::srv::Move_Response_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      jaka_msgs::srv::Move_Response_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<jaka_msgs::srv::Move_Response_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      jaka_msgs::srv::Move_Response_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<jaka_msgs::srv::Move_Response_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<jaka_msgs::srv::Move_Response_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<jaka_msgs::srv::Move_Response_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__jaka_msgs__srv__Move_Response
    std::shared_ptr<jaka_msgs::srv::Move_Response_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__jaka_msgs__srv__Move_Response
    std::shared_ptr<jaka_msgs::srv::Move_Response_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const Move_Response_ & other) const
  {
    if (this->ret != other.ret) {
      return false;
    }
    if (this->message != other.message) {
      return false;
    }
    return true;
  }
  bool operator!=(const Move_Response_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct Move_Response_

// alias to use template instance with default allocator
using Move_Response =
  jaka_msgs::srv::Move_Response_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace jaka_msgs

namespace jaka_msgs
{

namespace srv
{

struct Move
{
  using Request = jaka_msgs::srv::Move_Request;
  using Response = jaka_msgs::srv::Move_Response;
};

}  // namespace srv

}  // namespace jaka_msgs

#endif  // JAKA_MSGS__SRV__DETAIL__MOVE__STRUCT_HPP_
