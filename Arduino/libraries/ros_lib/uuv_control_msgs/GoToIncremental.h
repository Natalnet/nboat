#ifndef _ROS_SERVICE_GoToIncremental_h
#define _ROS_SERVICE_GoToIncremental_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "geometry_msgs/Point.h"

namespace uuv_control_msgs
{

static const char GOTOINCREMENTAL[] = "uuv_control_msgs/GoToIncremental";

  class GoToIncrementalRequest : public ros::Msg
  {
    public:
      typedef geometry_msgs::Point _step_type;
      _step_type step;
      typedef float _max_forward_speed_type;
      _max_forward_speed_type max_forward_speed;
      typedef const char* _interpolator_type;
      _interpolator_type interpolator;
      enum { LIPB = 'lipb' };
      enum { CUBIC = 'cubic' };
      enum { DUBINS = 'dubins' };
      enum { LINEAR = 'linear' };

    GoToIncrementalRequest():
      step(),
      max_forward_speed(0),
      interpolator("")
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->step.serialize(outbuffer + offset);
      offset += serializeAvrFloat64(outbuffer + offset, this->max_forward_speed);
      uint32_t length_interpolator = strlen(this->interpolator);
      varToArr(outbuffer + offset, length_interpolator);
      offset += 4;
      memcpy(outbuffer + offset, this->interpolator, length_interpolator);
      offset += length_interpolator;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->step.deserialize(inbuffer + offset);
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->max_forward_speed));
      uint32_t length_interpolator;
      arrToVar(length_interpolator, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_interpolator; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_interpolator-1]=0;
      this->interpolator = (char *)(inbuffer + offset-1);
      offset += length_interpolator;
     return offset;
    }

    const char * getType(){ return GOTOINCREMENTAL; };
    const char * getMD5(){ return "83b72c3bd49f592c1f3511f3c61026e3"; };

  };

  class GoToIncrementalResponse : public ros::Msg
  {
    public:
      typedef bool _success_type;
      _success_type success;

    GoToIncrementalResponse():
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

    const char * getType(){ return GOTOINCREMENTAL; };
    const char * getMD5(){ return "358e233cde0c8a8bcfea4ce193f8fc15"; };

  };

  class GoToIncremental {
    public:
    typedef GoToIncrementalRequest Request;
    typedef GoToIncrementalResponse Response;
  };

}
#endif
