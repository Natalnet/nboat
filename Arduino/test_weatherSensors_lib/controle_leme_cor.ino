#include <Wire.h>
#include "Adafruit_TCS34725.h" //sensor de cor
#include "DualVNH5019MotorShield.h" //drive motor

DualVNH5019MotorShield md;
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);

float lux, r_red, r_green, r_blue;
int   cor, req_cor; 
int espera = 1;

void setup() {
     //Iniciando Serial
     Serial.begin(9600);
     //Testando Sensor de Cor
     // Serial.println("Testando integridade do sistema");
     if (tcs.begin()) {
      // Serial.println("Sensor encontrado");
     } else {
      // Serial.println("Sensor nao encontrado ... verifique sua conexoes");
      while (1);
     }
     //Iniciando Motor Shield
     md.init();
     //Define o pino de botão com resistor de elevação
     pinMode(5,  INPUT_PULLUP);
}

void loop() {
  char tecla;
  if (espera == 1) {
   tecla = Serial.read();
   if (tecla == 'c') {
   centro();
   }
   if (tecla == '1') {
   req_cor = 1;
   move_leme();
   }
   if (tecla == '2') {
   req_cor = 2;
   move_leme();
   }
   if (tecla == '3') {
   req_cor = 3;
   move_leme();
   }
   if (tecla == '4') {
   req_cor = 4;
   move_leme();
   }
   if (tecla == '5') {
   req_cor = 5;
   move_leme();
   }
   if (tecla == '6') {
   req_cor = 6;
   move_leme();
   }
   if (tecla == '7') {
   req_cor = 7;
   move_leme();
   }
   mostra_rgb();
   delay(1000);
  }
}




  

