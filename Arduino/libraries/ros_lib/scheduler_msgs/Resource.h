#ifndef _ROS_scheduler_msgs_Resource_h
#define _ROS_scheduler_msgs_Resource_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "uuid_msgs/UniqueID.h"
#include "rocon_std_msgs/Remapping.h"
#include "rocon_std_msgs/KeyValue.h"

namespace scheduler_msgs
{

  class Resource : public ros::Msg
  {
    public:
      typedef const char* _rapp_type;
      _rapp_type rapp;
      typedef uuid_msgs::UniqueID _id_type;
      _id_type id;
      typedef const char* _uri_type;
      _uri_type uri;
      uint32_t remappings_length;
      typedef rocon_std_msgs::Remapping _remappings_type;
      _remappings_type st_remappings;
      _remappings_type * remappings;
      uint32_t parameters_length;
      typedef rocon_std_msgs::KeyValue _parameters_type;
      _parameters_type st_parameters;
      _parameters_type * parameters;

    Resource():
      rapp(""),
      id(),
      uri(""),
      remappings_length(0), remappings(NULL),
      parameters_length(0), parameters(NULL)
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
      offset += this->id.serialize(outbuffer + offset);
      uint32_t length_uri = strlen(this->uri);
      varToArr(outbuffer + offset, length_uri);
      offset += 4;
      memcpy(outbuffer + offset, this->uri, length_uri);
      offset += length_uri;
      *(outbuffer + offset + 0) = (this->remappings_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->remappings_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->remappings_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->remappings_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->remappings_length);
      for( uint32_t i = 0; i < remappings_length; i++){
      offset += this->remappings[i].serialize(outbuffer + offset);
      }
      *(outbuffer + offset + 0) = (this->parameters_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->parameters_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->parameters_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->parameters_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->parameters_length);
      for( uint32_t i = 0; i < parameters_length; i++){
      offset += this->parameters[i].serialize(outbuffer + offset);
      }
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
      offset += this->id.deserialize(inbuffer + offset);
      uint32_t length_uri;
      arrToVar(length_uri, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_uri; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_uri-1]=0;
      this->uri = (char *)(inbuffer + offset-1);
      offset += length_uri;
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
      uint32_t parameters_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      parameters_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      parameters_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      parameters_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->parameters_length);
      if(parameters_lengthT > parameters_length)
        this->parameters = (rocon_std_msgs::KeyValue*)realloc(this->parameters, parameters_lengthT * sizeof(rocon_std_msgs::KeyValue));
      parameters_length = parameters_lengthT;
      for( uint32_t i = 0; i < parameters_length; i++){
      offset += this->st_parameters.deserialize(inbuffer + offset);
        memcpy( &(this->parameters[i]), &(this->st_parameters), sizeof(rocon_std_msgs::KeyValue));
      }
     return offset;
    }

    const char * getType(){ return "scheduler_msgs/Resource"; };
    const char * getMD5(){ return "754fd8dd757d06fa1564264b85a21995"; };

  };

}
#endif