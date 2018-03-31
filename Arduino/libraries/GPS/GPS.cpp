/*

  GPS.cpp - Library for getting curent position from GPS, compute heading and distance between two locations (lat, lon) using TinyGPS library.
  Created by Davi H. dos Santos, March 28, 2018.
  BSD license, all text above must be included in any redistribution.

*/

#include "Arduino.h"
#include "GPS.h"

GPS::GPS(){
  Serial3.begin(4800);
  ms = 500;
  start = 0.0;
}

Location GPS::readPosition(Location p1){  
  start = millis();
  do 
  {
    while(Serial3.available())
    {
      c = Serial3.read();
      if(gps.encode(c))
      {
        gps.f_get_position(&p1.latitude, &p1.longitude);
        //direcao = gps.f_course();
        //velocidade = gps.f_speed_kmph();
      }
    }
  } while (millis() - start < ms);
  return p1;
}

float GPS::computeDistance(Location p1, Location p2){
  return TinyGPS::distance_between(p1.latitude, p1.longitude, p2.latitude, p2.longitude);
}

float GPS::computeHeading(Location p1, Location p2){
  heading = TinyGPS::course_to(p1.latitude, p1.longitude, p2.latitude, p2.longitude);
  if(heading > 180){
    heading = heading-360;
  }
  if(heading < -180){
    heading = heading+360;
  }
  return heading;
}
