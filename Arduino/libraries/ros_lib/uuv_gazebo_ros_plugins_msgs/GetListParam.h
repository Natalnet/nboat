#ifndef _ROS_SERVICE_GetListParam_h
#define _ROS_SERVICE_GetListParam_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace uuv_gazebo_ros_plugins_msgs
{

static const char GETLISTPARAM[] = "uuv_gazebo_ros_plugins_msgs/GetListParam";

  class GetListParamRequest : public ros::Msg
  {
    public:

    GetListParamRequest()
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

    const char * getType(){ return GETLISTPARAM; };
    const char * getMD5(){ return "d41d8cd98f00b204e9800998ecf8427e"; };

  };

  class GetListParamResponse : public ros::Msg
  {
    public:
      typedef const char* _description_type;
      _description_type description;
      uint32_t tags_length;
      typedef char* _tags_type;
      _tags_type st_tags;
      _tags_type * tags;
      uint32_t data_length;
      typedef float _data_type;
      _data_type st_data;
      _data_type * data;

    GetListParamResponse():
      description(""),
      tags_length(0), tags(NULL),
      data_length(0), data(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      uint32_t length_description = strlen(this->description);
      varToArr(outbuffer + offset, length_description);
      offset += 4;
      memcpy(outbuffer + offset, this->description, length_description);
      offset += length_description;
      *(outbuffer + offset + 0) = (this->tags_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->tags_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->tags_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->tags_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->tags_length);
      for( uint32_t i = 0; i < tags_length; i++){
      uint32_t length_tagsi = strlen(this->tags[i]);
      varToArr(outbuffer + offset, length_tagsi);
      offset += 4;
      memcpy(outbuffer + offset, this->tags[i], length_tagsi);
      offset += length_tagsi;
      }
      *(outbuffer + offset + 0) = (this->data_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->data_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->data_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->data_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->data_length);
      for( uint32_t i = 0; i < data_length; i++){
      offset += serializeAvrFloat64(outbuffer + offset, this->data[i]);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t length_description;
      arrToVar(length_description, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_description; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_description-1]=0;
      this->description = (char *)(inbuffer + offset-1);
      offset += length_description;
      uint32_t tags_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      tags_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      tags_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      tags_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->tags_length);
      if(tags_lengthT > tags_length)
        this->tags = (char**)realloc(this->tags, tags_lengthT * sizeof(char*));
      tags_length = tags_lengthT;
      for( uint32_t i = 0; i < tags_length; i++){
      uint32_t length_st_tags;
      arrToVar(length_st_tags, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_st_tags; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_st_tags-1]=0;
      this->st_tags = (char *)(inbuffer + offset-1);
      offset += length_st_tags;
        memcpy( &(this->tags[i]), &(this->st_tags), sizeof(char*));
      }
      uint32_t data_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      data_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      data_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      data_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->data_length);
      if(data_lengthT > data_length)
        this->data = (float*)realloc(this->data, data_lengthT * sizeof(float));
      data_length = data_lengthT;
      for( uint32_t i = 0; i < data_length; i++){
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->st_data));
        memcpy( &(this->data[i]), &(this->st_data), sizeof(float));
      }
     return offset;
    }

    const char * getType(){ return GETLISTPARAM; };
    const char * getMD5(){ return "d3415e6ab074fdc7b0bd82ed3d6fccc7"; };

  };

  class GetListParam {
    public:
    typedef GetListParamRequest Request;
    typedef GetListParamResponse Response;
  };

}
#endif
