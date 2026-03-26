// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from jaka_msgs:srv/ClearError.idl
// generated code does not contain a copyright notice

#ifndef JAKA_MSGS__SRV__DETAIL__CLEAR_ERROR__BUILDER_HPP_
#define JAKA_MSGS__SRV__DETAIL__CLEAR_ERROR__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "jaka_msgs/srv/detail/clear_error__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace jaka_msgs
{

namespace srv
{

namespace builder
{

class Init_ClearError_Request_enable
{
public:
  Init_ClearError_Request_enable()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::jaka_msgs::srv::ClearError_Request enable(::jaka_msgs::srv::ClearError_Request::_enable_type arg)
  {
    msg_.enable = std::move(arg);
    return std::move(msg_);
  }

private:
  ::jaka_msgs::srv::ClearError_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::jaka_msgs::srv::ClearError_Request>()
{
  return jaka_msgs::srv::builder::Init_ClearError_Request_enable();
}

}  // namespace jaka_msgs


namespace jaka_msgs
{

namespace srv
{

namespace builder
{

class Init_ClearError_Response_message
{
public:
  explicit Init_ClearError_Response_message(::jaka_msgs::srv::ClearError_Response & msg)
  : msg_(msg)
  {}
  ::jaka_msgs::srv::ClearError_Response message(::jaka_msgs::srv::ClearError_Response::_message_type arg)
  {
    msg_.message = std::move(arg);
    return std::move(msg_);
  }

private:
  ::jaka_msgs::srv::ClearError_Response msg_;
};

class Init_ClearError_Response_ret
{
public:
  Init_ClearError_Response_ret()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ClearError_Response_message ret(::jaka_msgs::srv::ClearError_Response::_ret_type arg)
  {
    msg_.ret = std::move(arg);
    return Init_ClearError_Response_message(msg_);
  }

private:
  ::jaka_msgs::srv::ClearError_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::jaka_msgs::srv::ClearError_Response>()
{
  return jaka_msgs::srv::builder::Init_ClearError_Response_ret();
}

}  // namespace jaka_msgs

#endif  // JAKA_MSGS__SRV__DETAIL__CLEAR_ERROR__BUILDER_HPP_
