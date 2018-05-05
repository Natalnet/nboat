#include "Location.h"
#include "SailboatMiniActuatorDrivers.h"

SailboatMiniActuatorDrivers *sailboatAct;

void setup() {
  sailboatAct = new SailboatMiniActuatorDrivers();
  Serial.begin(9600);
}

void loop() {
  sailboatAct->setRudderAngle(40);
  sailboatAct->setSailAngle(12);
  //delay(15);
  /*for(int i = 0; i <= 180; i = i+1){
    sailboatAct->setRudderAngle(i);
    sailboatAct->setSailAngle(i);
    Serial.println(i);
    delay(50);
  }
  
  for(int i = 180; i >= 0; i -= 1){
    sailboatAct->setRudderAngle(i);
    sailboatAct->setSailAngle(i);
    Serial.println(i);
    delay(50);
  }*/
}


