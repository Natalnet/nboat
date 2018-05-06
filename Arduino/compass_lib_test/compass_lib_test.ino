#include <Compass_HMC6352.h>

Compass_HMC6352 compass;

void setup(){
  Serial.begin(9600);
}


void loop() {
  compass.read();
  Serial.println(compass.getHeading());  
}
