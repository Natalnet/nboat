#ifndef _ROS_SERVICE_GetThrusterManagerConfig_h
#define _ROS_SERVICE_GetThrusterManagerConfig_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace uuv_thruster_manager
{

static const char GETTHRUSTERMANAGERCONFIG[] = "uuv_thruster_manager/GetThrusterManagerConfig";

  class GetThrusterManagerConfigRequest : public ros::Msg
  {
    public:

    GetThrusterManagerConfigRequest()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
     return offset;
    }

    const char * getType(){ return GETTHRUSTERMANAGERCONFIG; };
    const char * getMD5(){ return "d41d8cd98f00b204e9800998ecf8427e"; };

  };

  class GetThrusterManagerConfigResponse : public ros::Msg
  {
    public:
      typedef const char* _tf_prefix_type;
      _tf_prefix_type tf_prefix;
      typedef const char* _base_link_type;
      _base_link_type base_link;
      typedef const char* _thruster_frame_base_type;
      _thruster_frame_base_type thruster_frame_base;
      typedef const char* _thruster_topic_prefix_type;
      _thruster_topic_prefix_type thruster_topic_prefix;
      typedef const char* _thruster_topic_suffix_type;
      _thruster_topic_suffix_type thruster_topic_suffix;
      typedef float _timeout_type;
      _timeout_type timeout;
      typedef float _max_thrust_type;
      _max_thrust_type max_thrust;
      typedef int32_t _n_thrusters_type;
      _n_thrusters_type n_thrusters;
      uint32_t allocation_matrix_length;
      typedef float _allocation_matrix_type;
      _allocation_matrix_type st_allocation_matrix;
      _allocation_matrix_type * allocation_matrix;

    GetThrusterManagerConfigResponse():
      tf_prefix(""),
      base_link(""),
      thruster_frame_base(""),
      thruster_topic_prefix(""),
      thruster_topic_suffix(""),
      timeout(0),
      max_thrust(0),
      n_thrusters(0),
      allocation_matrix_length(0), allocation_matrix(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      uint32_t length_tf_prefix = strlen(this->tf_prefix);
      varToArr(outbuffer + offset, length_tf_prefix);
      offset += 4;
      memcpy(outbuffer + offset, this->tf_prefix, length_tf_prefix);
      offset += length_tf_prefix;
      uint32_t length_base_link = strlen(this->base_link);
      varToArr(outbuffer + offset, length_base_link);
      offset += 4;
      memcpy(outbuffer + offset, this->base_link, length_base_link);
      offset += length_base_link;
      uint32_t length_thruster_frame_base = strlen(this->thruster_frame_base);
      varToArr(outbuffer + offset, length_thruster_frame_base);
      offset += 4;
      memcpy(outbuffer + offset, this->thruster_frame_base, length_thruster_frame_base);
      offset += length_thruster_frame_base;
      uint32_t length_thruster_topic_prefix = strlen(this->thruster_topic_prefix);
      varToArr(outbuffer + offset, length_thruster_topic_prefix);
      offset += 4;
      memcpy(outbuffer + offset, this->thruster_topic_prefix, length_thruster_topic_prefix);
      offset += length_thruster_topic_prefix;
      uint32_t length_thruster_topic_suffix = strlen(this->thruster_topic_suffix);
      varToArr(outbuffer + offset, length_thruster_topic_suffix);
      offset += 4;
      memcpy(outbuffer + offset, this->thruster_topic_suffix, length_thruster_topic_suffix);
      offset += length_thruster_topic_suffix;
      offset += serializeAvrFloat64(outbuffer + offset, this->timeout);
      offset += serializeAvrFloat64(outbuffer + offset, this->max_thrust);
      union {
        int32_t real;
        uint32_t base;
      } u_n_thrusters;
      u_n_thrusters.real = this->n_thrusters;
      *(outbuffer + offset + 0) = (u_n_thrusters.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_n_thrusters.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_n_thrusters.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_n_thrusters.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->n_thrusters);
      *(outbuffer + offset + 0) = (this->allocation_matrix_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->allocation_matrix_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->allocation_matrix_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->allocation_matrix_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->allocation_matrix_length);
      for( uint32_t i = 0; i < allocation_matrix_length; i++){
      offset += serializeAvrFloat64(outbuffer + offset, this->allocation_matrix[i]);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t length_tf_prefix;
      arrToVar(length_tf_prefix, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_tf_prefix; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_tf_prefix-1]=0;
      this->tf_prefix = (char *)(inbuffer + offset-1);
      offset += length_tf_prefix;
      uint32_t length_base_link;
      arrToVar(length_base_link, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_base_link; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_base_link-1]=0;
      this->base_link = (char *)(inbuffer + offset-1);
      offset += length_base_link;
      uint32_t length_thruster_frame_base;
      arrToVar(length_thruster_frame_base, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_thruster_frame_base; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_thruster_frame_base-1]=0;
      this->thruster_frame_base = (char *)(inbuffer + offset-1);
      offset += length_thruster_frame_base;
      uint32_t length_thruster_topic_prefix;
      arrToVar(length_thruster_topic_prefix, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_thruster_topic_prefix; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_thruster_topic_prefix-1]=0;
      this->thruster_topic_prefix = (char *)(inbuffer + offset-1);
      offset += length_thruster_topic_prefix;
      uint32_t length_thruster_topic_suffix;
      arrToVar(length_thruster_topic_suffix, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_thruster_topic_suffix; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_thruster_topic_suffix-1]=0;
      this->thruster_topic_suffix = (char *)(inbuffer + offset-1);
      offset += length_thruster_topic_suffix;
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->timeout));
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->max_thrust));
      union {
        int32_t real;
        uint32_t base;
      } u_n_thrusters;
      u_n_thrusters.base = 0;
      u_n_thrusters.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_n_thrusters.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_n_thrusters.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_n_thrusters.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->n_thrusters = u_n_thrusters.real;
      offset += sizeof(this->n_thrusters);
      uint32_t allocation_matrix_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      allocation_matrix_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      allocation_matrix_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      allocation_matrix_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->allocation_matrix_length);
      if(allocation_matrix_lengthT > allocation_matrix_length)
        this->allocation_matrix = (float*)realloc(this->allocation_matrix, allocation_matrix_lengthT * sizeof(float));
      allocation_matrix_length = allocation_matrix_lengthT;
      for( uint32_t i = 0; i < allocation_matrix_length; i++){
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->st_allocation_matrix));
        memcpy( &(this->allocation_matrix[i]), &(this->st_allocation_matrix), sizeof(float));
      }
     return offset;
    }

    const char * getType(){ return GETTHRUSTERMANAGERCONFIG; };
    const char * getMD5(){ return "b5a2d9d3bb510dd91fdb03f95e95b8de"; };

  };

  class GetThrusterManagerConfig {
    public:
    typedef GetThrusterManagerConfigRequest Request;
    typedef GetThrusterManagerConfigResponse Response;
  };

}
#endif
