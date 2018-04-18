/*

  GPS_EM506.cpp - Library for getting curent position from GPS model EM506, compute heading and distance between two locations (lat, lon) using TinyGPS library.
  Created by Davi H. dos Santos, March 28, 2018.
  BSD license, all text above must be included in any redistribution.

*/

#include "Arduino.h"
#include "GPS_EM506.h"

GPS_EM506::GPS_EM506(){
  Serial3.begin(4800);
  ms = 1000;
  start = 0.0;
}

Location GPS_EM506::readPosition(){  
  start = millis();
  do 
  {
    while(Serial3.available())
    {
      c = Serial3.read();
      if(gps.encode(c))
      {
        gps.f_get_position(&_p1.latitude, &_p1.longitude);
        //direcao = gps.f_course();
        //velocidade = gps.f_speed_kmph();
      }
    }
  } while (millis() - start < ms);

  if (_p1.latitude == NULL || _p1.longitude == NULL){
    Serial.println("GPS still calibrating...");
  }

  return _p1;
}

float GPS_EM506::computeDistance(Location p1, Location p2){
  return TinyGPS::distance_between(p1.latitude, p1.longitude, p2.latitude, p2.longitude);
}

float GPS_EM506::computeHeading(Location p1, Location p2){
  heading = TinyGPS::course_to(p1.latitude, p1.longitude, p2.latitude, p2.longitude);
  if(heading > 180){
    heading = heading-360;
  }
  if(heading < -180){
    heading = heading+360;
  }
  return heading;
}
