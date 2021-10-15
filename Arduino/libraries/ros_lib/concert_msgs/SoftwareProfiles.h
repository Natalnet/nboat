#ifndef _ROS_concert_msgs_SoftwareProfiles_h
#define _ROS_concert_msgs_SoftwareProfiles_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "concert_msgs/SoftwareProfile.h"

namespace concert_msgs
{

  class SoftwareProfiles : public ros::Msg
  {
    public:
      uint32_t profiles_length;
      typedef concert_msgs::SoftwareProfile _profiles_type;
      _profiles_type st_profiles;
      _profiles_type * profiles;

    SoftwareProfiles():
      profiles_length(0), profiles(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->profiles_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->profiles_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->profiles_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->profiles_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->profiles_length);
      for( uint32_t i = 0; i < profiles_length; i++){
      offset += this->profiles[i].serialize(outbuffer + offset);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t profiles_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      profiles_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      profiles_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      profiles_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->profiles_length);
      if(profiles_lengthT > profiles_length)
        this->profiles = (concert_msgs::SoftwareProfile*)realloc(this->profiles, profiles_lengthT * sizeof(concert_msgs::SoftwareProfile));
      profiles_length = profiles_lengthT;
      for( uint32_t i = 0; i < profiles_length; i++){
      offset += this->st_profiles.deserialize(inbuffer + offset);
        memcpy( &(this->profiles[i]), &(this->st_profiles), sizeof(concert_msgs::SoftwareProfile));
      }
     return offset;
    }

    const char * getType(){ return "concert_msgs/SoftwareProfiles"; };
    const char * getMD5(){ return "b1749b57e354bf30f98c3179a4fff5d7"; };

  };

}
#endif