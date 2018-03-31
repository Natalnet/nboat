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
     Serial.println("Testando integridade do sistema");
     if (tcs.begin()) {
      Serial.println("Sensor encontrado");
     } else {
      Serial.println("Sensor nao encontrado ... verifique sua conexoes");
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
   delay(1000);
  }
}

void mostra_rgb() {
  uint16_t clear, red, green, blue;
  tcs.setInterrupt(false);      // liga LED
  delay(60);  // leva 60ms para ler
  tcs.getRawData(&red, &green, &blue, &clear);
  tcs.setInterrupt(true);  // desliga LED

  Serial.print("C: ");
  Serial.println(lux);
  Serial.print("R: ");
  Serial.println(red);
  Serial.print("G: ");
  Serial.println(green);
  Serial.print("B: ");
  Serial.println(blue);
}

void detecta_cor() {
  uint16_t clear, red, green, blue;
  tcs.setInterrupt(false);      // liga LED
  delay(60);  // leva 60ms para ler
  tcs.getRawData(&red, &green, &blue, &clear);
  tcs.setInterrupt(true);  // desliga LED

  lux = clear;
  r_red = lux / red;
  r_green = lux / green;
  r_blue = lux / blue;

  if(r_red >= 5){
    cor = 1; //azul
    Serial.println("azul");
  } else if((r_blue >= 4.9) && (r_green <= 3.1)){
    cor = 2; //amarelo
    Serial.println("amarelo");
  } else if((lux <= 2200) && (r_blue <= 2.7) && (r_green >= 3.0)){
    cor = 3; //roxo
    Serial.println("roxo");
  } else if((lux <= 1900) && (r_blue >=2.8 && r_blue <= 3.3)){
    cor = 4; //preto
    Serial.println("preto");
  } else if((r_blue >= 4.4) && (r_green > 3.1 && r_green < 4)){
    cor = 5; //laranja
    Serial.println("laranja");
  } else if((r_green <=2.55) && (r_red >= 3.6 && r_red <= 4.3)){
    cor = 6; //verde
    Serial.println("verde");
  } else if(r_green >= 5){
    cor = 7; //vermelho
    Serial.println("vermelho");
  } else {
    Serial.println("nao identificada");
  }  
  
}

void centro() {
  Serial.println("Iniciando verificação de centro");
  md.setM1Speed(0);
  delay(500);
  cor = 0;
  detecta_cor();
  if (cor != 4) {
   while (cor < 4) {
     md.setM1Speed(200);
     detecta_cor();
     Serial.println(cor);
   }
  }   
  md.setM1Speed(0);
  if (cor != 4) {
   while (cor > 4) {
     md.setM1Speed(-200);
     detecta_cor();
     Serial.println(cor);
   }
  } 
  md.setM1Speed(0);
  Serial.println("Leme centralizado com sucesso");
}

void varredura_cores() {
  Serial.println("Iniciando varredura");
  md.setM1Speed(0);
  delay(1000);
  Serial.print("A cor atual é :");
  detecta_cor();
  Serial.println(cor);
  delay(1000);
  while (cor != 7) {
     md.setM1Speed(400);
     detecta_cor();
     Serial.println(cor);
   }
  md.setM1Speed(0);
  delay(500);
   Serial.println("Invertendo sentido do motor");
   delay(500);
   Serial.println("<<<--- Sentido");
   delay(1000);
   while (cor != 1) {
     md.setM1Speed(-400);
     detecta_cor();
     Serial.println(cor);
   }
  md.setM1Speed(0);
  delay(500);
  Serial.println("varredura completa");
}  
  
void move_leme() {
  espera = 0;
  md.setM1Speed(0);
  detecta_cor();
  while (cor < req_cor) {
    if (req_cor - cor <= 1) { 
    md.setM1Speed(200); } 
    else { 
    md.setM1Speed(400); }
    detecta_cor();
    Serial.println(cor);
  }
  while (cor > req_cor) {
    if (cor - req_cor <= 1) { 
    md.setM1Speed(-200); } 
    else { 
    md.setM1Speed(-400); }
    detecta_cor();
    Serial.println(cor);
  }
  //será q ele sai daqui?
  while (Serial.available() > 0) {
    char t = Serial.read();
  }
  delay(100);
  espera = 1;
  md.setM1Speed(0);
}
