/*

  WeatherSensors.h - Library for getting info from weather sensors used in N-Boat project.
  Created by Davi H. dos Santos, March 28, 2018.
  BSD license, all text above must be included in any redistribution.

*/

#ifndef WeatherSensors_h
#define WeatherSensors_h

#include "Arduino.h"

class WeatherSensors
{
  public:
    WeatherSensors();
    float readWindSpeed(int buttonPin = 2);
    float readWindDirection(int birutaPin = A0);
  private:
    float starttime, endtime, windSpeed, windDirection;
    int buttonState, buttonState_ant, windvaneRead;
};

#endif
