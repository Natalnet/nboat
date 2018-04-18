/*

  OdometrySensors.cpp - Library for getting curent heading from Compass model HMC6352.
  Created by Davi H. dos Santos, March 25, 2018.
  BSD license, all text above must be included in any redistribution.

*/


#include "Arduino.h"
#include "OdometrySensors.h"

OdometrySensors::OdometrySensors(){
  
}

bool OdometrySensors::checkSensors(){
  try {
    gps_EM506.readPosition();
  } catch (int e) {
    cout << "An exception occurred. Exception Nr. " << e << '\n';
  }

  try {
    compass_HMC6352.readHeading();
  } catch (const char* msg) {
    cout << "An exception occurred. Exception Nr. " << e << '\n';
  }
}


