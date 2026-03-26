// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from jaka_msgs:srv/GetFK.idl
// generated code does not contain a copyright notice

#ifndef JAKA_MSGS__SRV__DETAIL__GET_FK__BUILDER_HPP_
#define JAKA_MSGS__SRV__DETAIL__GET_FK__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "jaka_msgs/srv/detail/get_fk__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace jaka_msgs
{

namespace srv
{

namespace builder
{

class Init_GetFK_Request_joint
{
public:
  Init_GetFK_Request_joint()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::jaka_msgs::srv::GetFK_Request joint(::jaka_msgs::srv::GetFK_Request::_joint_type arg)
  {
    msg_.joint = std::move(arg);
    return std::move(msg_);
  }

private:
  ::jaka_msgs::srv::GetFK_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::jaka_msgs::srv::GetFK_Request>()
{
  return jaka_msgs::srv::builder::Init_GetFK_Request_joint();
}

}  // namespace jaka_msgs


namespace jaka_msgs
{

namespace srv
{

namespace builder
{

class Init_GetFK_Response_message
{
public:
  explicit Init_GetFK_Response_message(::jaka_msgs::srv::GetFK_Response & msg)
  : msg_(msg)
  {}
  ::jaka_msgs::srv::GetFK_Response message(::jaka_msgs::srv::GetFK_Response::_message_type arg)
  {
    msg_.message = std::move(arg);
    return std::move(msg_);
  }

private:
  ::jaka_msgs::srv::GetFK_Response msg_;
};

class Init_GetFK_Response_cartesian_pose
{
public:
  Init_GetFK_Response_cartesian_pose()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_GetFK_Response_message cartesian_pose(::jaka_msgs::srv::GetFK_Response::_cartesian_pose_type arg)
  {
    msg_.cartesian_pose = std::move(arg);
    return Init_GetFK_Response_message(msg_);
  }

private:
  ::jaka_msgs::srv::GetFK_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::jaka_msgs::srv::GetFK_Response>()
{
  return jaka_msgs::srv::builder::Init_GetFK_Response_cartesian_pose();
}

}  // namespace jaka_msgs

#endif  // JAKA_MSGS__SRV__DETAIL__GET_FK__BUILDER_HPP_
