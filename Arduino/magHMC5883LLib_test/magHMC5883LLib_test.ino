#include "Mag_HMC5883L.h"

Mag_HMC5883L mag;
float angle;

void setup() {
  Serial.begin(9600);

}

void loop() {
  angle = mag.readHeading();
  Serial.println(angle);
}
