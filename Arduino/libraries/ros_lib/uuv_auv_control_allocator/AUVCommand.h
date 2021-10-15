#ifndef _ROS_uuv_auv_control_allocator_AUVCommand_h
#define _ROS_uuv_auv_control_allocator_AUVCommand_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"
#include "geometry_msgs/Wrench.h"

namespace uuv_auv_control_allocator
{

  class AUVCommand : public ros::Msg
  {
    public:
      typedef std_msgs::Header _header_type;
      _header_type header;
      typedef float _surge_speed_type;
      _surge_speed_type surge_speed;
      typedef geometry_msgs::Wrench _command_type;
      _command_type command;

    AUVCommand():
      header(),
      surge_speed(0),
      command()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      offset += serializeAvrFloat64(outbuffer + offset, this->surge_speed);
      offset += this->command.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->surge_speed));
      offset += this->command.deserialize(inbuffer + offset);
     return offset;
    }

    const char * getType(){ return "uuv_auv_control_allocator/AUVCommand"; };
    const char * getMD5(){ return "9d7c962f08b7f118399273df23351e7c"; };

  };

}
#endif