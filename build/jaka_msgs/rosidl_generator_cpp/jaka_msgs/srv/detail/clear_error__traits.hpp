// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from jaka_msgs:srv/ClearError.idl
// generated code does not contain a copyright notice

#ifndef JAKA_MSGS__SRV__DETAIL__CLEAR_ERROR__TRAITS_HPP_
#define JAKA_MSGS__SRV__DETAIL__CLEAR_ERROR__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "jaka_msgs/srv/detail/clear_error__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace jaka_msgs
{

namespace srv
{

inline void to_flow_style_yaml(
  const ClearError_Request & msg,
  std::ostream & out)
{
  out << "{";
  // member: enable
  {
    out << "enable: ";
    rosidl_generator_traits::value_to_yaml(msg.enable, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const ClearError_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: enable
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "enable: ";
    rosidl_generator_traits::value_to_yaml(msg.enable, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const ClearError_Request & msg, bool use_flow_style = false)
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
  const jaka_msgs::srv::ClearError_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  jaka_msgs::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use jaka_msgs::srv::to_yaml() instead")]]
inline std::string to_yaml(const jaka_msgs::srv::ClearError_Request & msg)
{
  return jaka_msgs::srv::to_yaml(msg);
}

template<>
inline const char * data_type<jaka_msgs::srv::ClearError_Request>()
{
  return "jaka_msgs::srv::ClearError_Request";
}

template<>
inline const char * name<jaka_msgs::srv::ClearError_Request>()
{
  return "jaka_msgs/srv/ClearError_Request";
}

template<>
struct has_fixed_size<jaka_msgs::srv::ClearError_Request>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<jaka_msgs::srv::ClearError_Request>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<jaka_msgs::srv::ClearError_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace jaka_msgs
{

namespace srv
{

inline void to_flow_style_yaml(
  const ClearError_Response & msg,
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
  const ClearError_Response & msg,
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

inline std::string to_yaml(const ClearError_Response & msg, bool use_flow_style = false)
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
  const jaka_msgs::srv::ClearError_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  jaka_msgs::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use jaka_msgs::srv::to_yaml() instead")]]
inline std::string to_yaml(const jaka_msgs::srv::ClearError_Response & msg)
{
  return jaka_msgs::srv::to_yaml(msg);
}

template<>
inline const char * data_type<jaka_msgs::srv::ClearError_Response>()
{
  return "jaka_msgs::srv::ClearError_Response";
}

template<>
inline const char * name<jaka_msgs::srv::ClearError_Response>()
{
  return "jaka_msgs/srv/ClearError_Response";
}

template<>
struct has_fixed_size<jaka_msgs::srv::ClearError_Response>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<jaka_msgs::srv::ClearError_Response>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<jaka_msgs::srv::ClearError_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<jaka_msgs::srv::ClearError>()
{
  return "jaka_msgs::srv::ClearError";
}

template<>
inline const char * name<jaka_msgs::srv::ClearError>()
{
  return "jaka_msgs/srv/ClearError";
}

template<>
struct has_fixed_size<jaka_msgs::srv::ClearError>
  : std::integral_constant<
    bool,
    has_fixed_size<jaka_msgs::srv::ClearError_Request>::value &&
    has_fixed_size<jaka_msgs::srv::ClearError_Response>::value
  >
{
};

template<>
struct has_bounded_size<jaka_msgs::srv::ClearError>
  : std::integral_constant<
    bool,
    has_bounded_size<jaka_msgs::srv::ClearError_Request>::value &&
    has_bounded_size<jaka_msgs::srv::ClearError_Response>::value
  >
{
};

template<>
struct is_service<jaka_msgs::srv::ClearError>
  : std::true_type
{
};

template<>
struct is_service_request<jaka_msgs::srv::ClearError_Request>
  : std::true_type
{
};

template<>
struct is_service_response<jaka_msgs::srv::ClearError_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

#endif  // JAKA_MSGS__SRV__DETAIL__CLEAR_ERROR__TRAITS_HPP_
