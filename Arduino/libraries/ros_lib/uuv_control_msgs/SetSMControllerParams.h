#ifndef _ROS_SERVICE_SetSMControllerParams_h
#define _ROS_SERVICE_SetSMControllerParams_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace uuv_control_msgs
{

static const char SETSMCONTROLLERPARAMS[] = "uuv_control_msgs/SetSMControllerParams";

  class SetSMControllerParamsRequest : public ros::Msg
  {
    public:
      uint32_t K_length;
      typedef float _K_type;
      _K_type st_K;
      _K_type * K;
      uint32_t Kd_length;
      typedef float _Kd_type;
      _Kd_type st_Kd;
      _Kd_type * Kd;
      uint32_t Ki_length;
      typedef float _Ki_type;
      _Ki_type st_Ki;
      _Ki_type * Ki;
      uint32_t slope_length;
      typedef float _slope_type;
      _slope_type st_slope;
      _slope_type * slope;

    SetSMControllerParamsRequest():
      K_length(0), K(NULL),
      Kd_length(0), Kd(NULL),
      Ki_length(0), Ki(NULL),
      slope_length(0), slope(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->K_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->K_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->K_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->K_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->K_length);
      for( uint32_t i = 0; i < K_length; i++){
      offset += serializeAvrFloat64(outbuffer + offset, this->K[i]);
      }
      *(outbuffer + offset + 0) = (this->Kd_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->Kd_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->Kd_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->Kd_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->Kd_length);
      for( uint32_t i = 0; i < Kd_length; i++){
      offset += serializeAvrFloat64(outbuffer + offset, this->Kd[i]);
      }
      *(outbuffer + offset + 0) = (this->Ki_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->Ki_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->Ki_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->Ki_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->Ki_length);
      for( uint32_t i = 0; i < Ki_length; i++){
      offset += serializeAvrFloat64(outbuffer + offset, this->Ki[i]);
      }
      *(outbuffer + offset + 0) = (this->slope_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->slope_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->slope_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->slope_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->slope_length);
      for( uint32_t i = 0; i < slope_length; i++){
      offset += serializeAvrFloat64(outbuffer + offset, this->slope[i]);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t K_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      K_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      K_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      K_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->K_length);
      if(K_lengthT > K_length)
        this->K = (float*)realloc(this->K, K_lengthT * sizeof(float));
      K_length = K_lengthT;
      for( uint32_t i = 0; i < K_length; i++){
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->st_K));
        memcpy( &(this->K[i]), &(this->st_K), sizeof(float));
      }
      uint32_t Kd_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      Kd_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      Kd_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      Kd_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->Kd_length);
      if(Kd_lengthT > Kd_length)
        this->Kd = (float*)realloc(this->Kd, Kd_lengthT * sizeof(float));
      Kd_length = Kd_lengthT;
      for( uint32_t i = 0; i < Kd_length; i++){
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->st_Kd));
        memcpy( &(this->Kd[i]), &(this->st_Kd), sizeof(float));
      }
      uint32_t Ki_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      Ki_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      Ki_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      Ki_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->Ki_length);
      if(Ki_lengthT > Ki_length)
        this->Ki = (float*)realloc(this->Ki, Ki_lengthT * sizeof(float));
      Ki_length = Ki_lengthT;
      for( uint32_t i = 0; i < Ki_length; i++){
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->st_Ki));
        memcpy( &(this->Ki[i]), &(this->st_Ki), sizeof(float));
      }
      uint32_t slope_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      slope_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      slope_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      slope_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->slope_length);
      if(slope_lengthT > slope_length)
        this->slope = (float*)realloc(this->slope, slope_lengthT * sizeof(float));
      slope_length = slope_lengthT;
      for( uint32_t i = 0; i < slope_length; i++){
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->st_slope));
        memcpy( &(this->slope[i]), &(this->st_slope), sizeof(float));
      }
     return offset;
    }

    const char * getType(){ return SETSMCONTROLLERPARAMS; };
    const char * getMD5(){ return "dc294c7929e39ce02ce0ce70a116b3b3"; };

  };

  class SetSMControllerParamsResponse : public ros::Msg
  {
    public:
      typedef bool _success_type;
      _success_type success;

    SetSMControllerParamsResponse():
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

    const char * getType(){ return SETSMCONTROLLERPARAMS; };
    const char * getMD5(){ return "358e233cde0c8a8bcfea4ce193f8fc15"; };

  };

  class SetSMControllerParams {
    public:
    typedef SetSMControllerParamsRequest Request;
    typedef SetSMControllerParamsResponse Response;
  };

}
#endif
