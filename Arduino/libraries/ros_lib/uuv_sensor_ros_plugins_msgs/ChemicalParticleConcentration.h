#ifndef _ROS_uuv_sensor_ros_plugins_msgs_ChemicalParticleConcentration_h
#define _ROS_uuv_sensor_ros_plugins_msgs_ChemicalParticleConcentration_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"
#include "geometry_msgs/Vector3.h"

namespace uuv_sensor_ros_plugins_msgs
{

  class ChemicalParticleConcentration : public ros::Msg
  {
    public:
      typedef std_msgs::Header _header_type;
      _header_type header;
      typedef geometry_msgs::Vector3 _position_type;
      _position_type position;
      typedef float _latitude_type;
      _latitude_type latitude;
      typedef float _longitude_type;
      _longitude_type longitude;
      typedef float _depth_type;
      _depth_type depth;
      typedef float _concentration_type;
      _concentration_type concentration;
      typedef bool _is_measuring_type;
      _is_measuring_type is_measuring;

    ChemicalParticleConcentration():
      header(),
      position(),
      latitude(0),
      longitude(0),
      depth(0),
      concentration(0),
      is_measuring(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      offset += this->position.serialize(outbuffer + offset);
      offset += serializeAvrFloat64(outbuffer + offset, this->latitude);
      offset += serializeAvrFloat64(outbuffer + offset, this->longitude);
      offset += serializeAvrFloat64(outbuffer + offset, this->depth);
      offset += serializeAvrFloat64(outbuffer + offset, this->concentration);
      union {
        bool real;
        uint8_t base;
      } u_is_measuring;
      u_is_measuring.real = this->is_measuring;
      *(outbuffer + offset + 0) = (u_is_measuring.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->is_measuring);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      offset += this->position.deserialize(inbuffer + offset);
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->latitude));
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->longitude));
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->depth));
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->concentration));
      union {
        bool real;
        uint8_t base;
      } u_is_measuring;
      u_is_measuring.base = 0;
      u_is_measuring.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->is_measuring = u_is_measuring.real;
      offset += sizeof(this->is_measuring);
     return offset;
    }

    const char * getType(){ return "uuv_sensor_ros_plugins_msgs/ChemicalParticleConcentration"; };
    const char * getMD5(){ return "f17ac73d7dd3916a4fd6f721f0ccbe37"; };

  };

}
#endif