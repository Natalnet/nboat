#include "DualVNH5019MotorShield.h" //drive motor
DualVNH5019MotorShield md;

void setup() {
  md.init();
  Serial.begin(9600);

}

void loop() {
  md.setM1Speed(200); //-400 <-> +400
}
