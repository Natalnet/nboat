#ifndef _ROS_uuv_sensor_ros_plugins_msgs_Salinity_h
#define _ROS_uuv_sensor_ros_plugins_msgs_Salinity_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"

namespace uuv_sensor_ros_plugins_msgs
{

  class Salinity : public ros::Msg
  {
    public:
      typedef std_msgs::Header _header_type;
      _header_type header;
      typedef float _salinity_type;
      _salinity_type salinity;
      typedef float _variance_type;
      _variance_type variance;
      typedef const char* _unit_type;
      _unit_type unit;
      enum { PSU = "psu" };
      enum { PPM = "ppm" };
      enum { PPT = "ppt" };

    Salinity():
      header(),
      salinity(0),
      variance(0),
      unit("")
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      offset += serializeAvrFloat64(outbuffer + offset, this->salinity);
      offset += serializeAvrFloat64(outbuffer + offset, this->variance);
      uint32_t length_unit = strlen(this->unit);
      varToArr(outbuffer + offset, length_unit);
      offset += 4;
      memcpy(outbuffer + offset, this->unit, length_unit);
      offset += length_unit;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->salinity));
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->variance));
      uint32_t length_unit;
      arrToVar(length_unit, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_unit; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_unit-1]=0;
      this->unit = (char *)(inbuffer + offset-1);
      offset += length_unit;
     return offset;
    }

    const char * getType(){ return "uuv_sensor_ros_plugins_msgs/Salinity"; };
    const char * getMD5(){ return "4d20de37b8b3a344b3f4c36f2192b257"; };

  };

}
#endif