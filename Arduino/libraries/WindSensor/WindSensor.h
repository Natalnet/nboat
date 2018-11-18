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
    float getDirectionSigned();

    void read();
    
  private:
    float readSpeed(int buttonPin = 2);
    float readDirection(int birutaPin = A0);
    float starttime, endtime, windSpeed, windDirection, _windDirectionSigned;
    int buttonState, buttonState_ant, windvaneRead, windvaneReadAnt;
    WindData _windData;

  /*
  //ANEMOMETER SETUP
  //medianFilter Filter;
  float radius = 0.055; //m from center pin to middle of cup
  float mps;
  int revolutions = 0;
  int rpm = 0;
  unsigned long lastmillis = 0;
  
  long lastWindIRQ=0;
  long lastWindChk=0;
  long windClickNo=0;*/
};

#endif
