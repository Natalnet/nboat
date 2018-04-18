#include "Location.h"
#include "ActuatorsDrivers.h"
#include "BoatControl.h"

ActuatorsDrivers act;
BoatControl rudder;

Location loc1, tempLocation;
Location loc2;

void setup() {
  Serial.begin(9600);
  
  tempLocation.latitude = -5.842986;
  tempLocation.longitude = -35.197465;

}

void loop() {
  // put your main code here, to run repeatedly:
  rudder.rudderHeadingControl(tempLocation);
  //delay(500);
  
  //act.setRudderPositionBoat(0);
  //act.setThrusterPower(0);
}


