#include "GPS_EM506.h"
#include "Compass_HMC6352.h"

GPS_EM506 gps;
Location loc;
Compass_HMC6352 comp;
float startTime, endTime;

void setup() {
  Serial.begin(9600);
}

void loop() {
  startTime = millis();
  loc = gps.readPosition();
  endTime = millis();
  Serial.print(loc.latitude,  6);
  Serial.print(", ");
  Serial.print(loc.longitude, 6);
  Serial.print("---------------- ");
  Serial.print(endTime-startTime);
  startTime = millis();
  Serial.print("---------------- ");
  Serial.print(comp.readHeading());
  endTime = millis();
  Serial.print("---------------- ");
  Serial.print(endTime-startTime);
  Serial.println();
}
