#ifndef _ROS_SERVICE_TransformFromSphericalCoord_h
#define _ROS_SERVICE_TransformFromSphericalCoord_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "geometry_msgs/Vector3.h"

namespace uuv_world_ros_plugins_msgs
{

static const char TRANSFORMFROMSPHERICALCOORD[] = "uuv_world_ros_plugins_msgs/TransformFromSphericalCoord";

  class TransformFromSphericalCoordRequest : public ros::Msg
  {
    public:
      typedef float _latitude_deg_type;
      _latitude_deg_type latitude_deg;
      typedef float _longitude_deg_type;
      _longitude_deg_type longitude_deg;
      typedef float _altitude_type;
      _altitude_type altitude;

    TransformFromSphericalCoordRequest():
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

    const char * getType(){ return TRANSFORMFROMSPHERICALCOORD; };
    const char * getMD5(){ return "60457d630fe21cc5f8f6bd5d0fc90156"; };

  };

  class TransformFromSphericalCoordResponse : public ros::Msg
  {
    public:
      typedef geometry_msgs::Vector3 _output_type;
      _output_type output;

    TransformFromSphericalCoordResponse():
      output()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->output.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->output.deserialize(inbuffer + offset);
     return offset;
    }

    const char * getType(){ return TRANSFORMFROMSPHERICALCOORD; };
    const char * getMD5(){ return "d095d4a4697448df53fb4209e5def16e"; };

  };

  class TransformFromSphericalCoord {
    public:
    typedef TransformFromSphericalCoordRequest Request;
    typedef TransformFromSphericalCoordResponse Response;
  };

}
#endif
