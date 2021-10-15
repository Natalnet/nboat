#ifndef _ROS_SERVICE_InitRectTrajectory_h
#define _ROS_SERVICE_InitRectTrajectory_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Time.h"
#include "geometry_msgs/Point.h"

namespace uuv_control_msgs
{

static const char INITRECTTRAJECTORY[] = "uuv_control_msgs/InitRectTrajectory";

  class InitRectTrajectoryRequest : public ros::Msg
  {
    public:
      typedef std_msgs::Time _start_time_type;
      _start_time_type start_time;
      typedef bool _start_now_type;
      _start_now_type start_now;
      typedef geometry_msgs::Point _origin_type;
      _origin_type origin;
      typedef float _height_type;
      _height_type height;
      typedef float _width_type;
      _width_type width;
      typedef float _angle_offset_type;
      _angle_offset_type angle_offset;
      typedef float _heading_offset_type;
      _heading_offset_type heading_offset;
      typedef float _max_forward_speed_type;
      _max_forward_speed_type max_forward_speed;

    InitRectTrajectoryRequest():
      start_time(),
      start_now(0),
      origin(),
      height(0),
      width(0),
      angle_offset(0),
      heading_offset(0),
      max_forward_speed(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->start_time.serialize(outbuffer + offset);
      union {
        bool real;
        uint8_t base;
      } u_start_now;
      u_start_now.real = this->start_now;
      *(outbuffer + offset + 0) = (u_start_now.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->start_now);
      offset += this->origin.serialize(outbuffer + offset);
      offset += serializeAvrFloat64(outbuffer + offset, this->height);
      offset += serializeAvrFloat64(outbuffer + offset, this->width);
      offset += serializeAvrFloat64(outbuffer + offset, this->angle_offset);
      offset += serializeAvrFloat64(outbuffer + offset, this->heading_offset);
      offset += serializeAvrFloat64(outbuffer + offset, this->max_forward_speed);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->start_time.deserialize(inbuffer + offset);
      union {
        bool real;
        uint8_t base;
      } u_start_now;
      u_start_now.base = 0;
      u_start_now.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->start_now = u_start_now.real;
      offset += sizeof(this->start_now);
      offset += this->origin.deserialize(inbuffer + offset);
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->height));
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->width));
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->angle_offset));
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->heading_offset));
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->max_forward_speed));
     return offset;
    }

    const char * getType(){ return INITRECTTRAJECTORY; };
    const char * getMD5(){ return "82860775b3df6259cef2af6522eca70e"; };

  };

  class InitRectTrajectoryResponse : public ros::Msg
  {
    public:
      typedef bool _success_type;
      _success_type success;

    InitRectTrajectoryResponse():
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

    const char * getType(){ return INITRECTTRAJECTORY; };
    const char * getMD5(){ return "358e233cde0c8a8bcfea4ce193f8fc15"; };

  };

  class InitRectTrajectory {
    public:
    typedef InitRectTrajectoryRequest Request;
    typedef InitRectTrajectoryResponse Response;
  };

}
#endif
