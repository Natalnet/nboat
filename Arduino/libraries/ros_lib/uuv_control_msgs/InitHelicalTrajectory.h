#ifndef _ROS_SERVICE_InitHelicalTrajectory_h
#define _ROS_SERVICE_InitHelicalTrajectory_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Time.h"
#include "geometry_msgs/Point.h"

namespace uuv_control_msgs
{

static const char INITHELICALTRAJECTORY[] = "uuv_control_msgs/InitHelicalTrajectory";

  class InitHelicalTrajectoryRequest : public ros::Msg
  {
    public:
      typedef std_msgs::Time _start_time_type;
      _start_time_type start_time;
      typedef bool _start_now_type;
      _start_now_type start_now;
      typedef float _radius_type;
      _radius_type radius;
      typedef geometry_msgs::Point _center_type;
      _center_type center;
      typedef bool _is_clockwise_type;
      _is_clockwise_type is_clockwise;
      typedef float _angle_offset_type;
      _angle_offset_type angle_offset;
      typedef int32_t _n_points_type;
      _n_points_type n_points;
      typedef float _heading_offset_type;
      _heading_offset_type heading_offset;
      typedef float _max_forward_speed_type;
      _max_forward_speed_type max_forward_speed;
      typedef float _duration_type;
      _duration_type duration;
      typedef float _n_turns_type;
      _n_turns_type n_turns;
      typedef float _delta_z_type;
      _delta_z_type delta_z;

    InitHelicalTrajectoryRequest():
      start_time(),
      start_now(0),
      radius(0),
      center(),
      is_clockwise(0),
      angle_offset(0),
      n_points(0),
      heading_offset(0),
      max_forward_speed(0),
      duration(0),
      n_turns(0),
      delta_z(0)
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
      offset += serializeAvrFloat64(outbuffer + offset, this->radius);
      offset += this->center.serialize(outbuffer + offset);
      union {
        bool real;
        uint8_t base;
      } u_is_clockwise;
      u_is_clockwise.real = this->is_clockwise;
      *(outbuffer + offset + 0) = (u_is_clockwise.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->is_clockwise);
      offset += serializeAvrFloat64(outbuffer + offset, this->angle_offset);
      union {
        int32_t real;
        uint32_t base;
      } u_n_points;
      u_n_points.real = this->n_points;
      *(outbuffer + offset + 0) = (u_n_points.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_n_points.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_n_points.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_n_points.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->n_points);
      offset += serializeAvrFloat64(outbuffer + offset, this->heading_offset);
      offset += serializeAvrFloat64(outbuffer + offset, this->max_forward_speed);
      offset += serializeAvrFloat64(outbuffer + offset, this->duration);
      offset += serializeAvrFloat64(outbuffer + offset, this->n_turns);
      offset += serializeAvrFloat64(outbuffer + offset, this->delta_z);
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
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->radius));
      offset += this->center.deserialize(inbuffer + offset);
      union {
        bool real;
        uint8_t base;
      } u_is_clockwise;
      u_is_clockwise.base = 0;
      u_is_clockwise.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->is_clockwise = u_is_clockwise.real;
      offset += sizeof(this->is_clockwise);
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->angle_offset));
      union {
        int32_t real;
        uint32_t base;
      } u_n_points;
      u_n_points.base = 0;
      u_n_points.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_n_points.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_n_points.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_n_points.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->n_points = u_n_points.real;
      offset += sizeof(this->n_points);
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->heading_offset));
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->max_forward_speed));
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->duration));
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->n_turns));
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->delta_z));
     return offset;
    }

    const char * getType(){ return INITHELICALTRAJECTORY; };
    const char * getMD5(){ return "cdffc21ee67e10141d55f07c2ab01ebc"; };

  };

  class InitHelicalTrajectoryResponse : public ros::Msg
  {
    public:
      typedef bool _success_type;
      _success_type success;

    InitHelicalTrajectoryResponse():
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

    const char * getType(){ return INITHELICALTRAJECTORY; };
    const char * getMD5(){ return "358e233cde0c8a8bcfea4ce193f8fc15"; };

  };

  class InitHelicalTrajectory {
    public:
    typedef InitHelicalTrajectoryRequest Request;
    typedef InitHelicalTrajectoryResponse Response;
  };

}
#endif
