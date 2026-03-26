// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from jaka_msgs:srv/GetIO.idl
// generated code does not contain a copyright notice

#ifndef JAKA_MSGS__SRV__DETAIL__GET_IO__BUILDER_HPP_
#define JAKA_MSGS__SRV__DETAIL__GET_IO__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "jaka_msgs/srv/detail/get_io__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace jaka_msgs
{

namespace srv
{

namespace builder
{

class Init_GetIO_Request_index
{
public:
  explicit Init_GetIO_Request_index(::jaka_msgs::srv::GetIO_Request & msg)
  : msg_(msg)
  {}
  ::jaka_msgs::srv::GetIO_Request index(::jaka_msgs::srv::GetIO_Request::_index_type arg)
  {
    msg_.index = std::move(arg);
    return std::move(msg_);
  }

private:
  ::jaka_msgs::srv::GetIO_Request msg_;
};

class Init_GetIO_Request_type
{
public:
  explicit Init_GetIO_Request_type(::jaka_msgs::srv::GetIO_Request & msg)
  : msg_(msg)
  {}
  Init_GetIO_Request_index type(::jaka_msgs::srv::GetIO_Request::_type_type arg)
  {
    msg_.type = std::move(arg);
    return Init_GetIO_Request_index(msg_);
  }

private:
  ::jaka_msgs::srv::GetIO_Request msg_;
};

class Init_GetIO_Request_path
{
public:
  explicit Init_GetIO_Request_path(::jaka_msgs::srv::GetIO_Request & msg)
  : msg_(msg)
  {}
  Init_GetIO_Request_type path(::jaka_msgs::srv::GetIO_Request::_path_type arg)
  {
    msg_.path = std::move(arg);
    return Init_GetIO_Request_type(msg_);
  }

private:
  ::jaka_msgs::srv::GetIO_Request msg_;
};

class Init_GetIO_Request_signal
{
public:
  Init_GetIO_Request_signal()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_GetIO_Request_path signal(::jaka_msgs::srv::GetIO_Request::_signal_type arg)
  {
    msg_.signal = std::move(arg);
    return Init_GetIO_Request_path(msg_);
  }

private:
  ::jaka_msgs::srv::GetIO_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::jaka_msgs::srv::GetIO_Request>()
{
  return jaka_msgs::srv::builder::Init_GetIO_Request_signal();
}

}  // namespace jaka_msgs


namespace jaka_msgs
{

namespace srv
{

namespace builder
{

class Init_GetIO_Response_message
{
public:
  explicit Init_GetIO_Response_message(::jaka_msgs::srv::GetIO_Response & msg)
  : msg_(msg)
  {}
  ::jaka_msgs::srv::GetIO_Response message(::jaka_msgs::srv::GetIO_Response::_message_type arg)
  {
    msg_.message = std::move(arg);
    return std::move(msg_);
  }

private:
  ::jaka_msgs::srv::GetIO_Response msg_;
};

class Init_GetIO_Response_value
{
public:
  Init_GetIO_Response_value()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_GetIO_Response_message value(::jaka_msgs::srv::GetIO_Response::_value_type arg)
  {
    msg_.value = std::move(arg);
    return Init_GetIO_Response_message(msg_);
  }

private:
  ::jaka_msgs::srv::GetIO_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::jaka_msgs::srv::GetIO_Response>()
{
  return jaka_msgs::srv::builder::Init_GetIO_Response_value();
}

}  // namespace jaka_msgs

#endif  // JAKA_MSGS__SRV__DETAIL__GET_IO__BUILDER_HPP_
