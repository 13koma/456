// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from jaka_msgs:srv/SetCollision.idl
// generated code does not contain a copyright notice

#ifndef JAKA_MSGS__SRV__DETAIL__SET_COLLISION__BUILDER_HPP_
#define JAKA_MSGS__SRV__DETAIL__SET_COLLISION__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "jaka_msgs/srv/detail/set_collision__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace jaka_msgs
{

namespace srv
{

namespace builder
{

class Init_SetCollision_Request_value
{
public:
  explicit Init_SetCollision_Request_value(::jaka_msgs::srv::SetCollision_Request & msg)
  : msg_(msg)
  {}
  ::jaka_msgs::srv::SetCollision_Request value(::jaka_msgs::srv::SetCollision_Request::_value_type arg)
  {
    msg_.value = std::move(arg);
    return std::move(msg_);
  }

private:
  ::jaka_msgs::srv::SetCollision_Request msg_;
};

class Init_SetCollision_Request_is_enable
{
public:
  Init_SetCollision_Request_is_enable()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_SetCollision_Request_value is_enable(::jaka_msgs::srv::SetCollision_Request::_is_enable_type arg)
  {
    msg_.is_enable = std::move(arg);
    return Init_SetCollision_Request_value(msg_);
  }

private:
  ::jaka_msgs::srv::SetCollision_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::jaka_msgs::srv::SetCollision_Request>()
{
  return jaka_msgs::srv::builder::Init_SetCollision_Request_is_enable();
}

}  // namespace jaka_msgs


namespace jaka_msgs
{

namespace srv
{

namespace builder
{

class Init_SetCollision_Response_message
{
public:
  explicit Init_SetCollision_Response_message(::jaka_msgs::srv::SetCollision_Response & msg)
  : msg_(msg)
  {}
  ::jaka_msgs::srv::SetCollision_Response message(::jaka_msgs::srv::SetCollision_Response::_message_type arg)
  {
    msg_.message = std::move(arg);
    return std::move(msg_);
  }

private:
  ::jaka_msgs::srv::SetCollision_Response msg_;
};

class Init_SetCollision_Response_ret
{
public:
  Init_SetCollision_Response_ret()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_SetCollision_Response_message ret(::jaka_msgs::srv::SetCollision_Response::_ret_type arg)
  {
    msg_.ret = std::move(arg);
    return Init_SetCollision_Response_message(msg_);
  }

private:
  ::jaka_msgs::srv::SetCollision_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::jaka_msgs::srv::SetCollision_Response>()
{
  return jaka_msgs::srv::builder::Init_SetCollision_Response_ret();
}

}  // namespace jaka_msgs

#endif  // JAKA_MSGS__SRV__DETAIL__SET_COLLISION__BUILDER_HPP_
