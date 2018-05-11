/*

  GPS_EM506.cpp - Library for getting curent position from GPS model EM506, compute heading and distance between two locations (lat, lon) using TinyGPS library.
  Created by Davi H. dos Santos, March 28, 2018.
  BSD license, all text above must be included in any redistribution.

*/

#include "Arduino.h"
#include "GPS_EM506.h"

GPS_EM506::GPS_EM506(){
  Serial3.begin(4800);
  ms = 30;
  start = 0.0;
}

void GPS_EM506::read(){
  start = millis();
  do 
  {
    while(Serial3.available())
    {
      c = Serial3.read();
      if(gps.encode(c))
      {
        gps.f_get_position(&_p1.latitude, &_p1.longitude);
        _gpsCourse = gps.f_course();
        _gpsSpeed = gps.f_speed_kmph();
        gps.crack_datetime(&_year, &_month, &_day, &_hour, &_minute, &_second, &_hundredths, &_age);
        if (_age != TinyGPS::GPS_INVALID_AGE){
          sprintf(_gpsDate, "%02d:%02d:%02d", _hour-3, _minute, _second);
          sprintf(_gpsDateFull, "%02d/%02d/%02d %02d:%02d:%02d", _month, _day, _year, _hour-3, _minute, _second);
        }
      }
    }
  } while (millis() - start < ms);

  if (_p1.latitude == NULL || _p1.longitude == NULL){
    Serial.println("GPS still calibrating...");
  }

  _gpsData.location = _p1;
  _gpsData.course = _gpsCourse;
  _gpsData.speed = _gpsSpeed;
  _gpsData.date = String(_gpsDate);
  _gpsData.dateFull = String(_gpsDateFull);

}

GPSData GPS_EM506::get(){
  return _gpsData;
}
