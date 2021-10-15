#ifndef _ROS_SERVICE_GetWaypoints_h
#define _ROS_SERVICE_GetWaypoints_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "uuv_control_msgs/Waypoint.h"

namespace uuv_control_msgs
{

static const char GETWAYPOINTS[] = "uuv_control_msgs/GetWaypoints";

  class GetWaypointsRequest : public ros::Msg
  {
    public:

    GetWaypointsRequest()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
     return offset;
    }

    const char * getType(){ return GETWAYPOINTS; };
    const char * getMD5(){ return "d41d8cd98f00b204e9800998ecf8427e"; };

  };

  class GetWaypointsResponse : public ros::Msg
  {
    public:
      uint32_t waypoints_length;
      typedef uuv_control_msgs::Waypoint _waypoints_type;
      _waypoints_type st_waypoints;
      _waypoints_type * waypoints;

    GetWaypointsResponse():
      waypoints_length(0), waypoints(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
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

    const char * getType(){ return GETWAYPOINTS; };
    const char * getMD5(){ return "7256248537b12c726720758df9a72413"; };

  };

  class GetWaypoints {
    public:
    typedef GetWaypointsRequest Request;
    typedef GetWaypointsResponse Response;
  };

}
#endif
