#include "WindSensor.h"
//#include "windSpeed_tst.h"
//#include "myLib.h"

WindSensor wind;
//windSpeed_tst *wind;

void setup() {
  Serial.begin(9600);
//  wind = new windSpeed_tst();

}

void loop() {
//  wind.read();
  wind.read();
  Serial.print(wind.get().direction); Serial.println("  ");
}
