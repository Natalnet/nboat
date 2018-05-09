//#include "WindSensor.h"
#include "windSpeed_tst.h"
//#include "myLib.h"

//WindSensor wind;
windSpeed_tst wind;

void setup() {
  Serial.begin(9600);
//  wind = new WindSensor();

}

void loop() {
//  wind.read();
  wind.read();
  //Serial.print(wind.get().direction); Serial.print("  ");
  //Serial.print(wind.get().speed); Serial.println("  ");
}
