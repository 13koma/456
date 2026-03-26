// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from jaka_msgs:msg/RobotMsg.idl
// generated code does not contain a copyright notice

#ifndef JAKA_MSGS__MSG__DETAIL__ROBOT_MSG__BUILDER_HPP_
#define JAKA_MSGS__MSG__DETAIL__ROBOT_MSG__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "jaka_msgs/msg/detail/robot_msg__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace jaka_msgs
{

namespace msg
{

namespace builder
{

class Init_RobotMsg_collision_state
{
public:
  explicit Init_RobotMsg_collision_state(::jaka_msgs::msg::RobotMsg & msg)
  : msg_(msg)
  {}
  ::jaka_msgs::msg::RobotMsg collision_state(::jaka_msgs::msg::RobotMsg::_collision_state_type arg)
  {
    msg_.collision_state = std::move(arg);
    return std::move(msg_);
  }

private:
  ::jaka_msgs::msg::RobotMsg msg_;
};

class Init_RobotMsg_servo_state
{
public:
  explicit Init_RobotMsg_servo_state(::jaka_msgs::msg::RobotMsg & msg)
  : msg_(msg)
  {}
  Init_RobotMsg_collision_state servo_state(::jaka_msgs::msg::RobotMsg::_servo_state_type arg)
  {
    msg_.servo_state = std::move(arg);
    return Init_RobotMsg_collision_state(msg_);
  }

private:
  ::jaka_msgs::msg::RobotMsg msg_;
};

class Init_RobotMsg_power_state
{
public:
  explicit Init_RobotMsg_power_state(::jaka_msgs::msg::RobotMsg & msg)
  : msg_(msg)
  {}
  Init_RobotMsg_servo_state power_state(::jaka_msgs::msg::RobotMsg::_power_state_type arg)
  {
    msg_.power_state = std::move(arg);
    return Init_RobotMsg_servo_state(msg_);
  }

private:
  ::jaka_msgs::msg::RobotMsg msg_;
};

class Init_RobotMsg_motion_state
{
public:
  Init_RobotMsg_motion_state()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_RobotMsg_power_state motion_state(::jaka_msgs::msg::RobotMsg::_motion_state_type arg)
  {
    msg_.motion_state = std::move(arg);
    return Init_RobotMsg_power_state(msg_);
  }

private:
  ::jaka_msgs::msg::RobotMsg msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::jaka_msgs::msg::RobotMsg>()
{
  return jaka_msgs::msg::builder::Init_RobotMsg_motion_state();
}

}  // namespace jaka_msgs

#endif  // JAKA_MSGS__MSG__DETAIL__ROBOT_MSG__BUILDER_HPP_
