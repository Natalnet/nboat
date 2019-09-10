#ifndef _ROS_concert_msgs_ConcertClients_h
#define _ROS_concert_msgs_ConcertClients_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "concert_msgs/ConcertClient.h"

namespace concert_msgs
{

  class ConcertClients : public ros::Msg
  {
    public:
      uint32_t clients_length;
      typedef concert_msgs::ConcertClient _clients_type;
      _clients_type st_clients;
      _clients_type * clients;
      uint32_t missing_clients_length;
      typedef concert_msgs::ConcertClient _missing_clients_type;
      _missing_clients_type st_missing_clients;
      _missing_clients_type * missing_clients;
      uint32_t pending_clients_length;
      typedef concert_msgs::ConcertClient _pending_clients_type;
      _pending_clients_type st_pending_clients;
      _pending_clients_type * pending_clients;

    ConcertClients():
      clients_length(0), clients(NULL),
      missing_clients_length(0), missing_clients(NULL),
      pending_clients_length(0), pending_clients(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->clients_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->clients_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->clients_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->clients_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->clients_length);
      for( uint32_t i = 0; i < clients_length; i++){
      offset += this->clients[i].serialize(outbuffer + offset);
      }
      *(outbuffer + offset + 0) = (this->missing_clients_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->missing_clients_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->missing_clients_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->missing_clients_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->missing_clients_length);
      for( uint32_t i = 0; i < missing_clients_length; i++){
      offset += this->missing_clients[i].serialize(outbuffer + offset);
      }
      *(outbuffer + offset + 0) = (this->pending_clients_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->pending_clients_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->pending_clients_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->pending_clients_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->pending_clients_length);
      for( uint32_t i = 0; i < pending_clients_length; i++){
      offset += this->pending_clients[i].serialize(outbuffer + offset);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t clients_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      clients_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      clients_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      clients_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->clients_length);
      if(clients_lengthT > clients_length)
        this->clients = (concert_msgs::ConcertClient*)realloc(this->clients, clients_lengthT * sizeof(concert_msgs::ConcertClient));
      clients_length = clients_lengthT;
      for( uint32_t i = 0; i < clients_length; i++){
      offset += this->st_clients.deserialize(inbuffer + offset);
        memcpy( &(this->clients[i]), &(this->st_clients), sizeof(concert_msgs::ConcertClient));
      }
      uint32_t missing_clients_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      missing_clients_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      missing_clients_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      missing_clients_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->missing_clients_length);
      if(missing_clients_lengthT > missing_clients_length)
        this->missing_clients = (concert_msgs::ConcertClient*)realloc(this->missing_clients, missing_clients_lengthT * sizeof(concert_msgs::ConcertClient));
      missing_clients_length = missing_clients_lengthT;
      for( uint32_t i = 0; i < missing_clients_length; i++){
      offset += this->st_missing_clients.deserialize(inbuffer + offset);
        memcpy( &(this->missing_clients[i]), &(this->st_missing_clients), sizeof(concert_msgs::ConcertClient));
      }
      uint32_t pending_clients_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      pending_clients_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      pending_clients_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      pending_clients_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->pending_clients_length);
      if(pending_clients_lengthT > pending_clients_length)
        this->pending_clients = (concert_msgs::ConcertClient*)realloc(this->pending_clients, pending_clients_lengthT * sizeof(concert_msgs::ConcertClient));
      pending_clients_length = pending_clients_lengthT;
      for( uint32_t i = 0; i < pending_clients_length; i++){
      offset += this->st_pending_clients.deserialize(inbuffer + offset);
        memcpy( &(this->pending_clients[i]), &(this->st_pending_clients), sizeof(concert_msgs::ConcertClient));
      }
     return offset;
    }

    const char * getType(){ return "concert_msgs/ConcertClients"; };
    const char * getMD5(){ return "6950d7da025bef00c62c809b8487d74f"; };

  };

}
#endif