#ifndef _ROS_concert_msgs_LinkNode_h
#define _ROS_concert_msgs_LinkNode_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "rocon_std_msgs/KeyValue.h"

namespace concert_msgs
{

  class LinkNode : public ros::Msg
  {
    public:
      typedef const char* _id_type;
      _id_type id;
      typedef const char* _resource_type;
      _resource_type resource;
      typedef int8_t _min_type;
      _min_type min;
      typedef int8_t _max_type;
      _max_type max;
      typedef bool _force_name_matching_type;
      _force_name_matching_type force_name_matching;
      typedef rocon_std_msgs::KeyValue _parameters_type;
      _parameters_type parameters;
      enum { UNLIMITED_RESOURCE = -1 };

    LinkNode():
      id(""),
      resource(""),
      min(0),
      max(0),
      force_name_matching(0),
      parameters()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      uint32_t length_id = strlen(this->id);
      varToArr(outbuffer + offset, length_id);
      offset += 4;
      memcpy(outbuffer + offset, this->id, length_id);
      offset += length_id;
      uint32_t length_resource = strlen(this->resource);
      varToArr(outbuffer + offset, length_resource);
      offset += 4;
      memcpy(outbuffer + offset, this->resource, length_resource);
      offset += length_resource;
      union {
        int8_t real;
        uint8_t base;
      } u_min;
      u_min.real = this->min;
      *(outbuffer + offset + 0) = (u_min.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->min);
      union {
        int8_t real;
        uint8_t base;
      } u_max;
      u_max.real = this->max;
      *(outbuffer + offset + 0) = (u_max.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->max);
      union {
        bool real;
        uint8_t base;
      } u_force_name_matching;
      u_force_name_matching.real = this->force_name_matching;
      *(outbuffer + offset + 0) = (u_force_name_matching.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->force_name_matching);
      offset += this->parameters.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t length_id;
      arrToVar(length_id, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_id; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_id-1]=0;
      this->id = (char *)(inbuffer + offset-1);
      offset += length_id;
      uint32_t length_resource;
      arrToVar(length_resource, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_resource; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_resource-1]=0;
      this->resource = (char *)(inbuffer + offset-1);
      offset += length_resource;
      union {
        int8_t real;
        uint8_t base;
      } u_min;
      u_min.base = 0;
      u_min.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->min = u_min.real;
      offset += sizeof(this->min);
      union {
        int8_t real;
        uint8_t base;
      } u_max;
      u_max.base = 0;
      u_max.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->max = u_max.real;
      offset += sizeof(this->max);
      union {
        bool real;
        uint8_t base;
      } u_force_name_matching;
      u_force_name_matching.base = 0;
      u_force_name_matching.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->force_name_matching = u_force_name_matching.real;
      offset += sizeof(this->force_name_matching);
      offset += this->parameters.deserialize(inbuffer + offset);
     return offset;
    }

    const char * getType(){ return "concert_msgs/LinkNode"; };
    const char * getMD5(){ return "66d27e37c29408b86c119285c34c50cd"; };

  };

}
#endif