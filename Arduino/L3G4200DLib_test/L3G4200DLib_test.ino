#include "Gyro_L3G4200D.h"

Gyro_L3G4200D gyro;

void setup() {
  Serial.begin(9600);

}

void loop() {
  gyro.read();
  Serial.print("     ");
  Serial.print(gyro.get().x);
  Serial.print("; ");
  Serial.print(gyro.get().y);
  Serial.print("; ");
  Serial.println(gyro.get().z);
}
