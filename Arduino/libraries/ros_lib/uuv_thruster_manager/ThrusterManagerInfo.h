#ifndef _ROS_SERVICE_ThrusterManagerInfo_h
#define _ROS_SERVICE_ThrusterManagerInfo_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace uuv_thruster_manager
{

static const char THRUSTERMANAGERINFO[] = "uuv_thruster_manager/ThrusterManagerInfo";

  class ThrusterManagerInfoRequest : public ros::Msg
  {
    public:

    ThrusterManagerInfoRequest()
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

    const char * getType(){ return THRUSTERMANAGERINFO; };
    const char * getMD5(){ return "d41d8cd98f00b204e9800998ecf8427e"; };

  };

  class ThrusterManagerInfoResponse : public ros::Msg
  {
    public:
      typedef int32_t _n_thrusters_type;
      _n_thrusters_type n_thrusters;
      uint32_t allocation_matrix_length;
      typedef float _allocation_matrix_type;
      _allocation_matrix_type st_allocation_matrix;
      _allocation_matrix_type * allocation_matrix;
      typedef const char* _reference_frame_type;
      _reference_frame_type reference_frame;

    ThrusterManagerInfoResponse():
      n_thrusters(0),
      allocation_matrix_length(0), allocation_matrix(NULL),
      reference_frame("")
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        int32_t real;
        uint32_t base;
      } u_n_thrusters;
      u_n_thrusters.real = this->n_thrusters;
      *(outbuffer + offset + 0) = (u_n_thrusters.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_n_thrusters.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_n_thrusters.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_n_thrusters.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->n_thrusters);
      *(outbuffer + offset + 0) = (this->allocation_matrix_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->allocation_matrix_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->allocation_matrix_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->allocation_matrix_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->allocation_matrix_length);
      for( uint32_t i = 0; i < allocation_matrix_length; i++){
      offset += serializeAvrFloat64(outbuffer + offset, this->allocation_matrix[i]);
      }
      uint32_t length_reference_frame = strlen(this->reference_frame);
      varToArr(outbuffer + offset, length_reference_frame);
      offset += 4;
      memcpy(outbuffer + offset, this->reference_frame, length_reference_frame);
      offset += length_reference_frame;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        int32_t real;
        uint32_t base;
      } u_n_thrusters;
      u_n_thrusters.base = 0;
      u_n_thrusters.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_n_thrusters.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_n_thrusters.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_n_thrusters.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->n_thrusters = u_n_thrusters.real;
      offset += sizeof(this->n_thrusters);
      uint32_t allocation_matrix_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      allocation_matrix_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      allocation_matrix_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      allocation_matrix_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->allocation_matrix_length);
      if(allocation_matrix_lengthT > allocation_matrix_length)
        this->allocation_matrix = (float*)realloc(this->allocation_matrix, allocation_matrix_lengthT * sizeof(float));
      allocation_matrix_length = allocation_matrix_lengthT;
      for( uint32_t i = 0; i < allocation_matrix_length; i++){
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->st_allocation_matrix));
        memcpy( &(this->allocation_matrix[i]), &(this->st_allocation_matrix), sizeof(float));
      }
      uint32_t length_reference_frame;
      arrToVar(length_reference_frame, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_reference_frame; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_reference_frame-1]=0;
      this->reference_frame = (char *)(inbuffer + offset-1);
      offset += length_reference_frame;
     return offset;
    }

    const char * getType(){ return THRUSTERMANAGERINFO; };
    const char * getMD5(){ return "66fb8ab2f9c5649d97263c955edb636e"; };

  };

  class ThrusterManagerInfo {
    public:
    typedef ThrusterManagerInfoRequest Request;
    typedef ThrusterManagerInfoResponse Response;
  };

}
#endif
