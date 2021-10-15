#ifndef _ROS_concert_msgs_LinkGraph_h
#define _ROS_concert_msgs_LinkGraph_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "concert_msgs/LinkNode.h"
#include "concert_msgs/LinkConnection.h"
#include "concert_msgs/LinkEdge.h"

namespace concert_msgs
{

  class LinkGraph : public ros::Msg
  {
    public:
      uint32_t nodes_length;
      typedef concert_msgs::LinkNode _nodes_type;
      _nodes_type st_nodes;
      _nodes_type * nodes;
      uint32_t topics_length;
      typedef concert_msgs::LinkConnection _topics_type;
      _topics_type st_topics;
      _topics_type * topics;
      uint32_t actions_length;
      typedef concert_msgs::LinkConnection _actions_type;
      _actions_type st_actions;
      _actions_type * actions;
      uint32_t services_length;
      typedef concert_msgs::LinkConnection _services_type;
      _services_type st_services;
      _services_type * services;
      uint32_t edges_length;
      typedef concert_msgs::LinkEdge _edges_type;
      _edges_type st_edges;
      _edges_type * edges;

    LinkGraph():
      nodes_length(0), nodes(NULL),
      topics_length(0), topics(NULL),
      actions_length(0), actions(NULL),
      services_length(0), services(NULL),
      edges_length(0), edges(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->nodes_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->nodes_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->nodes_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->nodes_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->nodes_length);
      for( uint32_t i = 0; i < nodes_length; i++){
      offset += this->nodes[i].serialize(outbuffer + offset);
      }
      *(outbuffer + offset + 0) = (this->topics_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->topics_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->topics_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->topics_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->topics_length);
      for( uint32_t i = 0; i < topics_length; i++){
      offset += this->topics[i].serialize(outbuffer + offset);
      }
      *(outbuffer + offset + 0) = (this->actions_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->actions_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->actions_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->actions_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->actions_length);
      for( uint32_t i = 0; i < actions_length; i++){
      offset += this->actions[i].serialize(outbuffer + offset);
      }
      *(outbuffer + offset + 0) = (this->services_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->services_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->services_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->services_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->services_length);
      for( uint32_t i = 0; i < services_length; i++){
      offset += this->services[i].serialize(outbuffer + offset);
      }
      *(outbuffer + offset + 0) = (this->edges_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->edges_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->edges_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->edges_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->edges_length);
      for( uint32_t i = 0; i < edges_length; i++){
      offset += this->edges[i].serialize(outbuffer + offset);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t nodes_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      nodes_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      nodes_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      nodes_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->nodes_length);
      if(nodes_lengthT > nodes_length)
        this->nodes = (concert_msgs::LinkNode*)realloc(this->nodes, nodes_lengthT * sizeof(concert_msgs::LinkNode));
      nodes_length = nodes_lengthT;
      for( uint32_t i = 0; i < nodes_length; i++){
      offset += this->st_nodes.deserialize(inbuffer + offset);
        memcpy( &(this->nodes[i]), &(this->st_nodes), sizeof(concert_msgs::LinkNode));
      }
      uint32_t topics_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      topics_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      topics_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      topics_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->topics_length);
      if(topics_lengthT > topics_length)
        this->topics = (concert_msgs::LinkConnection*)realloc(this->topics, topics_lengthT * sizeof(concert_msgs::LinkConnection));
      topics_length = topics_lengthT;
      for( uint32_t i = 0; i < topics_length; i++){
      offset += this->st_topics.deserialize(inbuffer + offset);
        memcpy( &(this->topics[i]), &(this->st_topics), sizeof(concert_msgs::LinkConnection));
      }
      uint32_t actions_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      actions_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      actions_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      actions_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->actions_length);
      if(actions_lengthT > actions_length)
        this->actions = (concert_msgs::LinkConnection*)realloc(this->actions, actions_lengthT * sizeof(concert_msgs::LinkConnection));
      actions_length = actions_lengthT;
      for( uint32_t i = 0; i < actions_length; i++){
      offset += this->st_actions.deserialize(inbuffer + offset);
        memcpy( &(this->actions[i]), &(this->st_actions), sizeof(concert_msgs::LinkConnection));
      }
      uint32_t services_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      services_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      services_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      services_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->services_length);
      if(services_lengthT > services_length)
        this->services = (concert_msgs::LinkConnection*)realloc(this->services, services_lengthT * sizeof(concert_msgs::LinkConnection));
      services_length = services_lengthT;
      for( uint32_t i = 0; i < services_length; i++){
      offset += this->st_services.deserialize(inbuffer + offset);
        memcpy( &(this->services[i]), &(this->st_services), sizeof(concert_msgs::LinkConnection));
      }
      uint32_t edges_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      edges_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      edges_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      edges_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->edges_length);
      if(edges_lengthT > edges_length)
        this->edges = (concert_msgs::LinkEdge*)realloc(this->edges, edges_lengthT * sizeof(concert_msgs::LinkEdge));
      edges_length = edges_lengthT;
      for( uint32_t i = 0; i < edges_length; i++){
      offset += this->st_edges.deserialize(inbuffer + offset);
        memcpy( &(this->edges[i]), &(this->st_edges), sizeof(concert_msgs::LinkEdge));
      }
     return offset;
    }

    const char * getType(){ return "concert_msgs/LinkGraph"; };
    const char * getMD5(){ return "227c6e11d605d4647851f3e358cf10ba"; };

  };

}
#endif