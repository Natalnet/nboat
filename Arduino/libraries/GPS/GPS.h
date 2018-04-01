/*

  GPS.h - Library for getting curent position from GPS, compute heading and distance between two locations (lat, lon) using TinyGPS library.
  Created by Davi H. dos Santos, March 28, 2018.
  BSD license, all text above must be included in any redistribution.

*/

#ifndef GPS_h
#define GPS_h

#include "Arduino.h"
#include "TinyGPS.h"
#include "Location.h"

class GPS
{
  public:
    GPS();
    Location readPosition();
    float computeDistance(Location p1, Location p2);
    float computeHeading(Location p1, Location p2);
  private:
    TinyGPS gps;
    unsigned long start, ms;
    int c;
    Location _p1, _p2;
    float heading;
};

#endif
