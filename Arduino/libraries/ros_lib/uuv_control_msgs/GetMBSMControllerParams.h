#ifndef _ROS_SERVICE_GetMBSMControllerParams_h
#define _ROS_SERVICE_GetMBSMControllerParams_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace uuv_control_msgs
{

static const char GETMBSMCONTROLLERPARAMS[] = "uuv_control_msgs/GetMBSMControllerParams";

  class GetMBSMControllerParamsRequest : public ros::Msg
  {
    public:

    GetMBSMControllerParamsRequest()
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

    const char * getType(){ return GETMBSMCONTROLLERPARAMS; };
    const char * getMD5(){ return "d41d8cd98f00b204e9800998ecf8427e"; };

  };

  class GetMBSMControllerParamsResponse : public ros::Msg
  {
    public:
      uint32_t lambda_length;
      typedef float _lambda_type;
      _lambda_type st_lambda;
      _lambda_type * lambda;
      uint32_t rho_constant_length;
      typedef float _rho_constant_type;
      _rho_constant_type st_rho_constant;
      _rho_constant_type * rho_constant;
      uint32_t k_length;
      typedef float _k_type;
      _k_type st_k;
      _k_type * k;
      uint32_t c_length;
      typedef float _c_type;
      _c_type st_c;
      _c_type * c;
      uint32_t adapt_slope_length;
      typedef float _adapt_slope_type;
      _adapt_slope_type st_adapt_slope;
      _adapt_slope_type * adapt_slope;
      uint32_t rho_0_length;
      typedef float _rho_0_type;
      _rho_0_type st_rho_0;
      _rho_0_type * rho_0;
      typedef float _drift_prevent_type;
      _drift_prevent_type drift_prevent;

    GetMBSMControllerParamsResponse():
      lambda_length(0), lambda(NULL),
      rho_constant_length(0), rho_constant(NULL),
      k_length(0), k(NULL),
      c_length(0), c(NULL),
      adapt_slope_length(0), adapt_slope(NULL),
      rho_0_length(0), rho_0(NULL),
      drift_prevent(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->lambda_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->lambda_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->lambda_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->lambda_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->lambda_length);
      for( uint32_t i = 0; i < lambda_length; i++){
      offset += serializeAvrFloat64(outbuffer + offset, this->lambda[i]);
      }
      *(outbuffer + offset + 0) = (this->rho_constant_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->rho_constant_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->rho_constant_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->rho_constant_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->rho_constant_length);
      for( uint32_t i = 0; i < rho_constant_length; i++){
      offset += serializeAvrFloat64(outbuffer + offset, this->rho_constant[i]);
      }
      *(outbuffer + offset + 0) = (this->k_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->k_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->k_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->k_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->k_length);
      for( uint32_t i = 0; i < k_length; i++){
      offset += serializeAvrFloat64(outbuffer + offset, this->k[i]);
      }
      *(outbuffer + offset + 0) = (this->c_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->c_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->c_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->c_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->c_length);
      for( uint32_t i = 0; i < c_length; i++){
      offset += serializeAvrFloat64(outbuffer + offset, this->c[i]);
      }
      *(outbuffer + offset + 0) = (this->adapt_slope_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->adapt_slope_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->adapt_slope_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->adapt_slope_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->adapt_slope_length);
      for( uint32_t i = 0; i < adapt_slope_length; i++){
      offset += serializeAvrFloat64(outbuffer + offset, this->adapt_slope[i]);
      }
      *(outbuffer + offset + 0) = (this->rho_0_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->rho_0_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->rho_0_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->rho_0_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->rho_0_length);
      for( uint32_t i = 0; i < rho_0_length; i++){
      offset += serializeAvrFloat64(outbuffer + offset, this->rho_0[i]);
      }
      offset += serializeAvrFloat64(outbuffer + offset, this->drift_prevent);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t lambda_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      lambda_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      lambda_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      lambda_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->lambda_length);
      if(lambda_lengthT > lambda_length)
        this->lambda = (float*)realloc(this->lambda, lambda_lengthT * sizeof(float));
      lambda_length = lambda_lengthT;
      for( uint32_t i = 0; i < lambda_length; i++){
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->st_lambda));
        memcpy( &(this->lambda[i]), &(this->st_lambda), sizeof(float));
      }
      uint32_t rho_constant_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      rho_constant_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      rho_constant_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      rho_constant_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->rho_constant_length);
      if(rho_constant_lengthT > rho_constant_length)
        this->rho_constant = (float*)realloc(this->rho_constant, rho_constant_lengthT * sizeof(float));
      rho_constant_length = rho_constant_lengthT;
      for( uint32_t i = 0; i < rho_constant_length; i++){
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->st_rho_constant));
        memcpy( &(this->rho_constant[i]), &(this->st_rho_constant), sizeof(float));
      }
      uint32_t k_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      k_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      k_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      k_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->k_length);
      if(k_lengthT > k_length)
        this->k = (float*)realloc(this->k, k_lengthT * sizeof(float));
      k_length = k_lengthT;
      for( uint32_t i = 0; i < k_length; i++){
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->st_k));
        memcpy( &(this->k[i]), &(this->st_k), sizeof(float));
      }
      uint32_t c_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      c_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      c_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      c_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->c_length);
      if(c_lengthT > c_length)
        this->c = (float*)realloc(this->c, c_lengthT * sizeof(float));
      c_length = c_lengthT;
      for( uint32_t i = 0; i < c_length; i++){
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->st_c));
        memcpy( &(this->c[i]), &(this->st_c), sizeof(float));
      }
      uint32_t adapt_slope_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      adapt_slope_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      adapt_slope_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      adapt_slope_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->adapt_slope_length);
      if(adapt_slope_lengthT > adapt_slope_length)
        this->adapt_slope = (float*)realloc(this->adapt_slope, adapt_slope_lengthT * sizeof(float));
      adapt_slope_length = adapt_slope_lengthT;
      for( uint32_t i = 0; i < adapt_slope_length; i++){
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->st_adapt_slope));
        memcpy( &(this->adapt_slope[i]), &(this->st_adapt_slope), sizeof(float));
      }
      uint32_t rho_0_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      rho_0_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      rho_0_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      rho_0_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->rho_0_length);
      if(rho_0_lengthT > rho_0_length)
        this->rho_0 = (float*)realloc(this->rho_0, rho_0_lengthT * sizeof(float));
      rho_0_length = rho_0_lengthT;
      for( uint32_t i = 0; i < rho_0_length; i++){
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->st_rho_0));
        memcpy( &(this->rho_0[i]), &(this->st_rho_0), sizeof(float));
      }
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->drift_prevent));
     return offset;
    }

    const char * getType(){ return GETMBSMCONTROLLERPARAMS; };
    const char * getMD5(){ return "7293aecc8487ffe3e998814d65aa6940"; };

  };

  class GetMBSMControllerParams {
    public:
    typedef GetMBSMControllerParamsRequest Request;
    typedef GetMBSMControllerParamsResponse Response;
  };

}
#endif
