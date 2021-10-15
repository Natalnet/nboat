#ifndef _ROS_uuv_sensor_ros_plugins_msgs_PositionWithCovarianceStamped_h
#define _ROS_uuv_sensor_ros_plugins_msgs_PositionWithCovarianceStamped_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"
#include "uuv_sensor_ros_plugins_msgs/PositionWithCovariance.h"

namespace uuv_sensor_ros_plugins_msgs
{

  class PositionWithCovarianceStamped : public ros::Msg
  {
    public:
      typedef std_msgs::Header _header_type;
      _header_type header;
      typedef uuv_sensor_ros_plugins_msgs::PositionWithCovariance _pos_type;
      _pos_type pos;

    PositionWithCovarianceStamped():
      header(),
      pos()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      offset += this->pos.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      offset += this->pos.deserialize(inbuffer + offset);
     return offset;
    }

    const char * getType(){ return "uuv_sensor_ros_plugins_msgs/PositionWithCovarianceStamped"; };
    const char * getMD5(){ return "ef0ae60585e532ef356441a1a701f864"; };

  };

}
#endif