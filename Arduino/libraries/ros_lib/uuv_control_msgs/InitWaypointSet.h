#ifndef _ROS_SERVICE_InitWaypointSet_h
#define _ROS_SERVICE_InitWaypointSet_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "uuv_control_msgs/Waypoint.h"
#include "std_msgs/String.h"
#include "std_msgs/Time.h"

namespace uuv_control_msgs
{

static const char INITWAYPOINTSET[] = "uuv_control_msgs/InitWaypointSet";

  class InitWaypointSetRequest : public ros::Msg
  {
    public:
      typedef std_msgs::Time _start_time_type;
      _start_time_type start_time;
      typedef bool _start_now_type;
      _start_now_type start_now;
      uint32_t waypoints_length;
      typedef uuv_control_msgs::Waypoint _waypoints_type;
      _waypoints_type st_waypoints;
      _waypoints_type * waypoints;
      typedef float _max_forward_speed_type;
      _max_forward_speed_type max_forward_speed;
      typedef float _heading_offset_type;
      _heading_offset_type heading_offset;
      typedef std_msgs::String _interpolator_type;
      _interpolator_type interpolator;

    InitWaypointSetRequest():
      start_time(),
      start_now(0),
      waypoints_length(0), waypoints(NULL),
      max_forward_speed(0),
      heading_offset(0),
      interpolator()
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
      *(outbuffer + offset + 0) = (this->waypoints_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->waypoints_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->waypoints_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->waypoints_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->waypoints_length);
      for( uint32_t i = 0; i < waypoints_length; i++){
      offset += this->waypoints[i].serialize(outbuffer + offset);
      }
      offset += serializeAvrFloat64(outbuffer + offset, this->max_forward_speed);
      offset += serializeAvrFloat64(outbuffer + offset, this->heading_offset);
      offset += this->interpolator.serialize(outbuffer + offset);
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
      uint32_t waypoints_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      waypoints_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      waypoints_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      waypoints_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->waypoints_length);
      if(waypoints_lengthT > waypoints_length)
        this->waypoints = (uuv_control_msgs::Waypoint*)realloc(this->waypoints, waypoints_lengthT * sizeof(uuv_control_msgs::Waypoint));
      waypoints_length = waypoints_lengthT;
      for( uint32_t i = 0; i < waypoints_length; i++){
      offset += this->st_waypoints.deserialize(inbuffer + offset);
        memcpy( &(this->waypoints[i]), &(this->st_waypoints), sizeof(uuv_control_msgs::Waypoint));
      }
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->max_forward_speed));
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->heading_offset));
      offset += this->interpolator.deserialize(inbuffer + offset);
     return offset;
    }

    const char * getType(){ return INITWAYPOINTSET; };
    const char * getMD5(){ return "a1ff84a20694a6c851879f791bb28d61"; };

  };

  class InitWaypointSetResponse : public ros::Msg
  {
    public:
      typedef bool _success_type;
      _success_type success;

    InitWaypointSetResponse():
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

    const char * getType(){ return INITWAYPOINTSET; };
    const char * getMD5(){ return "358e233cde0c8a8bcfea4ce193f8fc15"; };

  };

  class InitWaypointSet {
    public:
    typedef InitWaypointSetRequest Request;
    typedef InitWaypointSetResponse Response;
  };

}
#endif
