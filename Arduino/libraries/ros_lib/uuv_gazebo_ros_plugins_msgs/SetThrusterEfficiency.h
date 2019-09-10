#ifndef _ROS_SERVICE_SetThrusterEfficiency_h
#define _ROS_SERVICE_SetThrusterEfficiency_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace uuv_gazebo_ros_plugins_msgs
{

static const char SETTHRUSTEREFFICIENCY[] = "uuv_gazebo_ros_plugins_msgs/SetThrusterEfficiency";

  class SetThrusterEfficiencyRequest : public ros::Msg
  {
    public:
      typedef float _efficiency_type;
      _efficiency_type efficiency;

    SetThrusterEfficiencyRequest():
      efficiency(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += serializeAvrFloat64(outbuffer + offset, this->efficiency);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->efficiency));
     return offset;
    }

    const char * getType(){ return SETTHRUSTEREFFICIENCY; };
    const char * getMD5(){ return "b80ec71e671b93e4cc403df1ac4c8a86"; };

  };

  class SetThrusterEfficiencyResponse : public ros::Msg
  {
    public:
      typedef bool _success_type;
      _success_type success;

    SetThrusterEfficiencyResponse():
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

    const char * getType(){ return SETTHRUSTEREFFICIENCY; };
    const char * getMD5(){ return "358e233cde0c8a8bcfea4ce193f8fc15"; };

  };

  class SetThrusterEfficiency {
    public:
    typedef SetThrusterEfficiencyRequest Request;
    typedef SetThrusterEfficiencyResponse Response;
  };

}
#endif
