// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from jaka_msgs:srv/GetIO.idl
// generated code does not contain a copyright notice

#ifndef JAKA_MSGS__SRV__DETAIL__GET_IO__TRAITS_HPP_
#define JAKA_MSGS__SRV__DETAIL__GET_IO__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "jaka_msgs/srv/detail/get_io__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace jaka_msgs
{

namespace srv
{

inline void to_flow_style_yaml(
  const GetIO_Request & msg,
  std::ostream & out)
{
  out << "{";
  // member: signal
  {
    out << "signal: ";
    rosidl_generator_traits::value_to_yaml(msg.signal, out);
    out << ", ";
  }

  // member: path
  {
    out << "path: ";
    rosidl_generator_traits::value_to_yaml(msg.path, out);
    out << ", ";
  }

  // member: type
  {
    out << "type: ";
    rosidl_generator_traits::value_to_yaml(msg.type, out);
    out << ", ";
  }

  // member: index
  {
    out << "index: ";
    rosidl_generator_traits::value_to_yaml(msg.index, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const GetIO_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: signal
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "signal: ";
    rosidl_generator_traits::value_to_yaml(msg.signal, out);
    out << "\n";
  }

  // member: path
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "path: ";
    rosidl_generator_traits::value_to_yaml(msg.path, out);
    out << "\n";
  }

  // member: type
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "type: ";
    rosidl_generator_traits::value_to_yaml(msg.type, out);
    out << "\n";
  }

  // member: index
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "index: ";
    rosidl_generator_traits::value_to_yaml(msg.index, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const GetIO_Request & msg, bool use_flow_style = false)
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
  const jaka_msgs::srv::GetIO_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  jaka_msgs::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use jaka_msgs::srv::to_yaml() instead")]]
inline std::string to_yaml(const jaka_msgs::srv::GetIO_Request & msg)
{
  return jaka_msgs::srv::to_yaml(msg);
}

template<>
inline const char * data_type<jaka_msgs::srv::GetIO_Request>()
{
  return "jaka_msgs::srv::GetIO_Request";
}

template<>
inline const char * name<jaka_msgs::srv::GetIO_Request>()
{
  return "jaka_msgs/srv/GetIO_Request";
}

template<>
struct has_fixed_size<jaka_msgs::srv::GetIO_Request>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<jaka_msgs::srv::GetIO_Request>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<jaka_msgs::srv::GetIO_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace jaka_msgs
{

namespace srv
{

inline void to_flow_style_yaml(
  const GetIO_Response & msg,
  std::ostream & out)
{
  out << "{";
  // member: value
  {
    out << "value: ";
    rosidl_generator_traits::value_to_yaml(msg.value, out);
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
  const GetIO_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: value
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "value: ";
    rosidl_generator_traits::value_to_yaml(msg.value, out);
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

inline std::string to_yaml(const GetIO_Response & msg, bool use_flow_style = false)
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
  const jaka_msgs::srv::GetIO_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  jaka_msgs::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use jaka_msgs::srv::to_yaml() instead")]]
inline std::string to_yaml(const jaka_msgs::srv::GetIO_Response & msg)
{
  return jaka_msgs::srv::to_yaml(msg);
}

template<>
inline const char * data_type<jaka_msgs::srv::GetIO_Response>()
{
  return "jaka_msgs::srv::GetIO_Response";
}

template<>
inline const char * name<jaka_msgs::srv::GetIO_Response>()
{
  return "jaka_msgs/srv/GetIO_Response";
}

template<>
struct has_fixed_size<jaka_msgs::srv::GetIO_Response>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<jaka_msgs::srv::GetIO_Response>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<jaka_msgs::srv::GetIO_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<jaka_msgs::srv::GetIO>()
{
  return "jaka_msgs::srv::GetIO";
}

template<>
inline const char * name<jaka_msgs::srv::GetIO>()
{
  return "jaka_msgs/srv/GetIO";
}

template<>
struct has_fixed_size<jaka_msgs::srv::GetIO>
  : std::integral_constant<
    bool,
    has_fixed_size<jaka_msgs::srv::GetIO_Request>::value &&
    has_fixed_size<jaka_msgs::srv::GetIO_Response>::value
  >
{
};

template<>
struct has_bounded_size<jaka_msgs::srv::GetIO>
  : std::integral_constant<
    bool,
    has_bounded_size<jaka_msgs::srv::GetIO_Request>::value &&
    has_bounded_size<jaka_msgs::srv::GetIO_Response>::value
  >
{
};

template<>
struct is_service<jaka_msgs::srv::GetIO>
  : std::true_type
{
};

template<>
struct is_service_request<jaka_msgs::srv::GetIO_Request>
  : std::true_type
{
};

template<>
struct is_service_response<jaka_msgs::srv::GetIO_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

#endif  // JAKA_MSGS__SRV__DETAIL__GET_IO__TRAITS_HPP_
