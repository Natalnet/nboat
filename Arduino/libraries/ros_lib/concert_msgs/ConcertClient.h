#ifndef _ROS_concert_msgs_ConcertClient_h
#define _ROS_concert_msgs_ConcertClient_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "rocon_std_msgs/MasterInfo.h"
#include "gateway_msgs/ConnectionStatistics.h"
#include "rocon_app_manager_msgs/Rapp.h"

namespace concert_msgs
{

  class ConcertClient : public ros::Msg
  {
    public:
      typedef const char* _name_type;
      _name_type name;
      typedef const char* _gateway_name_type;
      _gateway_name_type gateway_name;
      typedef rocon_std_msgs::MasterInfo _platform_info_type;
      _platform_info_type platform_info;
      typedef bool _is_local_client_type;
      _is_local_client_type is_local_client;
      typedef const char* _state_type;
      _state_type state;
      typedef const char* _ip_type;
      _ip_type ip;
      typedef gateway_msgs::ConnectionStatistics _conn_stats_type;
      _conn_stats_type conn_stats;
      uint32_t rapps_length;
      typedef rocon_app_manager_msgs::Rapp _rapps_type;
      _rapps_type st_rapps;
      _rapps_type * rapps;

    ConcertClient():
      name(""),
      gateway_name(""),
      platform_info(),
      is_local_client(0),
      state(""),
      ip(""),
      conn_stats(),
      rapps_length(0), rapps(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      uint32_t length_name = strlen(this->name);
      varToArr(outbuffer + offset, length_name);
      offset += 4;
      memcpy(outbuffer + offset, this->name, length_name);
      offset += length_name;
      uint32_t length_gateway_name = strlen(this->gateway_name);
      varToArr(outbuffer + offset, length_gateway_name);
      offset += 4;
      memcpy(outbuffer + offset, this->gateway_name, length_gateway_name);
      offset += length_gateway_name;
      offset += this->platform_info.serialize(outbuffer + offset);
      union {
        bool real;
        uint8_t base;
      } u_is_local_client;
      u_is_local_client.real = this->is_local_client;
      *(outbuffer + offset + 0) = (u_is_local_client.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->is_local_client);
      uint32_t length_state = strlen(this->state);
      varToArr(outbuffer + offset, length_state);
      offset += 4;
      memcpy(outbuffer + offset, this->state, length_state);
      offset += length_state;
      uint32_t length_ip = strlen(this->ip);
      varToArr(outbuffer + offset, length_ip);
      offset += 4;
      memcpy(outbuffer + offset, this->ip, length_ip);
      offset += length_ip;
      offset += this->conn_stats.serialize(outbuffer + offset);
      *(outbuffer + offset + 0) = (this->rapps_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->rapps_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->rapps_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->rapps_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->rapps_length);
      for( uint32_t i = 0; i < rapps_length; i++){
      offset += this->rapps[i].serialize(outbuffer + offset);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t length_name;
      arrToVar(length_name, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_name; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_name-1]=0;
      this->name = (char *)(inbuffer + offset-1);
      offset += length_name;
      uint32_t length_gateway_name;
      arrToVar(length_gateway_name, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_gateway_name; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_gateway_name-1]=0;
      this->gateway_name = (char *)(inbuffer + offset-1);
      offset += length_gateway_name;
      offset += this->platform_info.deserialize(inbuffer + offset);
      union {
        bool real;
        uint8_t base;
      } u_is_local_client;
      u_is_local_client.base = 0;
      u_is_local_client.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->is_local_client = u_is_local_client.real;
      offset += sizeof(this->is_local_client);
      uint32_t length_state;
      arrToVar(length_state, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_state; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_state-1]=0;
      this->state = (char *)(inbuffer + offset-1);
      offset += length_state;
      uint32_t length_ip;
      arrToVar(length_ip, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_ip; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_ip-1]=0;
      this->ip = (char *)(inbuffer + offset-1);
      offset += length_ip;
      offset += this->conn_stats.deserialize(inbuffer + offset);
      uint32_t rapps_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      rapps_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      rapps_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      rapps_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->rapps_length);
      if(rapps_lengthT > rapps_length)
        this->rapps = (rocon_app_manager_msgs::Rapp*)realloc(this->rapps, rapps_lengthT * sizeof(rocon_app_manager_msgs::Rapp));
      rapps_length = rapps_lengthT;
      for( uint32_t i = 0; i < rapps_length; i++){
      offset += this->st_rapps.deserialize(inbuffer + offset);
        memcpy( &(this->rapps[i]), &(this->st_rapps), sizeof(rocon_app_manager_msgs::Rapp));
      }
     return offset;
    }

    const char * getType(){ return "concert_msgs/ConcertClient"; };
    const char * getMD5(){ return "e86054949de7944800d67af80496ca28"; };

  };

}
#endif