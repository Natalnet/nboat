#include <Wire.h>
#include <mavlink.h>
double channel[3];

//recebe sinal do rádio
//mapeia para ângulo de leme e vela
//esse é o ângulo desejado
//envia angulo por i2c pros servos

//leme -> aileron -> direito esq-dir -> porta 3
//vela -> trotle -> esquerdo cima-baixo -> porta 2


void setup() {
  pinMode(52, INPUT); //vela
  //pinMode(3, INPUT); //leme
  //pinMode(13, INPUT); //gear (controle de automático/manual
  Serial.begin(9600);

  //delay(5000);

  Wire.begin();
}

void loop() {
  //lê sinal do rádio
  channel[0] = pulseIn(52, HIGH); //canal da vela
  //channel[1] = pulseIn(3, HIGH); //canal do leme
  //channel[2] = pulseIn(13, HIGH);

  Serial.print("VELA: "); Serial.println(channel[0]);
  //Serial.print("LEME: "); Serial.println(channel[1]);
  //Serial.print("GEAR: "); Serial.println(channel[2]);
  //Serial.println();}
}
