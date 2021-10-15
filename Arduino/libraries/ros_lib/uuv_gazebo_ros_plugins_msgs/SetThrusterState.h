#ifndef _ROS_SERVICE_SetThrusterState_h
#define _ROS_SERVICE_SetThrusterState_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace uuv_gazebo_ros_plugins_msgs
{

static const char SETTHRUSTERSTATE[] = "uuv_gazebo_ros_plugins_msgs/SetThrusterState";

  class SetThrusterStateRequest : public ros::Msg
  {
    public:
      typedef bool _on_type;
      _on_type on;

    SetThrusterStateRequest():
      on(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_on;
      u_on.real = this->on;
      *(outbuffer + offset + 0) = (u_on.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->on);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_on;
      u_on.base = 0;
      u_on.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->on = u_on.real;
      offset += sizeof(this->on);
     return offset;
    }

    const char * getType(){ return SETTHRUSTERSTATE; };
    const char * getMD5(){ return "74983d2ffe4877de8ae30b7a94625c41"; };

  };

  class SetThrusterStateResponse : public ros::Msg
  {
    public:
      typedef bool _success_type;
      _success_type success;

    SetThrusterStateResponse():
      success(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_success;
      u_success.real = this->success;
      *(outbuffer + offset + 0) = (u_success.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->success);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_success;
      u_success.base = 0;
      u_success.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->success = u_success.real;
      offset += sizeof(this->success);
     return offset;
    }

    const char * getType(){ return SETTHRUSTERSTATE; };
    const char * getMD5(){ return "358e233cde0c8a8bcfea4ce193f8fc15"; };

  };

  class SetThrusterState {
    public:
    typedef SetThrusterStateRequest Request;
    typedef SetThrusterStateResponse Response;
  };

}
#endif
