// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from jaka_msgs:msg/RobotMsg.idl
// generated code does not contain a copyright notice

#ifndef JAKA_MSGS__MSG__DETAIL__ROBOT_MSG__TRAITS_HPP_
#define JAKA_MSGS__MSG__DETAIL__ROBOT_MSG__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "jaka_msgs/msg/detail/robot_msg__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace jaka_msgs
{

namespace msg
{

inline void to_flow_style_yaml(
  const RobotMsg & msg,
  std::ostream & out)
{
  out << "{";
  // member: motion_state
  {
    out << "motion_state: ";
    rosidl_generator_traits::value_to_yaml(msg.motion_state, out);
    out << ", ";
  }

  // member: power_state
  {
    out << "power_state: ";
    rosidl_generator_traits::value_to_yaml(msg.power_state, out);
    out << ", ";
  }

  // member: servo_state
  {
    out << "servo_state: ";
    rosidl_generator_traits::value_to_yaml(msg.servo_state, out);
    out << ", ";
  }

  // member: collision_state
  {
    out << "collision_state: ";
    rosidl_generator_traits::value_to_yaml(msg.collision_state, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const RobotMsg & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: motion_state
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "motion_state: ";
    rosidl_generator_traits::value_to_yaml(msg.motion_state, out);
    out << "\n";
  }

  // member: power_state
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "power_state: ";
    rosidl_generator_traits::value_to_yaml(msg.power_state, out);
    out << "\n";
  }

  // member: servo_state
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "servo_state: ";
    rosidl_generator_traits::value_to_yaml(msg.servo_state, out);
    out << "\n";
  }

  // member: collision_state
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "collision_state: ";
    rosidl_generator_traits::value_to_yaml(msg.collision_state, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const RobotMsg & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace msg

}  // namespace jaka_msgs

namespace rosidl_generator_traits
{

[[deprecated("use jaka_msgs::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const jaka_msgs::msg::RobotMsg & msg,
  std::ostream & out, size_t indentation = 0)
{
  jaka_msgs::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use jaka_msgs::msg::to_yaml() instead")]]
inline std::string to_yaml(const jaka_msgs::msg::RobotMsg & msg)
{
  return jaka_msgs::msg::to_yaml(msg);
}

template<>
inline const char * data_type<jaka_msgs::msg::RobotMsg>()
{
  return "jaka_msgs::msg::RobotMsg";
}

template<>
inline const char * name<jaka_msgs::msg::RobotMsg>()
{
  return "jaka_msgs/msg/RobotMsg";
}

template<>
struct has_fixed_size<jaka_msgs::msg::RobotMsg>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<jaka_msgs::msg::RobotMsg>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<jaka_msgs::msg::RobotMsg>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // JAKA_MSGS__MSG__DETAIL__ROBOT_MSG__TRAITS_HPP_
