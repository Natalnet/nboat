#ifndef _ROS_uuv_sensor_ros_plugins_msgs_DVLBeam_h
#define _ROS_uuv_sensor_ros_plugins_msgs_DVLBeam_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "geometry_msgs/PoseStamped.h"

namespace uuv_sensor_ros_plugins_msgs
{

  class DVLBeam : public ros::Msg
  {
    public:
      typedef float _range_type;
      _range_type range;
      typedef float _range_covariance_type;
      _range_covariance_type range_covariance;
      typedef float _velocity_type;
      _velocity_type velocity;
      typedef float _velocity_covariance_type;
      _velocity_covariance_type velocity_covariance;
      typedef geometry_msgs::PoseStamped _pose_type;
      _pose_type pose;

    DVLBeam():
      range(0),
      range_covariance(0),
      velocity(0),
      velocity_covariance(0),
      pose()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += serializeAvrFloat64(outbuffer + offset, this->range);
      offset += serializeAvrFloat64(outbuffer + offset, this->range_covariance);
      offset += serializeAvrFloat64(outbuffer + offset, this->velocity);
      offset += serializeAvrFloat64(outbuffer + offset, this->velocity_covariance);
      offset += this->pose.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->range));
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->range_covariance));
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->velocity));
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->velocity_covariance));
      offset += this->pose.deserialize(inbuffer + offset);
     return offset;
    }

    const char * getType(){ return "uuv_sensor_ros_plugins_msgs/DVLBeam"; };
    const char * getMD5(){ return "9e6a08aaf7a740b2c17ba2ab21dac602"; };

  };

}
#endif