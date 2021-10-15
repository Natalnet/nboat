/*

  NavigationFunctions.h -Library that compile multiple NavigationFunctions behavior necessary for proper sailboat movement.
  Created by Davi H. dos Santos, March 28, 2018.
  BSD license, all text above must be included in any redistribution.

*/

#ifndef NavigationFunctions_h
#define NavigationFunctions_h

#include "Arduino.h"
#include "TinyGPS.h"
#include <StandardCplusplus.h>
#include <vector>
#include "Location.h"

using namespace std;

class NavigationFunctions
{
  public:
    NavigationFunctions();
    float findDistance(Location p1, Location p2);
    float findHeading(Location p1, Location p2);
    float adjustFrame(float sensor);
  private:
    float _heading;
};

#endif
