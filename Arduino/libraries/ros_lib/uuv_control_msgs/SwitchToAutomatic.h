#ifndef _ROS_SERVICE_SwitchToAutomatic_h
#define _ROS_SERVICE_SwitchToAutomatic_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace uuv_control_msgs
{

static const char SWITCHTOAUTOMATIC[] = "uuv_control_msgs/SwitchToAutomatic";

  class SwitchToAutomaticRequest : public ros::Msg
  {
    public:

    SwitchToAutomaticRequest()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
     return offset;
    }

    const char * getType(){ return SWITCHTOAUTOMATIC; };
    const char * getMD5(){ return "d41d8cd98f00b204e9800998ecf8427e"; };

  };

  class SwitchToAutomaticResponse : public ros::Msg
  {
    public:
      typedef bool _success_type;
      _success_type success;

    SwitchToAutomaticResponse():
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

    const char * getType(){ return SWITCHTOAUTOMATIC; };
    const char * getMD5(){ return "358e233cde0c8a8bcfea4ce193f8fc15"; };

  };

  class SwitchToAutomatic {
    public:
    typedef SwitchToAutomaticRequest Request;
    typedef SwitchToAutomaticResponse Response;
  };

}
#endif
