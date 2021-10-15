#ifndef _ROS_SERVICE_GetThrusterState_h
#define _ROS_SERVICE_GetThrusterState_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace uuv_gazebo_ros_plugins_msgs
{

static const char GETTHRUSTERSTATE[] = "uuv_gazebo_ros_plugins_msgs/GetThrusterState";

  class GetThrusterStateRequest : public ros::Msg
  {
    public:

    GetThrusterStateRequest()
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

    const char * getType(){ return GETTHRUSTERSTATE; };
    const char * getMD5(){ return "d41d8cd98f00b204e9800998ecf8427e"; };

  };

  class GetThrusterStateResponse : public ros::Msg
  {
    public:
      typedef bool _is_on_type;
      _is_on_type is_on;

    GetThrusterStateResponse():
      is_on(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_is_on;
      u_is_on.real = this->is_on;
      *(outbuffer + offset + 0) = (u_is_on.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->is_on);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_is_on;
      u_is_on.base = 0;
      u_is_on.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->is_on = u_is_on.real;
      offset += sizeof(this->is_on);
     return offset;
    }

    const char * getType(){ return GETTHRUSTERSTATE; };
    const char * getMD5(){ return "e2fdda8431274beee70eebaa081c813e"; };

  };

  class GetThrusterState {
    public:
    typedef GetThrusterStateRequest Request;
    typedef GetThrusterStateResponse Response;
  };

}
#endif
