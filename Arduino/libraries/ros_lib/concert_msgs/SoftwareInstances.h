#ifndef _ROS_concert_msgs_SoftwareInstances_h
#define _ROS_concert_msgs_SoftwareInstances_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "concert_msgs/SoftwareInstance.h"

namespace concert_msgs
{

  class SoftwareInstances : public ros::Msg
  {
    public:
      uint32_t instances_length;
      typedef concert_msgs::SoftwareInstance _instances_type;
      _instances_type st_instances;
      _instances_type * instances;

    SoftwareInstances():
      instances_length(0), instances(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->instances_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->instances_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->instances_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->instances_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->instances_length);
      for( uint32_t i = 0; i < instances_length; i++){
      offset += this->instances[i].serialize(outbuffer + offset);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t instances_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      instances_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      instances_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      instances_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->instances_length);
      if(instances_lengthT > instances_length)
        this->instances = (concert_msgs::SoftwareInstance*)realloc(this->instances, instances_lengthT * sizeof(concert_msgs::SoftwareInstance));
      instances_length = instances_lengthT;
      for( uint32_t i = 0; i < instances_length; i++){
      offset += this->st_instances.deserialize(inbuffer + offset);
        memcpy( &(this->instances[i]), &(this->st_instances), sizeof(concert_msgs::SoftwareInstance));
      }
     return offset;
    }

    const char * getType(){ return "concert_msgs/SoftwareInstances"; };
    const char * getMD5(){ return "3db13b2ea7c2b945782f742cf7b4ac03"; };

  };

}
#endif