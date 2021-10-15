#ifndef _ROS_SERVICE_GetOriginSphericalCoord_h
#define _ROS_SERVICE_GetOriginSphericalCoord_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace uuv_world_ros_plugins_msgs
{

static const char GETORIGINSPHERICALCOORD[] = "uuv_world_ros_plugins_msgs/GetOriginSphericalCoord";

  class GetOriginSphericalCoordRequest : public ros::Msg
  {
    public:

    GetOriginSphericalCoordRequest()
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

    const char * getType(){ return GETORIGINSPHERICALCOORD; };
    const char * getMD5(){ return "d41d8cd98f00b204e9800998ecf8427e"; };

  };

  class GetOriginSphericalCoordResponse : public ros::Msg
  {
    public:
      typedef float _latitude_deg_type;
      _latitude_deg_type latitude_deg;
      typedef float _longitude_deg_type;
      _longitude_deg_type longitude_deg;
      typedef float _altitude_type;
      _altitude_type altitude;

    GetOriginSphericalCoordResponse():
      latitude_deg(0),
      longitude_deg(0),
      altitude(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += serializeAvrFloat64(outbuffer + offset, this->latitude_deg);
      offset += serializeAvrFloat64(outbuffer + offset, this->longitude_deg);
      offset += serializeAvrFloat64(outbuffer + offset, this->altitude);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->latitude_deg));
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->longitude_deg));
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->altitude));
     return offset;
    }

    const char * getType(){ return GETORIGINSPHERICALCOORD; };
    const char * getMD5(){ return "60457d630fe21cc5f8f6bd5d0fc90156"; };

  };

  class GetOriginSphericalCoord {
    public:
    typedef GetOriginSphericalCoordRequest Request;
    typedef GetOriginSphericalCoordResponse Response;
  };

}
#endif
