// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from jaka_msgs:srv/ServoMove.idl
// generated code does not contain a copyright notice

#ifndef JAKA_MSGS__SRV__DETAIL__SERVO_MOVE__BUILDER_HPP_
#define JAKA_MSGS__SRV__DETAIL__SERVO_MOVE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "jaka_msgs/srv/detail/servo_move__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace jaka_msgs
{

namespace srv
{

namespace builder
{

class Init_ServoMove_Request_speed
{
public:
  explicit Init_ServoMove_Request_speed(::jaka_msgs::srv::ServoMove_Request & msg)
  : msg_(msg)
  {}
  ::jaka_msgs::srv::ServoMove_Request speed(::jaka_msgs::srv::ServoMove_Request::_speed_type arg)
  {
    msg_.speed = std::move(arg);
    return std::move(msg_);
  }

private:
  ::jaka_msgs::srv::ServoMove_Request msg_;
};

class Init_ServoMove_Request_pose
{
public:
  Init_ServoMove_Request_pose()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ServoMove_Request_speed pose(::jaka_msgs::srv::ServoMove_Request::_pose_type arg)
  {
    msg_.pose = std::move(arg);
    return Init_ServoMove_Request_speed(msg_);
  }

private:
  ::jaka_msgs::srv::ServoMove_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::jaka_msgs::srv::ServoMove_Request>()
{
  return jaka_msgs::srv::builder::Init_ServoMove_Request_pose();
}

}  // namespace jaka_msgs


namespace jaka_msgs
{

namespace srv
{

namespace builder
{

class Init_ServoMove_Response_message
{
public:
  explicit Init_ServoMove_Response_message(::jaka_msgs::srv::ServoMove_Response & msg)
  : msg_(msg)
  {}
  ::jaka_msgs::srv::ServoMove_Response message(::jaka_msgs::srv::ServoMove_Response::_message_type arg)
  {
    msg_.message = std::move(arg);
    return std::move(msg_);
  }

private:
  ::jaka_msgs::srv::ServoMove_Response msg_;
};

class Init_ServoMove_Response_ret
{
public:
  Init_ServoMove_Response_ret()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ServoMove_Response_message ret(::jaka_msgs::srv::ServoMove_Response::_ret_type arg)
  {
    msg_.ret = std::move(arg);
    return Init_ServoMove_Response_message(msg_);
  }

private:
  ::jaka_msgs::srv::ServoMove_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::jaka_msgs::srv::ServoMove_Response>()
{
  return jaka_msgs::srv::builder::Init_ServoMove_Response_ret();
}

}  // namespace jaka_msgs

#endif  // JAKA_MSGS__SRV__DETAIL__SERVO_MOVE__BUILDER_HPP_
