#ifndef _ROS_SERVICE_SwitchToManual_h
#define _ROS_SERVICE_SwitchToManual_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace uuv_control_msgs
{

static const char SWITCHTOMANUAL[] = "uuv_control_msgs/SwitchToManual";

  class SwitchToManualRequest : public ros::Msg
  {
    public:

    SwitchToManualRequest()
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

    const char * getType(){ return SWITCHTOMANUAL; };
    const char * getMD5(){ return "d41d8cd98f00b204e9800998ecf8427e"; };

  };

  class SwitchToManualResponse : public ros::Msg
  {
    public:
      typedef bool _success_type;
      _success_type success;

    SwitchToManualResponse():
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

    const char * getType(){ return SWITCHTOMANUAL; };
    const char * getMD5(){ return "358e233cde0c8a8bcfea4ce193f8fc15"; };

  };

  class SwitchToManual {
    public:
    typedef SwitchToManualRequest Request;
    typedef SwitchToManualResponse Response;
  };

}
#endif
