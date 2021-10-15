#ifndef _ROS_SERVICE_GetModelProperties_h
#define _ROS_SERVICE_GetModelProperties_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "uuv_gazebo_ros_plugins_msgs/UnderwaterObjectModel.h"

namespace uuv_gazebo_ros_plugins_msgs
{

static const char GETMODELPROPERTIES[] = "uuv_gazebo_ros_plugins_msgs/GetModelProperties";

  class GetModelPropertiesRequest : public ros::Msg
  {
    public:

    GetModelPropertiesRequest()
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

    const char * getType(){ return GETMODELPROPERTIES; };
    const char * getMD5(){ return "d41d8cd98f00b204e9800998ecf8427e"; };

  };

  class GetModelPropertiesResponse : public ros::Msg
  {
    public:
      uint32_t link_names_length;
      typedef char* _link_names_type;
      _link_names_type st_link_names;
      _link_names_type * link_names;
      uint32_t models_length;
      typedef uuv_gazebo_ros_plugins_msgs::UnderwaterObjectModel _models_type;
      _models_type st_models;
      _models_type * models;

    GetModelPropertiesResponse():
      link_names_length(0), link_names(NULL),
      models_length(0), models(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->link_names_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->link_names_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->link_names_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->link_names_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->link_names_length);
      for( uint32_t i = 0; i < link_names_length; i++){
      uint32_t length_link_namesi = strlen(this->link_names[i]);
      varToArr(outbuffer + offset, length_link_namesi);
      offset += 4;
      memcpy(outbuffer + offset, this->link_names[i], length_link_namesi);
      offset += length_link_namesi;
      }
      *(outbuffer + offset + 0) = (this->models_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->models_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->models_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->models_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->models_length);
      for( uint32_t i = 0; i < models_length; i++){
      offset += this->models[i].serialize(outbuffer + offset);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t link_names_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      link_names_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      link_names_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      link_names_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->link_names_length);
      if(link_names_lengthT > link_names_length)
        this->link_names = (char**)realloc(this->link_names, link_names_lengthT * sizeof(char*));
      link_names_length = link_names_lengthT;
      for( uint32_t i = 0; i < link_names_length; i++){
      uint32_t length_st_link_names;
      arrToVar(length_st_link_names, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_st_link_names; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_st_link_names-1]=0;
      this->st_link_names = (char *)(inbuffer + offset-1);
      offset += length_st_link_names;
        memcpy( &(this->link_names[i]), &(this->st_link_names), sizeof(char*));
      }
      uint32_t models_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      models_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      models_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      models_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->models_length);
      if(models_lengthT > models_length)
        this->models = (uuv_gazebo_ros_plugins_msgs::UnderwaterObjectModel*)realloc(this->models, models_lengthT * sizeof(uuv_gazebo_ros_plugins_msgs::UnderwaterObjectModel));
      models_length = models_lengthT;
      for( uint32_t i = 0; i < models_length; i++){
      offset += this->st_models.deserialize(inbuffer + offset);
        memcpy( &(this->models[i]), &(this->st_models), sizeof(uuv_gazebo_ros_plugins_msgs::UnderwaterObjectModel));
      }
     return offset;
    }

    const char * getType(){ return GETMODELPROPERTIES; };
    const char * getMD5(){ return "222d64ab6fa46c24f1abd065170ebe7a"; };

  };

  class GetModelProperties {
    public:
    typedef GetModelPropertiesRequest Request;
    typedef GetModelPropertiesResponse Response;
  };

}
#endif
