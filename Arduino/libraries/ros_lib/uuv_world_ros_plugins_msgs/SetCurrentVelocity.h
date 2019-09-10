#ifndef _ROS_SERVICE_SetCurrentVelocity_h
#define _ROS_SERVICE_SetCurrentVelocity_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace uuv_world_ros_plugins_msgs
{

static const char SETCURRENTVELOCITY[] = "uuv_world_ros_plugins_msgs/SetCurrentVelocity";

  class SetCurrentVelocityRequest : public ros::Msg
  {
    public:
      typedef float _velocity_type;
      _velocity_type velocity;
      typedef float _horizontal_angle_type;
      _horizontal_angle_type horizontal_angle;
      typedef float _vertical_angle_type;
      _vertical_angle_type vertical_angle;

    SetCurrentVelocityRequest():
      velocity(0),
      horizontal_angle(0),
      vertical_angle(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += serializeAvrFloat64(outbuffer + offset, this->velocity);
      offset += serializeAvrFloat64(outbuffer + offset, this->horizontal_angle);
      offset += serializeAvrFloat64(outbuffer + offset, this->vertical_angle);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->velocity));
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->horizontal_angle));
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->vertical_angle));
     return offset;
    }

    const char * getType(){ return SETCURRENTVELOCITY; };
    const char * getMD5(){ return "44059aaf9c13a2ec083fad30e8a17ee3"; };

  };

  class SetCurrentVelocityResponse : public ros::Msg
  {
    public:
      typedef bool _success_type;
      _success_type success;

    SetCurrentVelocityResponse():
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

    const char * getType(){ return SETCURRENTVELOCITY; };
    const char * getMD5(){ return "358e233cde0c8a8bcfea4ce193f8fc15"; };

  };

  class SetCurrentVelocity {
    public:
    typedef SetCurrentVelocityRequest Request;
    typedef SetCurrentVelocityResponse Response;
  };

}
#endif
