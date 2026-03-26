// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from jaka_msgs:srv/SetIO.idl
// generated code does not contain a copyright notice

#ifndef JAKA_MSGS__SRV__DETAIL__SET_IO__BUILDER_HPP_
#define JAKA_MSGS__SRV__DETAIL__SET_IO__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "jaka_msgs/srv/detail/set_io__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace jaka_msgs
{

namespace srv
{

namespace builder
{

class Init_SetIO_Request_value
{
public:
  explicit Init_SetIO_Request_value(::jaka_msgs::srv::SetIO_Request & msg)
  : msg_(msg)
  {}
  ::jaka_msgs::srv::SetIO_Request value(::jaka_msgs::srv::SetIO_Request::_value_type arg)
  {
    msg_.value = std::move(arg);
    return std::move(msg_);
  }

private:
  ::jaka_msgs::srv::SetIO_Request msg_;
};

class Init_SetIO_Request_index
{
public:
  explicit Init_SetIO_Request_index(::jaka_msgs::srv::SetIO_Request & msg)
  : msg_(msg)
  {}
  Init_SetIO_Request_value index(::jaka_msgs::srv::SetIO_Request::_index_type arg)
  {
    msg_.index = std::move(arg);
    return Init_SetIO_Request_value(msg_);
  }

private:
  ::jaka_msgs::srv::SetIO_Request msg_;
};

class Init_SetIO_Request_type
{
public:
  explicit Init_SetIO_Request_type(::jaka_msgs::srv::SetIO_Request & msg)
  : msg_(msg)
  {}
  Init_SetIO_Request_index type(::jaka_msgs::srv::SetIO_Request::_type_type arg)
  {
    msg_.type = std::move(arg);
    return Init_SetIO_Request_index(msg_);
  }

private:
  ::jaka_msgs::srv::SetIO_Request msg_;
};

class Init_SetIO_Request_signal
{
public:
  Init_SetIO_Request_signal()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_SetIO_Request_type signal(::jaka_msgs::srv::SetIO_Request::_signal_type arg)
  {
    msg_.signal = std::move(arg);
    return Init_SetIO_Request_type(msg_);
  }

private:
  ::jaka_msgs::srv::SetIO_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::jaka_msgs::srv::SetIO_Request>()
{
  return jaka_msgs::srv::builder::Init_SetIO_Request_signal();
}

}  // namespace jaka_msgs


namespace jaka_msgs
{

namespace srv
{

namespace builder
{

class Init_SetIO_Response_message
{
public:
  explicit Init_SetIO_Response_message(::jaka_msgs::srv::SetIO_Response & msg)
  : msg_(msg)
  {}
  ::jaka_msgs::srv::SetIO_Response message(::jaka_msgs::srv::SetIO_Response::_message_type arg)
  {
    msg_.message = std::move(arg);
    return std::move(msg_);
  }

private:
  ::jaka_msgs::srv::SetIO_Response msg_;
};

class Init_SetIO_Response_ret
{
public:
  Init_SetIO_Response_ret()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_SetIO_Response_message ret(::jaka_msgs::srv::SetIO_Response::_ret_type arg)
  {
    msg_.ret = std::move(arg);
    return Init_SetIO_Response_message(msg_);
  }

private:
  ::jaka_msgs::srv::SetIO_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::jaka_msgs::srv::SetIO_Response>()
{
  return jaka_msgs::srv::builder::Init_SetIO_Response_ret();
}

}  // namespace jaka_msgs

#endif  // JAKA_MSGS__SRV__DETAIL__SET_IO__BUILDER_HPP_
