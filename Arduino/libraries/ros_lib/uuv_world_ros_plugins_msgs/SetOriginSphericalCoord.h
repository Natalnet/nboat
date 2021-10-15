#ifndef _ROS_SERVICE_SetOriginSphericalCoord_h
#define _ROS_SERVICE_SetOriginSphericalCoord_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace uuv_world_ros_plugins_msgs
{

static const char SETORIGINSPHERICALCOORD[] = "uuv_world_ros_plugins_msgs/SetOriginSphericalCoord";

  class SetOriginSphericalCoordRequest : public ros::Msg
  {
    public:
      typedef float _latitude_deg_type;
      _latitude_deg_type latitude_deg;
      typedef float _longitude_deg_type;
      _longitude_deg_type longitude_deg;
      typedef float _altitude_type;
      _altitude_type altitude;

    SetOriginSphericalCoordRequest():
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

    const char * getType(){ return SETORIGINSPHERICALCOORD; };
    const char * getMD5(){ return "60457d630fe21cc5f8f6bd5d0fc90156"; };

  };

  class SetOriginSphericalCoordResponse : public ros::Msg
  {
    public:
      typedef bool _success_type;
      _success_type success;

    SetOriginSphericalCoordResponse():
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

    const char * getType(){ return SETORIGINSPHERICALCOORD; };
    const char * getMD5(){ return "358e233cde0c8a8bcfea4ce193f8fc15"; };

  };

  class SetOriginSphericalCoord {
    public:
    typedef SetOriginSphericalCoordRequest Request;
    typedef SetOriginSphericalCoordResponse Response;
  };

}
#endif
