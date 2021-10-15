#ifndef _ROS_scheduler_msgs_KnownResources_h
#define _ROS_scheduler_msgs_KnownResources_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"
#include "scheduler_msgs/CurrentStatus.h"

namespace scheduler_msgs
{

  class KnownResources : public ros::Msg
  {
    public:
      typedef std_msgs::Header _header_type;
      _header_type header;
      uint32_t resources_length;
      typedef scheduler_msgs::CurrentStatus _resources_type;
      _resources_type st_resources;
      _resources_type * resources;

    KnownResources():
      header(),
      resources_length(0), resources(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      *(outbuffer + offset + 0) = (this->resources_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->resources_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->resources_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->resources_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->resources_length);
      for( uint32_t i = 0; i < resources_length; i++){
      offset += this->resources[i].serialize(outbuffer + offset);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      uint32_t resources_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      resources_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      resources_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      resources_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->resources_length);
      if(resources_lengthT > resources_length)
        this->resources = (scheduler_msgs::CurrentStatus*)realloc(this->resources, resources_lengthT * sizeof(scheduler_msgs::CurrentStatus));
      resources_length = resources_lengthT;
      for( uint32_t i = 0; i < resources_length; i++){
      offset += this->st_resources.deserialize(inbuffer + offset);
        memcpy( &(this->resources[i]), &(this->st_resources), sizeof(scheduler_msgs::CurrentStatus));
      }
     return offset;
    }

    const char * getType(){ return "scheduler_msgs/KnownResources"; };
    const char * getMD5(){ return "d3e12e9eddf5fe98089b8d550ce49151"; };

  };

}
#endif