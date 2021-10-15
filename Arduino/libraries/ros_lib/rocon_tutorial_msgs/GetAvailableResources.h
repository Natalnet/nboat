#ifndef _ROS_SERVICE_GetAvailableResources_h
#define _ROS_SERVICE_GetAvailableResources_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace rocon_tutorial_msgs
{

static const char GETAVAILABLERESOURCES[] = "rocon_tutorial_msgs/GetAvailableResources";

  class GetAvailableResourcesRequest : public ros::Msg
  {
    public:
      typedef const char* _rapp_type;
      _rapp_type rapp;
      typedef int16_t _priority_type;
      _priority_type priority;

    GetAvailableResourcesRequest():
      rapp(""),
      priority(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      uint32_t length_rapp = strlen(this->rapp);
      varToArr(outbuffer + offset, length_rapp);
      offset += 4;
      memcpy(outbuffer + offset, this->rapp, length_rapp);
      offset += length_rapp;
      union {
        int16_t real;
        uint16_t base;
      } u_priority;
      u_priority.real = this->priority;
      *(outbuffer + offset + 0) = (u_priority.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_priority.base >> (8 * 1)) & 0xFF;
      offset += sizeof(this->priority);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t length_rapp;
      arrToVar(length_rapp, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_rapp; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_rapp-1]=0;
      this->rapp = (char *)(inbuffer + offset-1);
      offset += length_rapp;
      union {
        int16_t real;
        uint16_t base;
      } u_priority;
      u_priority.base = 0;
      u_priority.base |= ((uint16_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_priority.base |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->priority = u_priority.real;
      offset += sizeof(this->priority);
     return offset;
    }

    const char * getType(){ return GETAVAILABLERESOURCES; };
    const char * getMD5(){ return "d6acea3bcb7fdb592ecb7ffc748c29b2"; };

  };

  class GetAvailableResourcesResponse : public ros::Msg
  {
    public:
      uint32_t available_resources_length;
      typedef char* _available_resources_type;
      _available_resources_type st_available_resources;
      _available_resources_type * available_resources;
      uint32_t preemptible_resources_length;
      typedef char* _preemptible_resources_type;
      _preemptible_resources_type st_preemptible_resources;
      _preemptible_resources_type * preemptible_resources;

    GetAvailableResourcesResponse():
      available_resources_length(0), available_resources(NULL),
      preemptible_resources_length(0), preemptible_resources(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->available_resources_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->available_resources_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->available_resources_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->available_resources_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->available_resources_length);
      for( uint32_t i = 0; i < available_resources_length; i++){
      uint32_t length_available_resourcesi = strlen(this->available_resources[i]);
      varToArr(outbuffer + offset, length_available_resourcesi);
      offset += 4;
      memcpy(outbuffer + offset, this->available_resources[i], length_available_resourcesi);
      offset += length_available_resourcesi;
      }
      *(outbuffer + offset + 0) = (this->preemptible_resources_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->preemptible_resources_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->preemptible_resources_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->preemptible_resources_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->preemptible_resources_length);
      for( uint32_t i = 0; i < preemptible_resources_length; i++){
      uint32_t length_preemptible_resourcesi = strlen(this->preemptible_resources[i]);
      varToArr(outbuffer + offset, length_preemptible_resourcesi);
      offset += 4;
      memcpy(outbuffer + offset, this->preemptible_resources[i], length_preemptible_resourcesi);
      offset += length_preemptible_resourcesi;
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t available_resources_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      available_resources_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      available_resources_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      available_resources_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->available_resources_length);
      if(available_resources_lengthT > available_resources_length)
        this->available_resources = (char**)realloc(this->available_resources, available_resources_lengthT * sizeof(char*));
      available_resources_length = available_resources_lengthT;
      for( uint32_t i = 0; i < available_resources_length; i++){
      uint32_t length_st_available_resources;
      arrToVar(length_st_available_resources, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_st_available_resources; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_st_available_resources-1]=0;
      this->st_available_resources = (char *)(inbuffer + offset-1);
      offset += length_st_available_resources;
        memcpy( &(this->available_resources[i]), &(this->st_available_resources), sizeof(char*));
      }
      uint32_t preemptible_resources_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      preemptible_resources_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      preemptible_resources_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      preemptible_resources_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->preemptible_resources_length);
      if(preemptible_resources_lengthT > preemptible_resources_length)
        this->preemptible_resources = (char**)realloc(this->preemptible_resources, preemptible_resources_lengthT * sizeof(char*));
      preemptible_resources_length = preemptible_resources_lengthT;
      for( uint32_t i = 0; i < preemptible_resources_length; i++){
      uint32_t length_st_preemptible_resources;
      arrToVar(length_st_preemptible_resources, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_st_preemptible_resources; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_st_preemptible_resources-1]=0;
      this->st_preemptible_resources = (char *)(inbuffer + offset-1);
      offset += length_st_preemptible_resources;
        memcpy( &(this->preemptible_resources[i]), &(this->st_preemptible_resources), sizeof(char*));
      }
     return offset;
    }

    const char * getType(){ return GETAVAILABLERESOURCES; };
    const char * getMD5(){ return "4211656ed7da3f4d2a05064e9d6a2241"; };

  };

  class GetAvailableResources {
    public:
    typedef GetAvailableResourcesRequest Request;
    typedef GetAvailableResourcesResponse Response;
  };

}
#endif
