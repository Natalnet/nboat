#include <Compass.h>

Compass compass(104.0);

void setup(){
  Serial.begin(9600);
}


void loop() {
  Serial.println(compass.get_value());  
}
