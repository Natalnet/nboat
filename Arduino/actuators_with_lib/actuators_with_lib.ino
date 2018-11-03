#include "BoatControl.h"
#include "SensorManager.h"

BoatControl *movementControl;
SensorManager *sensors;

void setup() {
  movementControl = new BoatControl();
  sensors = new SensorManager();
  movementControl->initThruster();
  delay(3000);
  //_actuators->setThrusterPower(100);
  Serial.begin(9600);
}

void loop() {
  //Serial.println(sensors->getWind().direction);
  sensors->read();
  movementControl->thrusterControl(sensors);
}
