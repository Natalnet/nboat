#ifndef _ROS_SERVICE_AddWaypoint_h
#define _ROS_SERVICE_AddWaypoint_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "uuv_control_msgs/Waypoint.h"

namespace uuv_control_msgs
{

static const char ADDWAYPOINT[] = "uuv_control_msgs/AddWaypoint";

  class AddWaypointRequest : public ros::Msg
  {
    public:
      typedef uuv_control_msgs::Waypoint _waypoint_type;
      _waypoint_type waypoint;

    AddWaypointRequest():
      waypoint()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->waypoint.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->waypoint.deserialize(inbuffer + offset);
     return offset;
    }

    const char * getType(){ return ADDWAYPOINT; };
    const char * getMD5(){ return "3a004c7bf8d1b045f54b4f0d0d7256f0"; };

  };

  class AddWaypointResponse : public ros::Msg
  {
    public:
      typedef bool _success_type;
      _success_type success;
      uint32_t waypoints_length;
      typedef uuv_control_msgs::Waypoint _waypoints_type;
      _waypoints_type st_waypoints;
      _waypoints_type * waypoints;

    AddWaypointResponse():
      success(0),
      waypoints_length(0), waypoints(NULL)
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
      *(outbuffer + offset + 0) = (this->waypoints_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->waypoints_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->waypoints_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->waypoints_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->waypoints_length);
      for( uint32_t i = 0; i < waypoints_length; i++){
      offset += this->waypoints[i].serialize(outbuffer + offset);
      }
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
     return offset;
    }

    const char * getType(){ return ADDWAYPOINT; };
    const char * getMD5(){ return "48bd8f09705ced6872f0bda693e6f08c"; };

  };

  class AddWaypoint {
    public:
    typedef AddWaypointRequest Request;
    typedef AddWaypointResponse Response;
  };

}
#endif
