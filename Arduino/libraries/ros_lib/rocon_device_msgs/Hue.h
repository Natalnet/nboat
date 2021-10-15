#ifndef _ROS_rocon_device_msgs_Hue_h
#define _ROS_rocon_device_msgs_Hue_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "rocon_device_msgs/HueState.h"

namespace rocon_device_msgs
{

  class Hue : public ros::Msg
  {
    public:
      typedef int32_t _light_id_type;
      _light_id_type light_id;
      typedef const char* _type_type;
      _type_type type;
      typedef const char* _name_type;
      _name_type name;
      typedef const char* _modelid_type;
      _modelid_type modelid;
      typedef const char* _swvesion_type;
      _swvesion_type swvesion;
      typedef rocon_device_msgs::HueState _state_type;
      _state_type state;

    Hue():
      light_id(0),
      type(""),
      name(""),
      modelid(""),
      swvesion(""),
      state()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        int32_t real;
        uint32_t base;
      } u_light_id;
      u_light_id.real = this->light_id;
      *(outbuffer + offset + 0) = (u_light_id.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_light_id.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_light_id.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_light_id.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->light_id);
      uint32_t length_type = strlen(this->type);
      varToArr(outbuffer + offset, length_type);
      offset += 4;
      memcpy(outbuffer + offset, this->type, length_type);
      offset += length_type;
      uint32_t length_name = strlen(this->name);
      varToArr(outbuffer + offset, length_name);
      offset += 4;
      memcpy(outbuffer + offset, this->name, length_name);
      offset += length_name;
      uint32_t length_modelid = strlen(this->modelid);
      varToArr(outbuffer + offset, length_modelid);
      offset += 4;
      memcpy(outbuffer + offset, this->modelid, length_modelid);
      offset += length_modelid;
      uint32_t length_swvesion = strlen(this->swvesion);
      varToArr(outbuffer + offset, length_swvesion);
      offset += 4;
      memcpy(outbuffer + offset, this->swvesion, length_swvesion);
      offset += length_swvesion;
      offset += this->state.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        int32_t real;
        uint32_t base;
      } u_light_id;
      u_light_id.base = 0;
      u_light_id.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_light_id.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_light_id.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_light_id.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->light_id = u_light_id.real;
      offset += sizeof(this->light_id);
      uint32_t length_type;
      arrToVar(length_type, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_type; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_type-1]=0;
      this->type = (char *)(inbuffer + offset-1);
      offset += length_type;
      uint32_t length_name;
      arrToVar(length_name, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_name; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_name-1]=0;
      this->name = (char *)(inbuffer + offset-1);
      offset += length_name;
      uint32_t length_modelid;
      arrToVar(length_modelid, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_modelid; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_modelid-1]=0;
      this->modelid = (char *)(inbuffer + offset-1);
      offset += length_modelid;
      uint32_t length_swvesion;
      arrToVar(length_swvesion, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_swvesion; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_swvesion-1]=0;
      this->swvesion = (char *)(inbuffer + offset-1);
      offset += length_swvesion;
      offset += this->state.deserialize(inbuffer + offset);
     return offset;
    }

    const char * getType(){ return "rocon_device_msgs/Hue"; };
    const char * getMD5(){ return "468758d766494876ea4e198e409600ee"; };

  };

}
#endif