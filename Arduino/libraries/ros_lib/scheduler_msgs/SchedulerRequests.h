#ifndef _ROS_scheduler_msgs_SchedulerRequests_h
#define _ROS_scheduler_msgs_SchedulerRequests_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"
#include "uuid_msgs/UniqueID.h"
#include "scheduler_msgs/Request.h"

namespace scheduler_msgs
{

  class SchedulerRequests : public ros::Msg
  {
    public:
      typedef std_msgs::Header _header_type;
      _header_type header;
      typedef uuid_msgs::UniqueID _requester_type;
      _requester_type requester;
      uint32_t requests_length;
      typedef scheduler_msgs::Request _requests_type;
      _requests_type st_requests;
      _requests_type * requests;

    SchedulerRequests():
      header(),
      requester(),
      requests_length(0), requests(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      offset += this->requester.serialize(outbuffer + offset);
      *(outbuffer + offset + 0) = (this->requests_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->requests_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->requests_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->requests_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->requests_length);
      for( uint32_t i = 0; i < requests_length; i++){
      offset += this->requests[i].serialize(outbuffer + offset);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      offset += this->requester.deserialize(inbuffer + offset);
      uint32_t requests_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      requests_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      requests_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      requests_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->requests_length);
      if(requests_lengthT > requests_length)
        this->requests = (scheduler_msgs::Request*)realloc(this->requests, requests_lengthT * sizeof(scheduler_msgs::Request));
      requests_length = requests_lengthT;
      for( uint32_t i = 0; i < requests_length; i++){
      offset += this->st_requests.deserialize(inbuffer + offset);
        memcpy( &(this->requests[i]), &(this->st_requests), sizeof(scheduler_msgs::Request));
      }
     return offset;
    }

    const char * getType(){ return "scheduler_msgs/SchedulerRequests"; };
    const char * getMD5(){ return "d0adc2f83296939c4b208a3e0619e86f"; };

  };

}
#endif