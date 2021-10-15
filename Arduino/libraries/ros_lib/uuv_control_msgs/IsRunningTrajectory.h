#ifndef _ROS_SERVICE_IsRunningTrajectory_h
#define _ROS_SERVICE_IsRunningTrajectory_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace uuv_control_msgs
{

static const char ISRUNNINGTRAJECTORY[] = "uuv_control_msgs/IsRunningTrajectory";

  class IsRunningTrajectoryRequest : public ros::Msg
  {
    public:

    IsRunningTrajectoryRequest()
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

    const char * getType(){ return ISRUNNINGTRAJECTORY; };
    const char * getMD5(){ return "d41d8cd98f00b204e9800998ecf8427e"; };

  };

  class IsRunningTrajectoryResponse : public ros::Msg
  {
    public:
      typedef float _progress_type;
      _progress_type progress;

    IsRunningTrajectoryResponse():
      progress(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += serializeAvrFloat64(outbuffer + offset, this->progress);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->progress));
     return offset;
    }

    const char * getType(){ return ISRUNNINGTRAJECTORY; };
    const char * getMD5(){ return "7afca0099e0cddc25243b1e3569895fe"; };

  };

  class IsRunningTrajectory {
    public:
    typedef IsRunningTrajectoryRequest Request;
    typedef IsRunningTrajectoryResponse Response;
  };

}
#endif
