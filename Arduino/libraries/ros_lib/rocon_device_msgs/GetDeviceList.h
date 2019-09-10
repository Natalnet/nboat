#ifndef _ROS_SERVICE_GetDeviceList_h
#define _ROS_SERVICE_GetDeviceList_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "rocon_device_msgs/Device.h"

namespace rocon_device_msgs
{

static const char GETDEVICELIST[] = "rocon_device_msgs/GetDeviceList";

  class GetDeviceListRequest : public ros::Msg
  {
    public:

    GetDeviceListRequest()
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

    const char * getType(){ return GETDEVICELIST; };
    const char * getMD5(){ return "d41d8cd98f00b204e9800998ecf8427e"; };

  };

  class GetDeviceListResponse : public ros::Msg
  {
    public:
      uint32_t devices_length;
      typedef rocon_device_msgs::Device _devices_type;
      _devices_type st_devices;
      _devices_type * devices;

    GetDeviceListResponse():
      devices_length(0), devices(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->devices_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->devices_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->devices_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->devices_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->devices_length);
      for( uint32_t i = 0; i < devices_length; i++){
      offset += this->devices[i].serialize(outbuffer + offset);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t devices_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      devices_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      devices_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      devices_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->devices_length);
      if(devices_lengthT > devices_length)
        this->devices = (rocon_device_msgs::Device*)realloc(this->devices, devices_lengthT * sizeof(rocon_device_msgs::Device));
      devices_length = devices_lengthT;
      for( uint32_t i = 0; i < devices_length; i++){
      offset += this->st_devices.deserialize(inbuffer + offset);
        memcpy( &(this->devices[i]), &(this->st_devices), sizeof(rocon_device_msgs::Device));
      }
     return offset;
    }

    const char * getType(){ return GETDEVICELIST; };
    const char * getMD5(){ return "47ac4241194bb5519686779949c9843b"; };

  };

  class GetDeviceList {
    public:
    typedef GetDeviceListRequest Request;
    typedef GetDeviceListResponse Response;
  };

}
#endif
