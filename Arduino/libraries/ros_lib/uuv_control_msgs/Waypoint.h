#ifndef _ROS_uuv_control_msgs_Waypoint_h
#define _ROS_uuv_control_msgs_Waypoint_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"
#include "geometry_msgs/Point.h"

namespace uuv_control_msgs
{

  class Waypoint : public ros::Msg
  {
    public:
      typedef std_msgs::Header _header_type;
      _header_type header;
      typedef geometry_msgs::Point _point_type;
      _point_type point;
      typedef float _max_forward_speed_type;
      _max_forward_speed_type max_forward_speed;
      typedef float _heading_offset_type;
      _heading_offset_type heading_offset;
      typedef bool _use_fixed_heading_type;
      _use_fixed_heading_type use_fixed_heading;
      typedef float _radius_of_acceptance_type;
      _radius_of_acceptance_type radius_of_acceptance;

    Waypoint():
      header(),
      point(),
      max_forward_speed(0),
      heading_offset(0),
      use_fixed_heading(0),
      radius_of_acceptance(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      offset += this->point.serialize(outbuffer + offset);
      offset += serializeAvrFloat64(outbuffer + offset, this->max_forward_speed);
      offset += serializeAvrFloat64(outbuffer + offset, this->heading_offset);
      union {
        bool real;
        uint8_t base;
      } u_use_fixed_heading;
      u_use_fixed_heading.real = this->use_fixed_heading;
      *(outbuffer + offset + 0) = (u_use_fixed_heading.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->use_fixed_heading);
      offset += serializeAvrFloat64(outbuffer + offset, this->radius_of_acceptance);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      offset += this->point.deserialize(inbuffer + offset);
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->max_forward_speed));
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->heading_offset));
      union {
        bool real;
        uint8_t base;
      } u_use_fixed_heading;
      u_use_fixed_heading.base = 0;
      u_use_fixed_heading.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->use_fixed_heading = u_use_fixed_heading.real;
      offset += sizeof(this->use_fixed_heading);
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->radius_of_acceptance));
     return offset;
    }

    const char * getType(){ return "uuv_control_msgs/Waypoint"; };
    const char * getMD5(){ return "0efb7fda1b5980152de94b6064a5cf35"; };

  };

}
#endif