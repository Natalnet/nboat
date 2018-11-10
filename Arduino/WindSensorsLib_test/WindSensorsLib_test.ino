//#include "WindSensor.h"
#include "SensorManager.h"
//#include "windSpeed_tst.h"
//#include "myLib.h"

//WindSensor wind;
//windSpeed_tst *wind
SensorManager *sensor;

void setup() {
  sensor = new SensorManager();
  Serial.begin(9600);
  //wind = new windt();

}

void loop() {
  sensor->read();
  //wind.read();
  //wind->read();
  //Serial.println(map(wind.getDirection(), 0, 180, 0, 100));
  //Serial.println(map(sensor->getWind().direction, 0, 180, 0, 100));
  
  //Serial.println(wind.getDirectionSigned());
  Serial.println(sensor->getWindRaw());
  //delay(100);  
  //Serial.print(wind.get().speed); Serial.println("  ");
}

/*45 -> 435 465
90 -> 65 85
135 -> 155 175
180 -> 265 285
-135 -> 605 625
-90 -> 925 945
-45 -> 865 885
0 -> 765 785
*/
