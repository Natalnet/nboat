#ifndef _ROS_rocon_device_msgs_HueState_h
#define _ROS_rocon_device_msgs_HueState_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace rocon_device_msgs
{

  class HueState : public ros::Msg
  {
    public:
      typedef bool _on_type;
      _on_type on;
      typedef uint16_t _hue_type;
      _hue_type hue;
      typedef uint8_t _sat_type;
      _sat_type sat;
      typedef uint8_t _bri_type;
      _bri_type bri;
      typedef bool _reachable_type;
      _reachable_type reachable;
      typedef const char* _color_type;
      _color_type color;
      enum { OFF =  "OFF" };
      enum { WHITE =  "WHITE" };
      enum { RED =  "RED" };
      enum { GREEN =  "GREEN" };
      enum { BLUE =  "BLUE" };
      enum { YELLOW =  "YELLOW" };
      enum { ORANGE =  "ORANGE" };
      enum { MAGENTA =  "MAGENTA" };
      enum { VIOLET =  "VIOLET" };

    HueState():
      on(0),
      hue(0),
      sat(0),
      bri(0),
      reachable(0),
      color("")
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_on;
      u_on.real = this->on;
      *(outbuffer + offset + 0) = (u_on.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->on);
      *(outbuffer + offset + 0) = (this->hue >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->hue >> (8 * 1)) & 0xFF;
      offset += sizeof(this->hue);
      *(outbuffer + offset + 0) = (this->sat >> (8 * 0)) & 0xFF;
      offset += sizeof(this->sat);
      *(outbuffer + offset + 0) = (this->bri >> (8 * 0)) & 0xFF;
      offset += sizeof(this->bri);
      union {
        bool real;
        uint8_t base;
      } u_reachable;
      u_reachable.real = this->reachable;
      *(outbuffer + offset + 0) = (u_reachable.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->reachable);
      uint32_t length_color = strlen(this->color);
      varToArr(outbuffer + offset, length_color);
      offset += 4;
      memcpy(outbuffer + offset, this->color, length_color);
      offset += length_color;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_on;
      u_on.base = 0;
      u_on.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->on = u_on.real;
      offset += sizeof(this->on);
      this->hue =  ((uint16_t) (*(inbuffer + offset)));
      this->hue |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      offset += sizeof(this->hue);
      this->sat =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->sat);
      this->bri =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->bri);
      union {
        bool real;
        uint8_t base;
      } u_reachable;
      u_reachable.base = 0;
      u_reachable.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->reachable = u_reachable.real;
      offset += sizeof(this->reachable);
      uint32_t length_color;
      arrToVar(length_color, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_color; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_color-1]=0;
      this->color = (char *)(inbuffer + offset-1);
      offset += length_color;
     return offset;
    }

    const char * getType(){ return "rocon_device_msgs/HueState"; };
    const char * getMD5(){ return "3fa6578e37628a062177e792a87fa213"; };

  };

}
#endif