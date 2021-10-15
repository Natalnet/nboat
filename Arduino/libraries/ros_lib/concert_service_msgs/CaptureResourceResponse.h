#ifndef _ROS_concert_service_msgs_CaptureResourceResponse_h
#define _ROS_concert_service_msgs_CaptureResourceResponse_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "rocon_std_msgs/Remapping.h"

namespace concert_service_msgs
{

  class CaptureResourceResponse : public ros::Msg
  {
    public:
      typedef bool _result_type;
      _result_type result;
      uint32_t remappings_length;
      typedef rocon_std_msgs::Remapping _remappings_type;
      _remappings_type st_remappings;
      _remappings_type * remappings;

    CaptureResourceResponse():
      result(0),
      remappings_length(0), remappings(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_result;
      u_result.real = this->result;
      *(outbuffer + offset + 0) = (u_result.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->result);
      *(outbuffer + offset + 0) = (this->remappings_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->remappings_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->remappings_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->remappings_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->remappings_length);
      for( uint32_t i = 0; i < remappings_length; i++){
      offset += this->remappings[i].serialize(outbuffer + offset);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_result;
      u_result.base = 0;
      u_result.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->result = u_result.real;
      offset += sizeof(this->result);
      uint32_t remappings_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      remappings_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      remappings_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      remappings_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->remappings_length);
      if(remappings_lengthT > remappings_length)
        this->remappings = (rocon_std_msgs::Remapping*)realloc(this->remappings, remappings_lengthT * sizeof(rocon_std_msgs::Remapping));
      remappings_length = remappings_lengthT;
      for( uint32_t i = 0; i < remappings_length; i++){
      offset += this->st_remappings.deserialize(inbuffer + offset);
        memcpy( &(this->remappings[i]), &(this->st_remappings), sizeof(rocon_std_msgs::Remapping));
      }
     return offset;
    }

    const char * getType(){ return "concert_service_msgs/CaptureResourceResponse"; };
    const char * getMD5(){ return "f42045c0fb1faf0f4b9b3be576a75c21"; };

  };

}
#endif