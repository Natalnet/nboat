#ifndef _ROS_SERVICE_SetCurrentModel_h
#define _ROS_SERVICE_SetCurrentModel_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace uuv_world_ros_plugins_msgs
{

static const char SETCURRENTMODEL[] = "uuv_world_ros_plugins_msgs/SetCurrentModel";

  class SetCurrentModelRequest : public ros::Msg
  {
    public:
      typedef float _mean_type;
      _mean_type mean;
      typedef float _min_type;
      _min_type min;
      typedef float _max_type;
      _max_type max;
      typedef float _noise_type;
      _noise_type noise;
      typedef float _mu_type;
      _mu_type mu;

    SetCurrentModelRequest():
      mean(0),
      min(0),
      max(0),
      noise(0),
      mu(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += serializeAvrFloat64(outbuffer + offset, this->mean);
      offset += serializeAvrFloat64(outbuffer + offset, this->min);
      offset += serializeAvrFloat64(outbuffer + offset, this->max);
      offset += serializeAvrFloat64(outbuffer + offset, this->noise);
      offset += serializeAvrFloat64(outbuffer + offset, this->mu);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->mean));
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->min));
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->max));
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->noise));
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->mu));
     return offset;
    }

    const char * getType(){ return SETCURRENTMODEL; };
    const char * getMD5(){ return "b8222571af4e4180b9b706d1e17ad7e1"; };

  };

  class SetCurrentModelResponse : public ros::Msg
  {
    public:
      typedef bool _success_type;
      _success_type success;

    SetCurrentModelResponse():
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

    const char * getType(){ return SETCURRENTMODEL; };
    const char * getMD5(){ return "358e233cde0c8a8bcfea4ce193f8fc15"; };

  };

  class SetCurrentModel {
    public:
    typedef SetCurrentModelRequest Request;
    typedef SetCurrentModelResponse Response;
  };

}
#endif
