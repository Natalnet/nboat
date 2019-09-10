#ifndef _ROS_SERVICE_SetCurrentDirection_h
#define _ROS_SERVICE_SetCurrentDirection_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace uuv_world_ros_plugins_msgs
{

static const char SETCURRENTDIRECTION[] = "uuv_world_ros_plugins_msgs/SetCurrentDirection";

  class SetCurrentDirectionRequest : public ros::Msg
  {
    public:
      typedef float _angle_type;
      _angle_type angle;

    SetCurrentDirectionRequest():
      angle(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += serializeAvrFloat64(outbuffer + offset, this->angle);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->angle));
     return offset;
    }

    const char * getType(){ return SETCURRENTDIRECTION; };
    const char * getMD5(){ return "4edb55038e2b888976a0c0c56935341c"; };

  };

  class SetCurrentDirectionResponse : public ros::Msg
  {
    public:
      typedef bool _success_type;
      _success_type success;

    SetCurrentDirectionResponse():
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

    const char * getType(){ return SETCURRENTDIRECTION; };
    const char * getMD5(){ return "358e233cde0c8a8bcfea4ce193f8fc15"; };

  };

  class SetCurrentDirection {
    public:
    typedef SetCurrentDirectionRequest Request;
    typedef SetCurrentDirectionResponse Response;
  };

}
#endif
