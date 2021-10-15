#ifndef _ROS_concert_msgs_ConductorGraph_h
#define _ROS_concert_msgs_ConductorGraph_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "concert_msgs/ConcertClient.h"

namespace concert_msgs
{

  class ConductorGraph : public ros::Msg
  {
    public:
      uint32_t pending_length;
      typedef concert_msgs::ConcertClient _pending_type;
      _pending_type st_pending;
      _pending_type * pending;
      uint32_t available_length;
      typedef concert_msgs::ConcertClient _available_type;
      _available_type st_available;
      _available_type * available;
      uint32_t missing_length;
      typedef concert_msgs::ConcertClient _missing_type;
      _missing_type st_missing;
      _missing_type * missing;
      uint32_t gone_length;
      typedef concert_msgs::ConcertClient _gone_type;
      _gone_type st_gone;
      _gone_type * gone;

    ConductorGraph():
      pending_length(0), pending(NULL),
      available_length(0), available(NULL),
      missing_length(0), missing(NULL),
      gone_length(0), gone(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->pending_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->pending_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->pending_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->pending_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->pending_length);
      for( uint32_t i = 0; i < pending_length; i++){
      offset += this->pending[i].serialize(outbuffer + offset);
      }
      *(outbuffer + offset + 0) = (this->available_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->available_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->available_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->available_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->available_length);
      for( uint32_t i = 0; i < available_length; i++){
      offset += this->available[i].serialize(outbuffer + offset);
      }
      *(outbuffer + offset + 0) = (this->missing_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->missing_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->missing_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->missing_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->missing_length);
      for( uint32_t i = 0; i < missing_length; i++){
      offset += this->missing[i].serialize(outbuffer + offset);
      }
      *(outbuffer + offset + 0) = (this->gone_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->gone_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->gone_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->gone_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->gone_length);
      for( uint32_t i = 0; i < gone_length; i++){
      offset += this->gone[i].serialize(outbuffer + offset);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t pending_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      pending_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      pending_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      pending_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->pending_length);
      if(pending_lengthT > pending_length)
        this->pending = (concert_msgs::ConcertClient*)realloc(this->pending, pending_lengthT * sizeof(concert_msgs::ConcertClient));
      pending_length = pending_lengthT;
      for( uint32_t i = 0; i < pending_length; i++){
      offset += this->st_pending.deserialize(inbuffer + offset);
        memcpy( &(this->pending[i]), &(this->st_pending), sizeof(concert_msgs::ConcertClient));
      }
      uint32_t available_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      available_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      available_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      available_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->available_length);
      if(available_lengthT > available_length)
        this->available = (concert_msgs::ConcertClient*)realloc(this->available, available_lengthT * sizeof(concert_msgs::ConcertClient));
      available_length = available_lengthT;
      for( uint32_t i = 0; i < available_length; i++){
      offset += this->st_available.deserialize(inbuffer + offset);
        memcpy( &(this->available[i]), &(this->st_available), sizeof(concert_msgs::ConcertClient));
      }
      uint32_t missing_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      missing_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      missing_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      missing_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->missing_length);
      if(missing_lengthT > missing_length)
        this->missing = (concert_msgs::ConcertClient*)realloc(this->missing, missing_lengthT * sizeof(concert_msgs::ConcertClient));
      missing_length = missing_lengthT;
      for( uint32_t i = 0; i < missing_length; i++){
      offset += this->st_missing.deserialize(inbuffer + offset);
        memcpy( &(this->missing[i]), &(this->st_missing), sizeof(concert_msgs::ConcertClient));
      }
      uint32_t gone_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      gone_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      gone_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      gone_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->gone_length);
      if(gone_lengthT > gone_length)
        this->gone = (concert_msgs::ConcertClient*)realloc(this->gone, gone_lengthT * sizeof(concert_msgs::ConcertClient));
      gone_length = gone_lengthT;
      for( uint32_t i = 0; i < gone_length; i++){
      offset += this->st_gone.deserialize(inbuffer + offset);
        memcpy( &(this->gone[i]), &(this->st_gone), sizeof(concert_msgs::ConcertClient));
      }
     return offset;
    }

    const char * getType(){ return "concert_msgs/ConductorGraph"; };
    const char * getMD5(){ return "79f1f3ca0d6e8e424874455f4beb1056"; };

  };

}
#endif