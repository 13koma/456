// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from jaka_msgs:srv/Move.idl
// generated code does not contain a copyright notice

#ifndef JAKA_MSGS__SRV__DETAIL__MOVE__BUILDER_HPP_
#define JAKA_MSGS__SRV__DETAIL__MOVE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "jaka_msgs/srv/detail/move__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace jaka_msgs
{

namespace srv
{

namespace builder
{

class Init_Move_Request_index
{
public:
  explicit Init_Move_Request_index(::jaka_msgs::srv::Move_Request & msg)
  : msg_(msg)
  {}
  ::jaka_msgs::srv::Move_Request index(::jaka_msgs::srv::Move_Request::_index_type arg)
  {
    msg_.index = std::move(arg);
    return std::move(msg_);
  }

private:
  ::jaka_msgs::srv::Move_Request msg_;
};

class Init_Move_Request_coord_mode
{
public:
  explicit Init_Move_Request_coord_mode(::jaka_msgs::srv::Move_Request & msg)
  : msg_(msg)
  {}
  Init_Move_Request_index coord_mode(::jaka_msgs::srv::Move_Request::_coord_mode_type arg)
  {
    msg_.coord_mode = std::move(arg);
    return Init_Move_Request_index(msg_);
  }

private:
  ::jaka_msgs::srv::Move_Request msg_;
};

class Init_Move_Request_mvradii
{
public:
  explicit Init_Move_Request_mvradii(::jaka_msgs::srv::Move_Request & msg)
  : msg_(msg)
  {}
  Init_Move_Request_coord_mode mvradii(::jaka_msgs::srv::Move_Request::_mvradii_type arg)
  {
    msg_.mvradii = std::move(arg);
    return Init_Move_Request_coord_mode(msg_);
  }

private:
  ::jaka_msgs::srv::Move_Request msg_;
};

class Init_Move_Request_mvtime
{
public:
  explicit Init_Move_Request_mvtime(::jaka_msgs::srv::Move_Request & msg)
  : msg_(msg)
  {}
  Init_Move_Request_mvradii mvtime(::jaka_msgs::srv::Move_Request::_mvtime_type arg)
  {
    msg_.mvtime = std::move(arg);
    return Init_Move_Request_mvradii(msg_);
  }

private:
  ::jaka_msgs::srv::Move_Request msg_;
};

class Init_Move_Request_mvacc
{
public:
  explicit Init_Move_Request_mvacc(::jaka_msgs::srv::Move_Request & msg)
  : msg_(msg)
  {}
  Init_Move_Request_mvtime mvacc(::jaka_msgs::srv::Move_Request::_mvacc_type arg)
  {
    msg_.mvacc = std::move(arg);
    return Init_Move_Request_mvtime(msg_);
  }

private:
  ::jaka_msgs::srv::Move_Request msg_;
};

class Init_Move_Request_mvvelo
{
public:
  explicit Init_Move_Request_mvvelo(::jaka_msgs::srv::Move_Request & msg)
  : msg_(msg)
  {}
  Init_Move_Request_mvacc mvvelo(::jaka_msgs::srv::Move_Request::_mvvelo_type arg)
  {
    msg_.mvvelo = std::move(arg);
    return Init_Move_Request_mvacc(msg_);
  }

private:
  ::jaka_msgs::srv::Move_Request msg_;
};

class Init_Move_Request_ref_joint
{
public:
  explicit Init_Move_Request_ref_joint(::jaka_msgs::srv::Move_Request & msg)
  : msg_(msg)
  {}
  Init_Move_Request_mvvelo ref_joint(::jaka_msgs::srv::Move_Request::_ref_joint_type arg)
  {
    msg_.ref_joint = std::move(arg);
    return Init_Move_Request_mvvelo(msg_);
  }

private:
  ::jaka_msgs::srv::Move_Request msg_;
};

class Init_Move_Request_has_ref
{
public:
  explicit Init_Move_Request_has_ref(::jaka_msgs::srv::Move_Request & msg)
  : msg_(msg)
  {}
  Init_Move_Request_ref_joint has_ref(::jaka_msgs::srv::Move_Request::_has_ref_type arg)
  {
    msg_.has_ref = std::move(arg);
    return Init_Move_Request_ref_joint(msg_);
  }

private:
  ::jaka_msgs::srv::Move_Request msg_;
};

class Init_Move_Request_pose
{
public:
  Init_Move_Request_pose()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Move_Request_has_ref pose(::jaka_msgs::srv::Move_Request::_pose_type arg)
  {
    msg_.pose = std::move(arg);
    return Init_Move_Request_has_ref(msg_);
  }

private:
  ::jaka_msgs::srv::Move_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::jaka_msgs::srv::Move_Request>()
{
  return jaka_msgs::srv::builder::Init_Move_Request_pose();
}

}  // namespace jaka_msgs


namespace jaka_msgs
{

namespace srv
{

namespace builder
{

class Init_Move_Response_message
{
public:
  explicit Init_Move_Response_message(::jaka_msgs::srv::Move_Response & msg)
  : msg_(msg)
  {}
  ::jaka_msgs::srv::Move_Response message(::jaka_msgs::srv::Move_Response::_message_type arg)
  {
    msg_.message = std::move(arg);
    return std::move(msg_);
  }

private:
  ::jaka_msgs::srv::Move_Response msg_;
};

class Init_Move_Response_ret
{
public:
  Init_Move_Response_ret()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Move_Response_message ret(::jaka_msgs::srv::Move_Response::_ret_type arg)
  {
    msg_.ret = std::move(arg);
    return Init_Move_Response_message(msg_);
  }

private:
  ::jaka_msgs::srv::Move_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::jaka_msgs::srv::Move_Response>()
{
  return jaka_msgs::srv::builder::Init_Move_Response_ret();
}

}  // namespace jaka_msgs

#endif  // JAKA_MSGS__SRV__DETAIL__MOVE__BUILDER_HPP_
