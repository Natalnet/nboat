#include "DualVNH5019MotorShield.h" //drive motor
DualVNH5019MotorShield md(2, 7, 6, A0, 2, 7, 12, A1);
 
void setup() {
  md.init();
}
 
void loop() {
  /*for(int i = 0; i < 200; i = i + 10){
    md.setM1Speed(i);
    delay(500);
  }*/
  md.setM1Speed(0); //-400 <-> +400
}
