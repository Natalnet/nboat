#include "BoatControl.h"
#include "SensorManager.h"

BoatControl *movementControl;
SensorManager *sensors;

void setup() {
  movementControl = new BoatControl();
  sensors = new SensorManager();
  //delay(3000);
  //_actuators->setThrusterPower(100);
  Serial.begin(9600);
}

void loop() {
  sensors->read();
  //Serial.println(sensors->getWind().direction);
  movementControl->thrusterControl(sensors);
}
