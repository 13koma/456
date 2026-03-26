// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from jaka_msgs:srv/SetTcpFrame.idl
// generated code does not contain a copyright notice

#ifndef JAKA_MSGS__SRV__DETAIL__SET_TCP_FRAME__BUILDER_HPP_
#define JAKA_MSGS__SRV__DETAIL__SET_TCP_FRAME__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "jaka_msgs/srv/detail/set_tcp_frame__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace jaka_msgs
{

namespace srv
{

namespace builder
{

class Init_SetTcpFrame_Request_tool_num
{
public:
  explicit Init_SetTcpFrame_Request_tool_num(::jaka_msgs::srv::SetTcpFrame_Request & msg)
  : msg_(msg)
  {}
  ::jaka_msgs::srv::SetTcpFrame_Request tool_num(::jaka_msgs::srv::SetTcpFrame_Request::_tool_num_type arg)
  {
    msg_.tool_num = std::move(arg);
    return std::move(msg_);
  }

private:
  ::jaka_msgs::srv::SetTcpFrame_Request msg_;
};

class Init_SetTcpFrame_Request_pose
{
public:
  Init_SetTcpFrame_Request_pose()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_SetTcpFrame_Request_tool_num pose(::jaka_msgs::srv::SetTcpFrame_Request::_pose_type arg)
  {
    msg_.pose = std::move(arg);
    return Init_SetTcpFrame_Request_tool_num(msg_);
  }

private:
  ::jaka_msgs::srv::SetTcpFrame_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::jaka_msgs::srv::SetTcpFrame_Request>()
{
  return jaka_msgs::srv::builder::Init_SetTcpFrame_Request_pose();
}

}  // namespace jaka_msgs


namespace jaka_msgs
{

namespace srv
{

namespace builder
{

class Init_SetTcpFrame_Response_message
{
public:
  explicit Init_SetTcpFrame_Response_message(::jaka_msgs::srv::SetTcpFrame_Response & msg)
  : msg_(msg)
  {}
  ::jaka_msgs::srv::SetTcpFrame_Response message(::jaka_msgs::srv::SetTcpFrame_Response::_message_type arg)
  {
    msg_.message = std::move(arg);
    return std::move(msg_);
  }

private:
  ::jaka_msgs::srv::SetTcpFrame_Response msg_;
};

class Init_SetTcpFrame_Response_ret
{
public:
  Init_SetTcpFrame_Response_ret()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_SetTcpFrame_Response_message ret(::jaka_msgs::srv::SetTcpFrame_Response::_ret_type arg)
  {
    msg_.ret = std::move(arg);
    return Init_SetTcpFrame_Response_message(msg_);
  }

private:
  ::jaka_msgs::srv::SetTcpFrame_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::jaka_msgs::srv::SetTcpFrame_Response>()
{
  return jaka_msgs::srv::builder::Init_SetTcpFrame_Response_ret();
}

}  // namespace jaka_msgs

#endif  // JAKA_MSGS__SRV__DETAIL__SET_TCP_FRAME__BUILDER_HPP_
