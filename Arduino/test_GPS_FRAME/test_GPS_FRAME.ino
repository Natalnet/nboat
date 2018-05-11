#include "TinyGPS.h"

//Navigation *nav;

void setup() {
  //nav = new Navigation();
  Serial.begin(9600);

}

void loop() {
  Serial.println(TinyGPS::course_to(-5.842893, -35.197407, -5.840383, -34.990960));
}
