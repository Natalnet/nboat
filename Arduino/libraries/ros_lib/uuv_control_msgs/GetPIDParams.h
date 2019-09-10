#ifndef _ROS_SERVICE_GetPIDParams_h
#define _ROS_SERVICE_GetPIDParams_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace uuv_control_msgs
{

static const char GETPIDPARAMS[] = "uuv_control_msgs/GetPIDParams";

  class GetPIDParamsRequest : public ros::Msg
  {
    public:

    GetPIDParamsRequest()
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

    const char * getType(){ return GETPIDPARAMS; };
    const char * getMD5(){ return "d41d8cd98f00b204e9800998ecf8427e"; };

  };

  class GetPIDParamsResponse : public ros::Msg
  {
    public:
      uint32_t Kp_length;
      typedef float _Kp_type;
      _Kp_type st_Kp;
      _Kp_type * Kp;
      uint32_t Kd_length;
      typedef float _Kd_type;
      _Kd_type st_Kd;
      _Kd_type * Kd;
      uint32_t Ki_length;
      typedef float _Ki_type;
      _Ki_type st_Ki;
      _Ki_type * Ki;

    GetPIDParamsResponse():
      Kp_length(0), Kp(NULL),
      Kd_length(0), Kd(NULL),
      Ki_length(0), Ki(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->Kp_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->Kp_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->Kp_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->Kp_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->Kp_length);
      for( uint32_t i = 0; i < Kp_length; i++){
      offset += serializeAvrFloat64(outbuffer + offset, this->Kp[i]);
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
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t Kp_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      Kp_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      Kp_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      Kp_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->Kp_length);
      if(Kp_lengthT > Kp_length)
        this->Kp = (float*)realloc(this->Kp, Kp_lengthT * sizeof(float));
      Kp_length = Kp_lengthT;
      for( uint32_t i = 0; i < Kp_length; i++){
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->st_Kp));
        memcpy( &(this->Kp[i]), &(this->st_Kp), sizeof(float));
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
     return offset;
    }

    const char * getType(){ return GETPIDPARAMS; };
    const char * getMD5(){ return "1dae001799e4bc231c788fb194cf733a"; };

  };

  class GetPIDParams {
    public:
    typedef GetPIDParamsRequest Request;
    typedef GetPIDParamsResponse Response;
  };

}
#endif
