#include "GPS.h"
#include "Compass.h"

GPS gps;
Location loc;
Compass comp;

void setup() {
  Serial.begin(9600);
}

void loop() {
  loc = gps.readPosition();
  Serial.print(loc.latitude,  6);
  Serial.print(", ");
  Serial.print(loc.longitude, 6);
  Serial.print("---------------- ");
  Serial.print(comp.readHeading());
  Serial.println();
}
