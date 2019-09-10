#ifndef _ROS_concert_msgs_Services_h
#define _ROS_concert_msgs_Services_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "concert_msgs/ServiceProfile.h"

namespace concert_msgs
{

  class Services : public ros::Msg
  {
    public:
      uint32_t services_length;
      typedef concert_msgs::ServiceProfile _services_type;
      _services_type st_services;
      _services_type * services;

    Services():
      services_length(0), services(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->services_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->services_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->services_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->services_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->services_length);
      for( uint32_t i = 0; i < services_length; i++){
      offset += this->services[i].serialize(outbuffer + offset);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t services_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      services_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      services_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      services_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->services_length);
      if(services_lengthT > services_length)
        this->services = (concert_msgs::ServiceProfile*)realloc(this->services, services_lengthT * sizeof(concert_msgs::ServiceProfile));
      services_length = services_lengthT;
      for( uint32_t i = 0; i < services_length; i++){
      offset += this->st_services.deserialize(inbuffer + offset);
        memcpy( &(this->services[i]), &(this->st_services), sizeof(concert_msgs::ServiceProfile));
      }
     return offset;
    }

    const char * getType(){ return "concert_msgs/Services"; };
    const char * getMD5(){ return "385406088e57b4886d05051733612cb1"; };

  };

}
#endif