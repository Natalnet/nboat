#include "DualVNH5019MotorShield.h" //drive motor

DualVNH5019MotorShield md;

void setup() {
  md.init();
  Serial.begin(9600);
}

void loop() {
  set_speed_suave(0, 300, 1);
}

void set_speed_suave(int vel_atual, int vel_ant, int motor){
  // vel_ant -> vel_atual
  // 100 -> 200  = erro 100
  // 100 -> -100 = erro -200
  // vai da velocidade anterior até a atual de forma suave
  // evitar grande pico de corrente
  
  int erro = vel_atual - vel_ant;
  if (abs(erro) > 200){
    if (erro > 0){
      // fazer isso só pros primeiros 200. pula de 5 em 5
      for (int i = vel_ant; i <= (vel_ant + 200); i = i + 5)
      {
        if (motor == 1){
          md.setM1Speed(i);
          Serial.println(i);
        }        
        if (motor == 2){
          md.setM2Speed(i);
        }
        delay(20);
      }
    }
    if (erro < 0){
      // fazer isso só pros primeiros 200
      for (int i = vel_ant; i >= (vel_ant - 200); i = i - 5)
      {
        if (motor == 1){
          md.setM1Speed(i);
          Serial.println(i);
        }
        
        if (motor == 2){
          md.setM2Speed(i);
        }
        delay(20);
      }
    }
  } else {
    if (motor == 1){
      md.setM1Speed(vel_atual);
      Serial.println(vel_atual);
    }
    if (motor == 2){
      md.setM2Speed(vel_atual);
    }
  }
}
