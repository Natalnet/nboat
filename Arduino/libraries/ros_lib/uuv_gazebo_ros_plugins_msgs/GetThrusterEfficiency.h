#ifndef _ROS_SERVICE_GetThrusterEfficiency_h
#define _ROS_SERVICE_GetThrusterEfficiency_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace uuv_gazebo_ros_plugins_msgs
{

static const char GETTHRUSTEREFFICIENCY[] = "uuv_gazebo_ros_plugins_msgs/GetThrusterEfficiency";

  class GetThrusterEfficiencyRequest : public ros::Msg
  {
    public:

    GetThrusterEfficiencyRequest()
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

    const char * getType(){ return GETTHRUSTEREFFICIENCY; };
    const char * getMD5(){ return "d41d8cd98f00b204e9800998ecf8427e"; };

  };

  class GetThrusterEfficiencyResponse : public ros::Msg
  {
    public:
      typedef float _efficiency_type;
      _efficiency_type efficiency;

    GetThrusterEfficiencyResponse():
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

    const char * getType(){ return GETTHRUSTEREFFICIENCY; };
    const char * getMD5(){ return "b80ec71e671b93e4cc403df1ac4c8a86"; };

  };

  class GetThrusterEfficiency {
    public:
    typedef GetThrusterEfficiencyRequest Request;
    typedef GetThrusterEfficiencyResponse Response;
  };

}
#endif
