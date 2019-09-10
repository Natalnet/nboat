#ifndef _ROS_SERVICE_GetThrusterCurve_h
#define _ROS_SERVICE_GetThrusterCurve_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace uuv_thruster_manager
{

static const char GETTHRUSTERCURVE[] = "uuv_thruster_manager/GetThrusterCurve";

  class GetThrusterCurveRequest : public ros::Msg
  {
    public:
      typedef float _min_type;
      _min_type min;
      typedef float _max_type;
      _max_type max;
      typedef int32_t _n_points_type;
      _n_points_type n_points;

    GetThrusterCurveRequest():
      min(0),
      max(0),
      n_points(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += serializeAvrFloat64(outbuffer + offset, this->min);
      offset += serializeAvrFloat64(outbuffer + offset, this->max);
      union {
        int32_t real;
        uint32_t base;
      } u_n_points;
      u_n_points.real = this->n_points;
      *(outbuffer + offset + 0) = (u_n_points.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_n_points.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_n_points.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_n_points.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->n_points);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->min));
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->max));
      union {
        int32_t real;
        uint32_t base;
      } u_n_points;
      u_n_points.base = 0;
      u_n_points.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_n_points.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_n_points.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_n_points.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->n_points = u_n_points.real;
      offset += sizeof(this->n_points);
     return offset;
    }

    const char * getType(){ return GETTHRUSTERCURVE; };
    const char * getMD5(){ return "3b8a1df953063c9de5f9a6419991fa0c"; };

  };

  class GetThrusterCurveResponse : public ros::Msg
  {
    public:
      uint32_t input_length;
      typedef float _input_type;
      _input_type st_input;
      _input_type * input;
      uint32_t thrust_length;
      typedef float _thrust_type;
      _thrust_type st_thrust;
      _thrust_type * thrust;

    GetThrusterCurveResponse():
      input_length(0), input(NULL),
      thrust_length(0), thrust(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->input_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->input_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->input_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->input_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->input_length);
      for( uint32_t i = 0; i < input_length; i++){
      offset += serializeAvrFloat64(outbuffer + offset, this->input[i]);
      }
      *(outbuffer + offset + 0) = (this->thrust_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->thrust_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->thrust_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->thrust_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->thrust_length);
      for( uint32_t i = 0; i < thrust_length; i++){
      offset += serializeAvrFloat64(outbuffer + offset, this->thrust[i]);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t input_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      input_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      input_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      input_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->input_length);
      if(input_lengthT > input_length)
        this->input = (float*)realloc(this->input, input_lengthT * sizeof(float));
      input_length = input_lengthT;
      for( uint32_t i = 0; i < input_length; i++){
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->st_input));
        memcpy( &(this->input[i]), &(this->st_input), sizeof(float));
      }
      uint32_t thrust_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      thrust_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      thrust_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      thrust_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->thrust_length);
      if(thrust_lengthT > thrust_length)
        this->thrust = (float*)realloc(this->thrust, thrust_lengthT * sizeof(float));
      thrust_length = thrust_lengthT;
      for( uint32_t i = 0; i < thrust_length; i++){
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->st_thrust));
        memcpy( &(this->thrust[i]), &(this->st_thrust), sizeof(float));
      }
     return offset;
    }

    const char * getType(){ return GETTHRUSTERCURVE; };
    const char * getMD5(){ return "183802edaba8fb9ba8a2d917792277f6"; };

  };

  class GetThrusterCurve {
    public:
    typedef GetThrusterCurveRequest Request;
    typedef GetThrusterCurveResponse Response;
  };

}
#endif
