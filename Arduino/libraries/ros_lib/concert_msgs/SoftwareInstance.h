#ifndef _ROS_concert_msgs_SoftwareInstance_h
#define _ROS_concert_msgs_SoftwareInstance_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "rocon_std_msgs/KeyValue.h"

namespace concert_msgs
{

  class SoftwareInstance : public ros::Msg
  {
    public:
      typedef const char* _resource_name_type;
      _resource_name_type resource_name;
      typedef const char* _name_type;
      _name_type name;
      typedef int16_t _max_count_type;
      _max_count_type max_count;
      typedef const char* _namespace_type;
      _namespace_type namespace;
      uint32_t users_length;
      typedef char* _users_type;
      _users_type st_users;
      _users_type * users;
      uint32_t parameters_length;
      typedef rocon_std_msgs::KeyValue _parameters_type;
      _parameters_type st_parameters;
      _parameters_type * parameters;

    SoftwareInstance():
      resource_name(""),
      name(""),
      max_count(0),
      namespace(""),
      users_length(0), users(NULL),
      parameters_length(0), parameters(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      uint32_t length_resource_name = strlen(this->resource_name);
      varToArr(outbuffer + offset, length_resource_name);
      offset += 4;
      memcpy(outbuffer + offset, this->resource_name, length_resource_name);
      offset += length_resource_name;
      uint32_t length_name = strlen(this->name);
      varToArr(outbuffer + offset, length_name);
      offset += 4;
      memcpy(outbuffer + offset, this->name, length_name);
      offset += length_name;
      union {
        int16_t real;
        uint16_t base;
      } u_max_count;
      u_max_count.real = this->max_count;
      *(outbuffer + offset + 0) = (u_max_count.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_max_count.base >> (8 * 1)) & 0xFF;
      offset += sizeof(this->max_count);
      uint32_t length_namespace = strlen(this->namespace);
      varToArr(outbuffer + offset, length_namespace);
      offset += 4;
      memcpy(outbuffer + offset, this->namespace, length_namespace);
      offset += length_namespace;
      *(outbuffer + offset + 0) = (this->users_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->users_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->users_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->users_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->users_length);
      for( uint32_t i = 0; i < users_length; i++){
      uint32_t length_usersi = strlen(this->users[i]);
      varToArr(outbuffer + offset, length_usersi);
      offset += 4;
      memcpy(outbuffer + offset, this->users[i], length_usersi);
      offset += length_usersi;
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
      uint32_t length_resource_name;
      arrToVar(length_resource_name, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_resource_name; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_resource_name-1]=0;
      this->resource_name = (char *)(inbuffer + offset-1);
      offset += length_resource_name;
      uint32_t length_name;
      arrToVar(length_name, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_name; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_name-1]=0;
      this->name = (char *)(inbuffer + offset-1);
      offset += length_name;
      union {
        int16_t real;
        uint16_t base;
      } u_max_count;
      u_max_count.base = 0;
      u_max_count.base |= ((uint16_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_max_count.base |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->max_count = u_max_count.real;
      offset += sizeof(this->max_count);
      uint32_t length_namespace;
      arrToVar(length_namespace, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_namespace; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_namespace-1]=0;
      this->namespace = (char *)(inbuffer + offset-1);
      offset += length_namespace;
      uint32_t users_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      users_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      users_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      users_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->users_length);
      if(users_lengthT > users_length)
        this->users = (char**)realloc(this->users, users_lengthT * sizeof(char*));
      users_length = users_lengthT;
      for( uint32_t i = 0; i < users_length; i++){
      uint32_t length_st_users;
      arrToVar(length_st_users, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_st_users; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_st_users-1]=0;
      this->st_users = (char *)(inbuffer + offset-1);
      offset += length_st_users;
        memcpy( &(this->users[i]), &(this->st_users), sizeof(char*));
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

    const char * getType(){ return "concert_msgs/SoftwareInstance"; };
    const char * getMD5(){ return "d51f42200dcf594007d5fbba6c47cfe9"; };

  };

}
#endif