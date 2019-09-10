#ifndef _ROS_SERVICE_SetUseGlobalCurrentVel_h
#define _ROS_SERVICE_SetUseGlobalCurrentVel_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace uuv_gazebo_ros_plugins_msgs
{

static const char SETUSEGLOBALCURRENTVEL[] = "uuv_gazebo_ros_plugins_msgs/SetUseGlobalCurrentVel";

  class SetUseGlobalCurrentVelRequest : public ros::Msg
  {
    public:
      typedef bool _use_global_type;
      _use_global_type use_global;

    SetUseGlobalCurrentVelRequest():
      use_global(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_use_global;
      u_use_global.real = this->use_global;
      *(outbuffer + offset + 0) = (u_use_global.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->use_global);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_use_global;
      u_use_global.base = 0;
      u_use_global.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->use_global = u_use_global.real;
      offset += sizeof(this->use_global);
     return offset;
    }

    const char * getType(){ return SETUSEGLOBALCURRENTVEL; };
    const char * getMD5(){ return "cb3581ad5adb4e1f612596312cf9e4fe"; };

  };

  class SetUseGlobalCurrentVelResponse : public ros::Msg
  {
    public:
      typedef bool _success_type;
      _success_type success;

    SetUseGlobalCurrentVelResponse():
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

    const char * getType(){ return SETUSEGLOBALCURRENTVEL; };
    const char * getMD5(){ return "358e233cde0c8a8bcfea4ce193f8fc15"; };

  };

  class SetUseGlobalCurrentVel {
    public:
    typedef SetUseGlobalCurrentVelRequest Request;
    typedef SetUseGlobalCurrentVelResponse Response;
  };

}
#endif
