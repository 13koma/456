// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from jaka_msgs:srv/SetPayload.idl
// generated code does not contain a copyright notice

#ifndef JAKA_MSGS__SRV__DETAIL__SET_PAYLOAD__TRAITS_HPP_
#define JAKA_MSGS__SRV__DETAIL__SET_PAYLOAD__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "jaka_msgs/srv/detail/set_payload__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace jaka_msgs
{

namespace srv
{

inline void to_flow_style_yaml(
  const SetPayload_Request & msg,
  std::ostream & out)
{
  out << "{";
  // member: tool_num
  {
    out << "tool_num: ";
    rosidl_generator_traits::value_to_yaml(msg.tool_num, out);
    out << ", ";
  }

  // member: mass
  {
    out << "mass: ";
    rosidl_generator_traits::value_to_yaml(msg.mass, out);
    out << ", ";
  }

  // member: xc
  {
    out << "xc: ";
    rosidl_generator_traits::value_to_yaml(msg.xc, out);
    out << ", ";
  }

  // member: yc
  {
    out << "yc: ";
    rosidl_generator_traits::value_to_yaml(msg.yc, out);
    out << ", ";
  }

  // member: zc
  {
    out << "zc: ";
    rosidl_generator_traits::value_to_yaml(msg.zc, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const SetPayload_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: tool_num
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "tool_num: ";
    rosidl_generator_traits::value_to_yaml(msg.tool_num, out);
    out << "\n";
  }

  // member: mass
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "mass: ";
    rosidl_generator_traits::value_to_yaml(msg.mass, out);
    out << "\n";
  }

  // member: xc
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "xc: ";
    rosidl_generator_traits::value_to_yaml(msg.xc, out);
    out << "\n";
  }

  // member: yc
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "yc: ";
    rosidl_generator_traits::value_to_yaml(msg.yc, out);
    out << "\n";
  }

  // member: zc
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "zc: ";
    rosidl_generator_traits::value_to_yaml(msg.zc, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const SetPayload_Request & msg, bool use_flow_style = false)
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
  const jaka_msgs::srv::SetPayload_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  jaka_msgs::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use jaka_msgs::srv::to_yaml() instead")]]
inline std::string to_yaml(const jaka_msgs::srv::SetPayload_Request & msg)
{
  return jaka_msgs::srv::to_yaml(msg);
}

template<>
inline const char * data_type<jaka_msgs::srv::SetPayload_Request>()
{
  return "jaka_msgs::srv::SetPayload_Request";
}

template<>
inline const char * name<jaka_msgs::srv::SetPayload_Request>()
{
  return "jaka_msgs/srv/SetPayload_Request";
}

template<>
struct has_fixed_size<jaka_msgs::srv::SetPayload_Request>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<jaka_msgs::srv::SetPayload_Request>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<jaka_msgs::srv::SetPayload_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace jaka_msgs
{

namespace srv
{

inline void to_flow_style_yaml(
  const SetPayload_Response & msg,
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
  const SetPayload_Response & msg,
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

inline std::string to_yaml(const SetPayload_Response & msg, bool use_flow_style = false)
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
  const jaka_msgs::srv::SetPayload_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  jaka_msgs::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use jaka_msgs::srv::to_yaml() instead")]]
inline std::string to_yaml(const jaka_msgs::srv::SetPayload_Response & msg)
{
  return jaka_msgs::srv::to_yaml(msg);
}

template<>
inline const char * data_type<jaka_msgs::srv::SetPayload_Response>()
{
  return "jaka_msgs::srv::SetPayload_Response";
}

template<>
inline const char * name<jaka_msgs::srv::SetPayload_Response>()
{
  return "jaka_msgs/srv/SetPayload_Response";
}

template<>
struct has_fixed_size<jaka_msgs::srv::SetPayload_Response>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<jaka_msgs::srv::SetPayload_Response>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<jaka_msgs::srv::SetPayload_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<jaka_msgs::srv::SetPayload>()
{
  return "jaka_msgs::srv::SetPayload";
}

template<>
inline const char * name<jaka_msgs::srv::SetPayload>()
{
  return "jaka_msgs/srv/SetPayload";
}

template<>
struct has_fixed_size<jaka_msgs::srv::SetPayload>
  : std::integral_constant<
    bool,
    has_fixed_size<jaka_msgs::srv::SetPayload_Request>::value &&
    has_fixed_size<jaka_msgs::srv::SetPayload_Response>::value
  >
{
};

template<>
struct has_bounded_size<jaka_msgs::srv::SetPayload>
  : std::integral_constant<
    bool,
    has_bounded_size<jaka_msgs::srv::SetPayload_Request>::value &&
    has_bounded_size<jaka_msgs::srv::SetPayload_Response>::value
  >
{
};

template<>
struct is_service<jaka_msgs::srv::SetPayload>
  : std::true_type
{
};

template<>
struct is_service_request<jaka_msgs::srv::SetPayload_Request>
  : std::true_type
{
};

template<>
struct is_service_response<jaka_msgs::srv::SetPayload_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

#endif  // JAKA_MSGS__SRV__DETAIL__SET_PAYLOAD__TRAITS_HPP_
