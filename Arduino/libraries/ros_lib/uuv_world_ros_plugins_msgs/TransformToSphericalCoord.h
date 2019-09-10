#ifndef _ROS_SERVICE_TransformToSphericalCoord_h
#define _ROS_SERVICE_TransformToSphericalCoord_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "geometry_msgs/Vector3.h"

namespace uuv_world_ros_plugins_msgs
{

static const char TRANSFORMTOSPHERICALCOORD[] = "uuv_world_ros_plugins_msgs/TransformToSphericalCoord";

  class TransformToSphericalCoordRequest : public ros::Msg
  {
    public:
      typedef geometry_msgs::Vector3 _input_type;
      _input_type input;

    TransformToSphericalCoordRequest():
      input()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->input.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->input.deserialize(inbuffer + offset);
     return offset;
    }

    const char * getType(){ return TRANSFORMTOSPHERICALCOORD; };
    const char * getMD5(){ return "62dfe86eef80ef12ae4c9c8bf6763cb7"; };

  };

  class TransformToSphericalCoordResponse : public ros::Msg
  {
    public:
      typedef float _latitude_deg_type;
      _latitude_deg_type latitude_deg;
      typedef float _longitude_deg_type;
      _longitude_deg_type longitude_deg;
      typedef float _altitude_type;
      _altitude_type altitude;

    TransformToSphericalCoordResponse():
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

    const char * getType(){ return TRANSFORMTOSPHERICALCOORD; };
    const char * getMD5(){ return "60457d630fe21cc5f8f6bd5d0fc90156"; };

  };

  class TransformToSphericalCoord {
    public:
    typedef TransformToSphericalCoordRequest Request;
    typedef TransformToSphericalCoordResponse Response;
  };

}
#endif
