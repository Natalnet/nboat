#ifndef _ROS_uuv_control_msgs_WaypointSet_h
#define _ROS_uuv_control_msgs_WaypointSet_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"
#include "std_msgs/Time.h"
#include "uuv_control_msgs/Waypoint.h"

namespace uuv_control_msgs
{

  class WaypointSet : public ros::Msg
  {
    public:
      typedef std_msgs::Header _header_type;
      _header_type header;
      typedef std_msgs::Time _start_time_type;
      _start_time_type start_time;
      uint32_t waypoints_length;
      typedef uuv_control_msgs::Waypoint _waypoints_type;
      _waypoints_type st_waypoints;
      _waypoints_type * waypoints;

    WaypointSet():
      header(),
      start_time(),
      waypoints_length(0), waypoints(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      offset += this->start_time.serialize(outbuffer + offset);
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
      offset += this->header.deserialize(inbuffer + offset);
      offset += this->start_time.deserialize(inbuffer + offset);
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

    const char * getType(){ return "uuv_control_msgs/WaypointSet"; };
    const char * getMD5(){ return "a946aaa8d17e35fe5a52e4f7ac482b5d"; };

  };

}
#endif