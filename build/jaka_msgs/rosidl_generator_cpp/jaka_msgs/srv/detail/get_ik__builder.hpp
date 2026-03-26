// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from jaka_msgs:srv/GetIK.idl
// generated code does not contain a copyright notice

#ifndef JAKA_MSGS__SRV__DETAIL__GET_IK__BUILDER_HPP_
#define JAKA_MSGS__SRV__DETAIL__GET_IK__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "jaka_msgs/srv/detail/get_ik__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace jaka_msgs
{

namespace srv
{

namespace builder
{

class Init_GetIK_Request_cartesian_pose
{
public:
  explicit Init_GetIK_Request_cartesian_pose(::jaka_msgs::srv::GetIK_Request & msg)
  : msg_(msg)
  {}
  ::jaka_msgs::srv::GetIK_Request cartesian_pose(::jaka_msgs::srv::GetIK_Request::_cartesian_pose_type arg)
  {
    msg_.cartesian_pose = std::move(arg);
    return std::move(msg_);
  }

private:
  ::jaka_msgs::srv::GetIK_Request msg_;
};

class Init_GetIK_Request_ref_joint
{
public:
  Init_GetIK_Request_ref_joint()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_GetIK_Request_cartesian_pose ref_joint(::jaka_msgs::srv::GetIK_Request::_ref_joint_type arg)
  {
    msg_.ref_joint = std::move(arg);
    return Init_GetIK_Request_cartesian_pose(msg_);
  }

private:
  ::jaka_msgs::srv::GetIK_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::jaka_msgs::srv::GetIK_Request>()
{
  return jaka_msgs::srv::builder::Init_GetIK_Request_ref_joint();
}

}  // namespace jaka_msgs


namespace jaka_msgs
{

namespace srv
{

namespace builder
{

class Init_GetIK_Response_message
{
public:
  explicit Init_GetIK_Response_message(::jaka_msgs::srv::GetIK_Response & msg)
  : msg_(msg)
  {}
  ::jaka_msgs::srv::GetIK_Response message(::jaka_msgs::srv::GetIK_Response::_message_type arg)
  {
    msg_.message = std::move(arg);
    return std::move(msg_);
  }

private:
  ::jaka_msgs::srv::GetIK_Response msg_;
};

class Init_GetIK_Response_joint
{
public:
  Init_GetIK_Response_joint()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_GetIK_Response_message joint(::jaka_msgs::srv::GetIK_Response::_joint_type arg)
  {
    msg_.joint = std::move(arg);
    return Init_GetIK_Response_message(msg_);
  }

private:
  ::jaka_msgs::srv::GetIK_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::jaka_msgs::srv::GetIK_Response>()
{
  return jaka_msgs::srv::builder::Init_GetIK_Response_joint();
}

}  // namespace jaka_msgs

#endif  // JAKA_MSGS__SRV__DETAIL__GET_IK__BUILDER_HPP_
