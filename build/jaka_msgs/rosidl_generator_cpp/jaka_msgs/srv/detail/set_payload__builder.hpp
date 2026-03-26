// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from jaka_msgs:srv/SetPayload.idl
// generated code does not contain a copyright notice

#ifndef JAKA_MSGS__SRV__DETAIL__SET_PAYLOAD__BUILDER_HPP_
#define JAKA_MSGS__SRV__DETAIL__SET_PAYLOAD__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "jaka_msgs/srv/detail/set_payload__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace jaka_msgs
{

namespace srv
{

namespace builder
{

class Init_SetPayload_Request_zc
{
public:
  explicit Init_SetPayload_Request_zc(::jaka_msgs::srv::SetPayload_Request & msg)
  : msg_(msg)
  {}
  ::jaka_msgs::srv::SetPayload_Request zc(::jaka_msgs::srv::SetPayload_Request::_zc_type arg)
  {
    msg_.zc = std::move(arg);
    return std::move(msg_);
  }

private:
  ::jaka_msgs::srv::SetPayload_Request msg_;
};

class Init_SetPayload_Request_yc
{
public:
  explicit Init_SetPayload_Request_yc(::jaka_msgs::srv::SetPayload_Request & msg)
  : msg_(msg)
  {}
  Init_SetPayload_Request_zc yc(::jaka_msgs::srv::SetPayload_Request::_yc_type arg)
  {
    msg_.yc = std::move(arg);
    return Init_SetPayload_Request_zc(msg_);
  }

private:
  ::jaka_msgs::srv::SetPayload_Request msg_;
};

class Init_SetPayload_Request_xc
{
public:
  explicit Init_SetPayload_Request_xc(::jaka_msgs::srv::SetPayload_Request & msg)
  : msg_(msg)
  {}
  Init_SetPayload_Request_yc xc(::jaka_msgs::srv::SetPayload_Request::_xc_type arg)
  {
    msg_.xc = std::move(arg);
    return Init_SetPayload_Request_yc(msg_);
  }

private:
  ::jaka_msgs::srv::SetPayload_Request msg_;
};

class Init_SetPayload_Request_mass
{
public:
  explicit Init_SetPayload_Request_mass(::jaka_msgs::srv::SetPayload_Request & msg)
  : msg_(msg)
  {}
  Init_SetPayload_Request_xc mass(::jaka_msgs::srv::SetPayload_Request::_mass_type arg)
  {
    msg_.mass = std::move(arg);
    return Init_SetPayload_Request_xc(msg_);
  }

private:
  ::jaka_msgs::srv::SetPayload_Request msg_;
};

class Init_SetPayload_Request_tool_num
{
public:
  Init_SetPayload_Request_tool_num()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_SetPayload_Request_mass tool_num(::jaka_msgs::srv::SetPayload_Request::_tool_num_type arg)
  {
    msg_.tool_num = std::move(arg);
    return Init_SetPayload_Request_mass(msg_);
  }

private:
  ::jaka_msgs::srv::SetPayload_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::jaka_msgs::srv::SetPayload_Request>()
{
  return jaka_msgs::srv::builder::Init_SetPayload_Request_tool_num();
}

}  // namespace jaka_msgs


namespace jaka_msgs
{

namespace srv
{

namespace builder
{

class Init_SetPayload_Response_message
{
public:
  explicit Init_SetPayload_Response_message(::jaka_msgs::srv::SetPayload_Response & msg)
  : msg_(msg)
  {}
  ::jaka_msgs::srv::SetPayload_Response message(::jaka_msgs::srv::SetPayload_Response::_message_type arg)
  {
    msg_.message = std::move(arg);
    return std::move(msg_);
  }

private:
  ::jaka_msgs::srv::SetPayload_Response msg_;
};

class Init_SetPayload_Response_ret
{
public:
  Init_SetPayload_Response_ret()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_SetPayload_Response_message ret(::jaka_msgs::srv::SetPayload_Response::_ret_type arg)
  {
    msg_.ret = std::move(arg);
    return Init_SetPayload_Response_message(msg_);
  }

private:
  ::jaka_msgs::srv::SetPayload_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::jaka_msgs::srv::SetPayload_Response>()
{
  return jaka_msgs::srv::builder::Init_SetPayload_Response_ret();
}

}  // namespace jaka_msgs

#endif  // JAKA_MSGS__SRV__DETAIL__SET_PAYLOAD__BUILDER_HPP_
