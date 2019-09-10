#ifndef _ROS_uuv_sensor_ros_plugins_msgs_PositionWithCovariance_h
#define _ROS_uuv_sensor_ros_plugins_msgs_PositionWithCovariance_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "geometry_msgs/Point.h"

namespace uuv_sensor_ros_plugins_msgs
{

  class PositionWithCovariance : public ros::Msg
  {
    public:
      typedef geometry_msgs::Point _pos_type;
      _pos_type pos;
      float covariance[9];

    PositionWithCovariance():
      pos(),
      covariance()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->pos.serialize(outbuffer + offset);
      for( uint32_t i = 0; i < 9; i++){
      offset += serializeAvrFloat64(outbuffer + offset, this->covariance[i]);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->pos.deserialize(inbuffer + offset);
      for( uint32_t i = 0; i < 9; i++){
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->covariance[i]));
      }
     return offset;
    }

    const char * getType(){ return "uuv_sensor_ros_plugins_msgs/PositionWithCovariance"; };
    const char * getMD5(){ return "4a54596b2ea1a0ed659f46ab0b26f202"; };

  };

}
#endif