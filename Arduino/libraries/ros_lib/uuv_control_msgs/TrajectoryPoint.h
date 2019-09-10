#ifndef _ROS_uuv_control_msgs_TrajectoryPoint_h
#define _ROS_uuv_control_msgs_TrajectoryPoint_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"
#include "geometry_msgs/Pose.h"
#include "geometry_msgs/Twist.h"
#include "geometry_msgs/Accel.h"

namespace uuv_control_msgs
{

  class TrajectoryPoint : public ros::Msg
  {
    public:
      typedef std_msgs::Header _header_type;
      _header_type header;
      typedef geometry_msgs::Pose _pose_type;
      _pose_type pose;
      typedef geometry_msgs::Twist _velocity_type;
      _velocity_type velocity;
      typedef geometry_msgs::Accel _acceleration_type;
      _acceleration_type acceleration;

    TrajectoryPoint():
      header(),
      pose(),
      velocity(),
      acceleration()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      offset += this->pose.serialize(outbuffer + offset);
      offset += this->velocity.serialize(outbuffer + offset);
      offset += this->acceleration.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      offset += this->pose.deserialize(inbuffer + offset);
      offset += this->velocity.deserialize(inbuffer + offset);
      offset += this->acceleration.deserialize(inbuffer + offset);
     return offset;
    }

    const char * getType(){ return "uuv_control_msgs/TrajectoryPoint"; };
    const char * getMD5(){ return "93e068582370cddd8d8a46dda0c2eaf2"; };

  };

}
#endif