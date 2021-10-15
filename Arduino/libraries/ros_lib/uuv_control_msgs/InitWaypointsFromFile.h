#ifndef _ROS_SERVICE_InitWaypointsFromFile_h
#define _ROS_SERVICE_InitWaypointsFromFile_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/String.h"
#include "std_msgs/Time.h"

namespace uuv_control_msgs
{

static const char INITWAYPOINTSFROMFILE[] = "uuv_control_msgs/InitWaypointsFromFile";

  class InitWaypointsFromFileRequest : public ros::Msg
  {
    public:
      typedef std_msgs::Time _start_time_type;
      _start_time_type start_time;
      typedef bool _start_now_type;
      _start_now_type start_now;
      typedef std_msgs::String _filename_type;
      _filename_type filename;
      typedef std_msgs::String _interpolator_type;
      _interpolator_type interpolator;
      enum { LIPB = 'lipb' };
      enum { CUBIC = 'cubic' };
      enum { DUBINS = 'dubins' };
      enum { LINEAR = 'linear' };

    InitWaypointsFromFileRequest():
      start_time(),
      start_now(0),
      filename(),
      interpolator()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->start_time.serialize(outbuffer + offset);
      union {
        bool real;
        uint8_t base;
      } u_start_now;
      u_start_now.real = this->start_now;
      *(outbuffer + offset + 0) = (u_start_now.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->start_now);
      offset += this->filename.serialize(outbuffer + offset);
      offset += this->interpolator.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->start_time.deserialize(inbuffer + offset);
      union {
        bool real;
        uint8_t base;
      } u_start_now;
      u_start_now.base = 0;
      u_start_now.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->start_now = u_start_now.real;
      offset += sizeof(this->start_now);
      offset += this->filename.deserialize(inbuffer + offset);
      offset += this->interpolator.deserialize(inbuffer + offset);
     return offset;
    }

    const char * getType(){ return INITWAYPOINTSFROMFILE; };
    const char * getMD5(){ return "ddaf659bb5628d87c763d02c9d4cc76b"; };

  };

  class InitWaypointsFromFileResponse : public ros::Msg
  {
    public:
      typedef bool _success_type;
      _success_type success;

    InitWaypointsFromFileResponse():
      success(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_success;
      u_success.real = this->success;
      *(outbuffer + offset + 0) = (u_success.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->success);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_success;
      u_success.base = 0;
      u_success.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->success = u_success.real;
      offset += sizeof(this->success);
     return offset;
    }

    const char * getType(){ return INITWAYPOINTSFROMFILE; };
    const char * getMD5(){ return "358e233cde0c8a8bcfea4ce193f8fc15"; };

  };

  class InitWaypointsFromFile {
    public:
    typedef InitWaypointsFromFileRequest Request;
    typedef InitWaypointsFromFileResponse Response;
  };

}
#endif
