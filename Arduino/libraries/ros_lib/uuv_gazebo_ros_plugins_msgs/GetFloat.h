#ifndef _ROS_SERVICE_GetFloat_h
#define _ROS_SERVICE_GetFloat_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace uuv_gazebo_ros_plugins_msgs
{

static const char GETFLOAT[] = "uuv_gazebo_ros_plugins_msgs/GetFloat";

  class GetFloatRequest : public ros::Msg
  {
    public:

    GetFloatRequest()
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

    const char * getType(){ return GETFLOAT; };
    const char * getMD5(){ return "d41d8cd98f00b204e9800998ecf8427e"; };

  };

  class GetFloatResponse : public ros::Msg
  {
    public:
      typedef float _data_type;
      _data_type data;

    GetFloatResponse():
      data(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += serializeAvrFloat64(outbuffer + offset, this->data);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->data));
     return offset;
    }

    const char * getType(){ return GETFLOAT; };
    const char * getMD5(){ return "fdb28210bfa9d7c91146260178d9a584"; };

  };

  class GetFloat {
    public:
    typedef GetFloatRequest Request;
    typedef GetFloatResponse Response;
  };

}
#endif
