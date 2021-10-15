#ifndef _ROS_SERVICE_GetThrusterConversionFcn_h
#define _ROS_SERVICE_GetThrusterConversionFcn_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "uuv_gazebo_ros_plugins_msgs/ThrusterConversionFcn.h"

namespace uuv_gazebo_ros_plugins_msgs
{

static const char GETTHRUSTERCONVERSIONFCN[] = "uuv_gazebo_ros_plugins_msgs/GetThrusterConversionFcn";

  class GetThrusterConversionFcnRequest : public ros::Msg
  {
    public:

    GetThrusterConversionFcnRequest()
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

    const char * getType(){ return GETTHRUSTERCONVERSIONFCN; };
    const char * getMD5(){ return "d41d8cd98f00b204e9800998ecf8427e"; };

  };

  class GetThrusterConversionFcnResponse : public ros::Msg
  {
    public:
      typedef uuv_gazebo_ros_plugins_msgs::ThrusterConversionFcn _fcn_type;
      _fcn_type fcn;

    GetThrusterConversionFcnResponse():
      fcn()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->fcn.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->fcn.deserialize(inbuffer + offset);
     return offset;
    }

    const char * getType(){ return GETTHRUSTERCONVERSIONFCN; };
    const char * getMD5(){ return "b489744fdf1ea3660acd86f33ee041a7"; };

  };

  class GetThrusterConversionFcn {
    public:
    typedef GetThrusterConversionFcnRequest Request;
    typedef GetThrusterConversionFcnResponse Response;
  };

}
#endif
