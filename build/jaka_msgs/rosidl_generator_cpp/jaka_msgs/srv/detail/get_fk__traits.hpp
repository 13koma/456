// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from jaka_msgs:srv/GetFK.idl
// generated code does not contain a copyright notice

#ifndef JAKA_MSGS__SRV__DETAIL__GET_FK__TRAITS_HPP_
#define JAKA_MSGS__SRV__DETAIL__GET_FK__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "jaka_msgs/srv/detail/get_fk__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace jaka_msgs
{

namespace srv
{

inline void to_flow_style_yaml(
  const GetFK_Request & msg,
  std::ostream & out)
{
  out << "{";
  // member: joint
  {
    if (msg.joint.size() == 0) {
      out << "joint: []";
    } else {
      out << "joint: [";
      size_t pending_items = msg.joint.size();
      for (auto item : msg.joint) {
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
  const GetFK_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: joint
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.joint.size() == 0) {
      out << "joint: []\n";
    } else {
      out << "joint:\n";
      for (auto item : msg.joint) {
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

inline std::string to_yaml(const GetFK_Request & msg, bool use_flow_style = false)
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
  const jaka_msgs::srv::GetFK_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  jaka_msgs::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use jaka_msgs::srv::to_yaml() instead")]]
inline std::string to_yaml(const jaka_msgs::srv::GetFK_Request & msg)
{
  return jaka_msgs::srv::to_yaml(msg);
}

template<>
inline const char * data_type<jaka_msgs::srv::GetFK_Request>()
{
  return "jaka_msgs::srv::GetFK_Request";
}

template<>
inline const char * name<jaka_msgs::srv::GetFK_Request>()
{
  return "jaka_msgs/srv/GetFK_Request";
}

template<>
struct has_fixed_size<jaka_msgs::srv::GetFK_Request>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<jaka_msgs::srv::GetFK_Request>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<jaka_msgs::srv::GetFK_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace jaka_msgs
{

namespace srv
{

inline void to_flow_style_yaml(
  const GetFK_Response & msg,
  std::ostream & out)
{
  out << "{";
  // member: cartesian_pose
  {
    if (msg.cartesian_pose.size() == 0) {
      out << "cartesian_pose: []";
    } else {
      out << "cartesian_pose: [";
      size_t pending_items = msg.cartesian_pose.size();
      for (auto item : msg.cartesian_pose) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
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
  const GetFK_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: cartesian_pose
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.cartesian_pose.size() == 0) {
      out << "cartesian_pose: []\n";
    } else {
      out << "cartesian_pose:\n";
      for (auto item : msg.cartesian_pose) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
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

inline std::string to_yaml(const GetFK_Response & msg, bool use_flow_style = false)
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
  const jaka_msgs::srv::GetFK_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  jaka_msgs::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use jaka_msgs::srv::to_yaml() instead")]]
inline std::string to_yaml(const jaka_msgs::srv::GetFK_Response & msg)
{
  return jaka_msgs::srv::to_yaml(msg);
}

template<>
inline const char * data_type<jaka_msgs::srv::GetFK_Response>()
{
  return "jaka_msgs::srv::GetFK_Response";
}

template<>
inline const char * name<jaka_msgs::srv::GetFK_Response>()
{
  return "jaka_msgs/srv/GetFK_Response";
}

template<>
struct has_fixed_size<jaka_msgs::srv::GetFK_Response>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<jaka_msgs::srv::GetFK_Response>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<jaka_msgs::srv::GetFK_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<jaka_msgs::srv::GetFK>()
{
  return "jaka_msgs::srv::GetFK";
}

template<>
inline const char * name<jaka_msgs::srv::GetFK>()
{
  return "jaka_msgs/srv/GetFK";
}

template<>
struct has_fixed_size<jaka_msgs::srv::GetFK>
  : std::integral_constant<
    bool,
    has_fixed_size<jaka_msgs::srv::GetFK_Request>::value &&
    has_fixed_size<jaka_msgs::srv::GetFK_Response>::value
  >
{
};

template<>
struct has_bounded_size<jaka_msgs::srv::GetFK>
  : std::integral_constant<
    bool,
    has_bounded_size<jaka_msgs::srv::GetFK_Request>::value &&
    has_bounded_size<jaka_msgs::srv::GetFK_Response>::value
  >
{
};

template<>
struct is_service<jaka_msgs::srv::GetFK>
  : std::true_type
{
};

template<>
struct is_service_request<jaka_msgs::srv::GetFK_Request>
  : std::true_type
{
};

template<>
struct is_service_response<jaka_msgs::srv::GetFK_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

#endif  // JAKA_MSGS__SRV__DETAIL__GET_FK__TRAITS_HPP_
