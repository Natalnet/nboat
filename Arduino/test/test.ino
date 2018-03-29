#include "Location.h"

Location loc1;
Location loc2;

void setup() {
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  //loc.latitude = 10.0;
  loc1.latitude = 5.0;
  loc2.latitude = 7.0;
  Serial.println(loc1.latitude);
  Serial.println(loc2.latitude);
}


