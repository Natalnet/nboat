/* Sweep
 by BARRAGAN <http://barraganstudio.com>
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Sweep
*/

#include "BoatControl.h"
#include "SensorManager.h"

BoatControl *movementControl;
double channel[3];
SensorManager *sensors;

void setup() {
  movementControl = new BoatControl(5,0.5);
  pinMode(34, INPUT);
  pinMode(35, INPUT);
  pinMode(36, INPUT);
}

void loop() {
  channel[0] = pulseIn(34, HIGH);
  channel[1] = pulseIn(35, HIGH);
  channel[2] = pulseIn(36, HIGH);
  sensors->read();
  
  movementControl->thrusterRCControl(sensors, channel[1]);
  movementControl->rudderRCControl(sensors, channel[2]);
}

