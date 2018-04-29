/*

  GPS_EM506.h - Library for getting curent position from GPS model EM506, compute heading and distance between two locations (lat, lon) using TinyGPS library.
  Created by Davi H. dos Santos, March 28, 2018.
  BSD license, all text above must be included in any redistribution.

*/

#ifndef GPS_EM506_h
#define GPS_EM506_h

#include "Arduino.h"
#include "TinyGPS.h"
#include "Location.h"
#include "GPSData.h"

class GPS_EM506
{
  public:
    GPS_EM506();

    void read();
    GPSData get();

    float findDistance(Location p1, Location p2);
    float findHeading(Location p1, Location p2);
  private:
    TinyGPS gps;
    unsigned long start, ms;
    int c;
    GPSData _gpsData;
    Location _p1;
    float heading, _gpsCourse, _gpsSpeed;
};

#endif
