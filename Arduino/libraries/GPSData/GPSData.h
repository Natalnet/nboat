/*

  GPSData.cpp - Library for setting a position structure with latitude and longitude.
  Created by Davi H. dos Santos, March 28, 2018.
  BSD license, all text above must be included in any redistribution.

*/

#ifndef GPSData_h
#define GPSData_h

#include "Location.h"

struct GPSData {
	Location location;
	float course;
	float speed;
        String date;
};

#endif
