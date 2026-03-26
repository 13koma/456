// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from jaka_msgs:srv/ServoMove.idl
// generated code does not contain a copyright notice

#ifndef JAKA_MSGS__SRV__DETAIL__SERVO_MOVE__TRAITS_HPP_
#define JAKA_MSGS__SRV__DETAIL__SERVO_MOVE__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "jaka_msgs/srv/detail/servo_move__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace jaka_msgs
{

namespace srv
{

inline void to_flow_style_yaml(
  const ServoMove_Request & msg,
  std::ostream & out)
{
  out << "{";
  // member: pose
  {
    if (msg.pose.size() == 0) {
      out << "pose: []";
    } else {
      out << "pose: [";
      size_t pending_items = msg.pose.size();
      for (auto item : msg.pose) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: speed
  {
    if (msg.speed.size() == 0) {
      out << "speed: []";
    } else {
      out << "speed: [";
      size_t pending_items = msg.speed.size();
      for (auto item : msg.speed) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const ServoMove_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: pose
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.pose.size() == 0) {
      out << "pose: []\n";
    } else {
      out << "pose:\n";
      for (auto item : msg.pose) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: speed
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.speed.size() == 0) {
      out << "speed: []\n";
    } else {
      out << "speed:\n";
      for (auto item : msg.speed) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const ServoMove_Request & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace srv

}  // namespace jaka_msgs

namespace rosidl_generator_traits
{

[[deprecated("use jaka_msgs::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const jaka_msgs::srv::ServoMove_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  jaka_msgs::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use jaka_msgs::srv::to_yaml() instead")]]
inline std::string to_yaml(const jaka_msgs::srv::ServoMove_Request & msg)
{
  return jaka_msgs::srv::to_yaml(msg);
}

template<>
inline const char * data_type<jaka_msgs::srv::ServoMove_Request>()
{
  return "jaka_msgs::srv::ServoMove_Request";
}

template<>
inline const char * name<jaka_msgs::srv::ServoMove_Request>()
{
  return "jaka_msgs/srv/ServoMove_Request";
}

template<>
struct has_fixed_size<jaka_msgs::srv::ServoMove_Request>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<jaka_msgs::srv::ServoMove_Request>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<jaka_msgs::srv::ServoMove_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace jaka_msgs
{

namespace srv
{

inline void to_flow_style_yaml(
  const ServoMove_Response & msg,
  std::ostream & out)
{
  out << "{";
  // member: ret
  {
    out << "ret: ";
    rosidl_generator_traits::value_to_yaml(msg.ret, out);
    out << ", ";
  }

  // member: message
  {
    out << "message: ";
    rosidl_generator_traits::value_to_yaml(msg.message, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const ServoMove_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: ret
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "ret: ";
    rosidl_generator_traits::value_to_yaml(msg.ret, out);
    out << "\n";
  }

  // member: message
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "message: ";
    rosidl_generator_traits::value_to_yaml(msg.message, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const ServoMove_Response & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace srv

}  // namespace jaka_msgs

namespace rosidl_generator_traits
{

[[deprecated("use jaka_msgs::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const jaka_msgs::srv::ServoMove_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  jaka_msgs::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use jaka_msgs::srv::to_yaml() instead")]]
inline std::string to_yaml(const jaka_msgs::srv::ServoMove_Response & msg)
{
  return jaka_msgs::srv::to_yaml(msg);
}

template<>
inline const char * data_type<jaka_msgs::srv::ServoMove_Response>()
{
  return "jaka_msgs::srv::ServoMove_Response";
}

template<>
inline const char * name<jaka_msgs::srv::ServoMove_Response>()
{
  return "jaka_msgs/srv/ServoMove_Response";
}

template<>
struct has_fixed_size<jaka_msgs::srv::ServoMove_Response>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<jaka_msgs::srv::ServoMove_Response>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<jaka_msgs::srv::ServoMove_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<jaka_msgs::srv::ServoMove>()
{
  return "jaka_msgs::srv::ServoMove";
}

template<>
inline const char * name<jaka_msgs::srv::ServoMove>()
{
  return "jaka_msgs/srv/ServoMove";
}

template<>
struct has_fixed_size<jaka_msgs::srv::ServoMove>
  : std::integral_constant<
    bool,
    has_fixed_size<jaka_msgs::srv::ServoMove_Request>::value &&
    has_fixed_size<jaka_msgs::srv::ServoMove_Response>::value
  >
{
};

template<>
struct has_bounded_size<jaka_msgs::srv::ServoMove>
  : std::integral_constant<
    bool,
    has_bounded_size<jaka_msgs::srv::ServoMove_Request>::value &&
    has_bounded_size<jaka_msgs::srv::ServoMove_Response>::value
  >
{
};

template<>
struct is_service<jaka_msgs::srv::ServoMove>
  : std::true_type
{
};

template<>
struct is_service_request<jaka_msgs::srv::ServoMove_Request>
  : std::true_type
{
};

template<>
struct is_service_response<jaka_msgs::srv::ServoMove_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

#endif  // JAKA_MSGS__SRV__DETAIL__SERVO_MOVE__TRAITS_HPP_
