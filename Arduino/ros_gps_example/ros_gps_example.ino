/*
 * rosserial PubSub Example
 * Prints "hello world!" and toggles led
 */

#include "GPS_EM506.h"
#include <ros.h>
#include <std_msgs/String.h>
#include <sensor_msgs/NavSatFix.h>
#include <geometry_msgs/Twist.h>
#include <std_msgs/Empty.h>
#include <std_msgs/Float64.h>

GPS_EM506 gps;

ros::NodeHandle  nh;

sensor_msgs::NavSatFix gps_msg;

std_msgs::Float64 gps_course;
std_msgs::Float64 gps_speed;

ros::Publisher chatter("gps/NavSatFix", &gps_msg);
ros::Publisher chatter2("gps/course", &gps_course);
ros::Publisher chatter3("gps/speed", &gps_speed);

void setup()
{
  nh.initNode();
  nh.advertise(chatter);
  nh.advertise(chatter2);
  nh.advertise(chatter3);
}

void loop()
{
  gps.read();
  gps_msg.latitude = gps.get().location.latitude;
  gps_msg.longitude = gps.get().location.longitude;
  gps_msg.header.frame_id = "gps";
  gps_msg.altitude = gps.get().altitude;

  gps_course.data = gps.get().course;
  gps_speed.data = gps.get().speed;
  
  chatter.publish( &gps_msg );
  chatter2.publish( &gps_course );
  chatter3.publish( &gps_speed );
  nh.spinOnce();
  delay(200);
}
