/*

  NavigationFunctions.cpp - Library that compile multiple NavigationFunctions behavior necessary for proper sailboat movement.
  Created by Davi H. dos Santos, March 28, 2018.
  BSD license, all text above must be included in any redistribution.

*/

#include "Arduino.h"
#include "NavigationFunctions.h"

NavigationFunctions::NavigationFunctions(){
}

float NavigationFunctions::adjustFrame(float sensor) {
  if (sensor > 180) {
    sensor = sensor - 360;
  }
  if (sensor < -180) {
    sensor = sensor + 360;
  }
  return sensor;
}

float NavigationFunctions::findDistance(Location p1, Location p2){
  return TinyGPS::distance_between(p1.latitude, p1.longitude, p2.latitude, p2.longitude);
}

float NavigationFunctions::findHeading(Location p1, Location p2){
  _heading = TinyGPS::course_to(p1.latitude, p1.longitude, p2.latitude, p2.longitude);
  _heading = adjustFrame(_heading);
  return _heading;
}
