#ifndef _ROS_SERVICE_SetThrusterManagerConfig_h
#define _ROS_SERVICE_SetThrusterManagerConfig_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace uuv_thruster_manager
{

static const char SETTHRUSTERMANAGERCONFIG[] = "uuv_thruster_manager/SetThrusterManagerConfig";

  class SetThrusterManagerConfigRequest : public ros::Msg
  {
    public:
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
      enum { DEFAULT_BASE_LINK =  /base_link };
      enum { DEFAULT_THRUSTER_FRAME_BASE =  /thruster_ };
      enum { DEFAULT_PREFIX =  thrusters/ };
      enum { DEFAULT_SUFFIX =  /input };

    SetThrusterManagerConfigRequest():
      base_link(""),
      thruster_frame_base(""),
      thruster_topic_prefix(""),
      thruster_topic_suffix(""),
      timeout(0),
      max_thrust(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
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
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
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
     return offset;
    }

    const char * getType(){ return SETTHRUSTERMANAGERCONFIG; };
    const char * getMD5(){ return "148002d6fd6bf6684e854899710838a2"; };

  };

  class SetThrusterManagerConfigResponse : public ros::Msg
  {
    public:
      typedef bool _success_type;
      _success_type success;

    SetThrusterManagerConfigResponse():
      success(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_success;
      u_success.real = this->success;
      *(outbuffer + offset + 0) = (u_success.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->success);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_success;
      u_success.base = 0;
      u_success.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->success = u_success.real;
      offset += sizeof(this->success);
     return offset;
    }

    const char * getType(){ return SETTHRUSTERMANAGERCONFIG; };
    const char * getMD5(){ return "358e233cde0c8a8bcfea4ce193f8fc15"; };

  };

  class SetThrusterManagerConfig {
    public:
    typedef SetThrusterManagerConfigRequest Request;
    typedef SetThrusterManagerConfigResponse Response;
  };

}
#endif
