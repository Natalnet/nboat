#ifndef _ROS_SERVICE_ClearWaypoints_h
#define _ROS_SERVICE_ClearWaypoints_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace uuv_control_msgs
{

static const char CLEARWAYPOINTS[] = "uuv_control_msgs/ClearWaypoints";

  class ClearWaypointsRequest : public ros::Msg
  {
    public:

    ClearWaypointsRequest()
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

    const char * getType(){ return CLEARWAYPOINTS; };
    const char * getMD5(){ return "d41d8cd98f00b204e9800998ecf8427e"; };

  };

  class ClearWaypointsResponse : public ros::Msg
  {
    public:
      typedef bool _success_type;
      _success_type success;

    ClearWaypointsResponse():
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

    const char * getType(){ return CLEARWAYPOINTS; };
    const char * getMD5(){ return "358e233cde0c8a8bcfea4ce193f8fc15"; };

  };

  class ClearWaypoints {
    public:
    typedef ClearWaypointsRequest Request;
    typedef ClearWaypointsResponse Response;
  };

}
#endif
