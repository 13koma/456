// generated from rosidl_typesupport_introspection_cpp/resource/idl__type_support.cpp.em
// with input from jaka_msgs:srv/GetIK.idl
// generated code does not contain a copyright notice

#include "array"
#include "cstddef"
#include "string"
#include "vector"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_interface/macros.h"
#include "jaka_msgs/srv/detail/get_ik__struct.hpp"
#include "rosidl_typesupport_introspection_cpp/field_types.hpp"
#include "rosidl_typesupport_introspection_cpp/identifier.hpp"
#include "rosidl_typesupport_introspection_cpp/message_introspection.hpp"
#include "rosidl_typesupport_introspection_cpp/message_type_support_decl.hpp"
#include "rosidl_typesupport_introspection_cpp/visibility_control.h"

namespace jaka_msgs
{

namespace srv
{

namespace rosidl_typesupport_introspection_cpp
{

void GetIK_Request_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) jaka_msgs::srv::GetIK_Request(_init);
}

void GetIK_Request_fini_function(void * message_memory)
{
  auto typed_message = static_cast<jaka_msgs::srv::GetIK_Request *>(message_memory);
  typed_message->~GetIK_Request();
}

size_t size_function__GetIK_Request__ref_joint(const void * untyped_member)
{
  const auto * member = reinterpret_cast<const std::vector<float> *>(untyped_member);
  return member->size();
}

const void * get_const_function__GetIK_Request__ref_joint(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::vector<float> *>(untyped_member);
  return &member[index];
}

void * get_function__GetIK_Request__ref_joint(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::vector<float> *>(untyped_member);
  return &member[index];
}

void fetch_function__GetIK_Request__ref_joint(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const float *>(
    get_const_function__GetIK_Request__ref_joint(untyped_member, index));
  auto & value = *reinterpret_cast<float *>(untyped_value);
  value = item;
}

void assign_function__GetIK_Request__ref_joint(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<float *>(
    get_function__GetIK_Request__ref_joint(untyped_member, index));
  const auto & value = *reinterpret_cast<const float *>(untyped_value);
  item = value;
}

void resize_function__GetIK_Request__ref_joint(void * untyped_member, size_t size)
{
  auto * member =
    reinterpret_cast<std::vector<float> *>(untyped_member);
  member->resize(size);
}

size_t size_function__GetIK_Request__cartesian_pose(const void * untyped_member)
{
  const auto * member = reinterpret_cast<const std::vector<float> *>(untyped_member);
  return member->size();
}

const void * get_const_function__GetIK_Request__cartesian_pose(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::vector<float> *>(untyped_member);
  return &member[index];
}

void * get_function__GetIK_Request__cartesian_pose(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::vector<float> *>(untyped_member);
  return &member[index];
}

void fetch_function__GetIK_Request__cartesian_pose(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const float *>(
    get_const_function__GetIK_Request__cartesian_pose(untyped_member, index));
  auto & value = *reinterpret_cast<float *>(untyped_value);
  value = item;
}

void assign_function__GetIK_Request__cartesian_pose(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<float *>(
    get_function__GetIK_Request__cartesian_pose(untyped_member, index));
  const auto & value = *reinterpret_cast<const float *>(untyped_value);
  item = value;
}

void resize_function__GetIK_Request__cartesian_pose(void * untyped_member, size_t size)
{
  auto * member =
    reinterpret_cast<std::vector<float> *>(untyped_member);
  member->resize(size);
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember GetIK_Request_message_member_array[2] = {
  {
    "ref_joint",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(jaka_msgs::srv::GetIK_Request, ref_joint),  // bytes offset in struct
    nullptr,  // default value
    size_function__GetIK_Request__ref_joint,  // size() function pointer
    get_const_function__GetIK_Request__ref_joint,  // get_const(index) function pointer
    get_function__GetIK_Request__ref_joint,  // get(index) function pointer
    fetch_function__GetIK_Request__ref_joint,  // fetch(index, &value) function pointer
    assign_function__GetIK_Request__ref_joint,  // assign(index, value) function pointer
    resize_function__GetIK_Request__ref_joint  // resize(index) function pointer
  },
  {
    "cartesian_pose",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(jaka_msgs::srv::GetIK_Request, cartesian_pose),  // bytes offset in struct
    nullptr,  // default value
    size_function__GetIK_Request__cartesian_pose,  // size() function pointer
    get_const_function__GetIK_Request__cartesian_pose,  // get_const(index) function pointer
    get_function__GetIK_Request__cartesian_pose,  // get(index) function pointer
    fetch_function__GetIK_Request__cartesian_pose,  // fetch(index, &value) function pointer
    assign_function__GetIK_Request__cartesian_pose,  // assign(index, value) function pointer
    resize_function__GetIK_Request__cartesian_pose  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers GetIK_Request_message_members = {
  "jaka_msgs::srv",  // message namespace
  "GetIK_Request",  // message name
  2,  // number of fields
  sizeof(jaka_msgs::srv::GetIK_Request),
  GetIK_Request_message_member_array,  // message members
  GetIK_Request_init_function,  // function to initialize message memory (memory has to be allocated)
  GetIK_Request_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t GetIK_Request_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &GetIK_Request_message_members,
  get_message_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_introspection_cpp

}  // namespace srv

}  // namespace jaka_msgs


namespace rosidl_typesupport_introspection_cpp
{

template<>
ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<jaka_msgs::srv::GetIK_Request>()
{
  return &::jaka_msgs::srv::rosidl_typesupport_introspection_cpp::GetIK_Request_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, jaka_msgs, srv, GetIK_Request)() {
  return &::jaka_msgs::srv::rosidl_typesupport_introspection_cpp::GetIK_Request_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif

// already included above
// #include "array"
// already included above
// #include "cstddef"
// already included above
// #include "string"
// already included above
// #include "vector"
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "rosidl_typesupport_cpp/message_type_support.hpp"
// already included above
// #include "rosidl_typesupport_interface/macros.h"
// already included above
// #include "jaka_msgs/srv/detail/get_ik__struct.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/field_types.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/identifier.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/message_introspection.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/message_type_support_decl.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/visibility_control.h"

namespace jaka_msgs
{

namespace srv
{

namespace rosidl_typesupport_introspection_cpp
{

void GetIK_Response_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) jaka_msgs::srv::GetIK_Response(_init);
}

void GetIK_Response_fini_function(void * message_memory)
{
  auto typed_message = static_cast<jaka_msgs::srv::GetIK_Response *>(message_memory);
  typed_message->~GetIK_Response();
}

size_t size_function__GetIK_Response__joint(const void * untyped_member)
{
  const auto * member = reinterpret_cast<const std::vector<float> *>(untyped_member);
  return member->size();
}

const void * get_const_function__GetIK_Response__joint(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::vector<float> *>(untyped_member);
  return &member[index];
}

void * get_function__GetIK_Response__joint(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::vector<float> *>(untyped_member);
  return &member[index];
}

void fetch_function__GetIK_Response__joint(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const float *>(
    get_const_function__GetIK_Response__joint(untyped_member, index));
  auto & value = *reinterpret_cast<float *>(untyped_value);
  value = item;
}

void assign_function__GetIK_Response__joint(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<float *>(
    get_function__GetIK_Response__joint(untyped_member, index));
  const auto & value = *reinterpret_cast<const float *>(untyped_value);
  item = value;
}

void resize_function__GetIK_Response__joint(void * untyped_member, size_t size)
{
  auto * member =
    reinterpret_cast<std::vector<float> *>(untyped_member);
  member->resize(size);
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember GetIK_Response_message_member_array[2] = {
  {
    "joint",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(jaka_msgs::srv::GetIK_Response, joint),  // bytes offset in struct
    nullptr,  // default value
    size_function__GetIK_Response__joint,  // size() function pointer
    get_const_function__GetIK_Response__joint,  // get_const(index) function pointer
    get_function__GetIK_Response__joint,  // get(index) function pointer
    fetch_function__GetIK_Response__joint,  // fetch(index, &value) function pointer
    assign_function__GetIK_Response__joint,  // assign(index, value) function pointer
    resize_function__GetIK_Response__joint  // resize(index) function pointer
  },
  {
    "message",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(jaka_msgs::srv::GetIK_Response, message),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers GetIK_Response_message_members = {
  "jaka_msgs::srv",  // message namespace
  "GetIK_Response",  // message name
  2,  // number of fields
  sizeof(jaka_msgs::srv::GetIK_Response),
  GetIK_Response_message_member_array,  // message members
  GetIK_Response_init_function,  // function to initialize message memory (memory has to be allocated)
  GetIK_Response_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t GetIK_Response_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &GetIK_Response_message_members,
  get_message_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_introspection_cpp

}  // namespace srv

}  // namespace jaka_msgs


namespace rosidl_typesupport_introspection_cpp
{

template<>
ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<jaka_msgs::srv::GetIK_Response>()
{
  return &::jaka_msgs::srv::rosidl_typesupport_introspection_cpp::GetIK_Response_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, jaka_msgs, srv, GetIK_Response)() {
  return &::jaka_msgs::srv::rosidl_typesupport_introspection_cpp::GetIK_Response_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif

#include "rosidl_runtime_c/service_type_support_struct.h"
// already included above
// #include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_cpp/service_type_support.hpp"
// already included above
// #include "rosidl_typesupport_interface/macros.h"
// already included above
// #include "rosidl_typesupport_introspection_cpp/visibility_control.h"
// already included above
// #include "jaka_msgs/srv/detail/get_ik__struct.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/identifier.hpp"
// already included above
// #include "rosidl_typesupport_introspection_cpp/message_type_support_decl.hpp"
#include "rosidl_typesupport_introspection_cpp/service_introspection.hpp"
#include "rosidl_typesupport_introspection_cpp/service_type_support_decl.hpp"

namespace jaka_msgs
{

namespace srv
{

namespace rosidl_typesupport_introspection_cpp
{

// this is intentionally not const to allow initialization later to prevent an initialization race
static ::rosidl_typesupport_introspection_cpp::ServiceMembers GetIK_service_members = {
  "jaka_msgs::srv",  // service namespace
  "GetIK",  // service name
  // these two fields are initialized below on the first access
  // see get_service_type_support_handle<jaka_msgs::srv::GetIK>()
  nullptr,  // request message
  nullptr  // response message
};

static const rosidl_service_type_support_t GetIK_service_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &GetIK_service_members,
  get_service_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_introspection_cpp

}  // namespace srv

}  // namespace jaka_msgs


namespace rosidl_typesupport_introspection_cpp
{

template<>
ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_service_type_support_t *
get_service_type_support_handle<jaka_msgs::srv::GetIK>()
{
  // get a handle to the value to be returned
  auto service_type_support =
    &::jaka_msgs::srv::rosidl_typesupport_introspection_cpp::GetIK_service_type_support_handle;
  // get a non-const and properly typed version of the data void *
  auto service_members = const_cast<::rosidl_typesupport_introspection_cpp::ServiceMembers *>(
    static_cast<const ::rosidl_typesupport_introspection_cpp::ServiceMembers *>(
      service_type_support->data));
  // make sure that both the request_members_ and the response_members_ are initialized
  // if they are not, initialize them
  if (
    service_members->request_members_ == nullptr ||
    service_members->response_members_ == nullptr)
  {
    // initialize the request_members_ with the static function from the external library
    service_members->request_members_ = static_cast<
      const ::rosidl_typesupport_introspection_cpp::MessageMembers *
      >(
      ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<
        ::jaka_msgs::srv::GetIK_Request
      >()->data
      );
    // initialize the response_members_ with the static function from the external library
    service_members->response_members_ = static_cast<
      const ::rosidl_typesupport_introspection_cpp::MessageMembers *
      >(
      ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<
        ::jaka_msgs::srv::GetIK_Response
      >()->data
      );
  }
  // finally return the properly initialized service_type_support handle
  return service_type_support;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, jaka_msgs, srv, GetIK)() {
  return ::rosidl_typesupport_introspection_cpp::get_service_type_support_handle<jaka_msgs::srv::GetIK>();
}

#ifdef __cplusplus
}
#endif
