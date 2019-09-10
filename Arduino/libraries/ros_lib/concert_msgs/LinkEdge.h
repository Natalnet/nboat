#ifndef _ROS_concert_msgs_LinkEdge_h
#define _ROS_concert_msgs_LinkEdge_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace concert_msgs
{

  class LinkEdge : public ros::Msg
  {
    public:
      typedef const char* _start_type;
      _start_type start;
      typedef const char* _finish_type;
      _finish_type finish;
      typedef const char* _remap_from_type;
      _remap_from_type remap_from;
      typedef const char* _remap_to_type;
      _remap_to_type remap_to;

    LinkEdge():
      start(""),
      finish(""),
      remap_from(""),
      remap_to("")
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      uint32_t length_start = strlen(this->start);
      varToArr(outbuffer + offset, length_start);
      offset += 4;
      memcpy(outbuffer + offset, this->start, length_start);
      offset += length_start;
      uint32_t length_finish = strlen(this->finish);
      varToArr(outbuffer + offset, length_finish);
      offset += 4;
      memcpy(outbuffer + offset, this->finish, length_finish);
      offset += length_finish;
      uint32_t length_remap_from = strlen(this->remap_from);
      varToArr(outbuffer + offset, length_remap_from);
      offset += 4;
      memcpy(outbuffer + offset, this->remap_from, length_remap_from);
      offset += length_remap_from;
      uint32_t length_remap_to = strlen(this->remap_to);
      varToArr(outbuffer + offset, length_remap_to);
      offset += 4;
      memcpy(outbuffer + offset, this->remap_to, length_remap_to);
      offset += length_remap_to;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t length_start;
      arrToVar(length_start, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_start; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_start-1]=0;
      this->start = (char *)(inbuffer + offset-1);
      offset += length_start;
      uint32_t length_finish;
      arrToVar(length_finish, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_finish; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_finish-1]=0;
      this->finish = (char *)(inbuffer + offset-1);
      offset += length_finish;
      uint32_t length_remap_from;
      arrToVar(length_remap_from, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_remap_from; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_remap_from-1]=0;
      this->remap_from = (char *)(inbuffer + offset-1);
      offset += length_remap_from;
      uint32_t length_remap_to;
      arrToVar(length_remap_to, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_remap_to; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_remap_to-1]=0;
      this->remap_to = (char *)(inbuffer + offset-1);
      offset += length_remap_to;
     return offset;
    }

    const char * getType(){ return "concert_msgs/LinkEdge"; };
    const char * getMD5(){ return "01f86ee3e51dd78d2e2153a94d6f3865"; };

  };

}
#endif