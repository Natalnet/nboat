/*

  WindSensor.h - Library for getting info from Wind sensors used in N-Boat project.
  Created by Davi H. dos Santos, March 28, 2018.
  BSD license, all text above must be included in any redistribution.

*/

#ifndef WindSensor_h
#define WindSensor_h

#include "Arduino.h"
#include "WindData.h"

class WindSensor
{
  public:
    WindSensor();
    float getSpeed();
    float getDirection();
    WindData get();
    int getDirectionRaw();

    void read();
    
  private:
    float readSpeed(int buttonPin = 2);
    float readDirection(int birutaPin = A0);
    float starttime, endtime, windSpeed, windDirection;
    int buttonState, buttonState_ant, windvaneRead, windvaneReadAnt;
    WindData _windData;
};

#endif
