//Programa: Controle de motor brushless EMAX CF2822
//Autor : Arduino e Cia

#include <Servo.h>

Servo ServoMotor;

//Pino do potenciometro
int pino_pot = A5;
//Pino de controle do motor
int pino_motor = 6;
int valor;

void setup()
{
  //Serial.begin(9600);
  ServoMotor.attach(pino_motor);
}

void loop()
{
  //Envia o valor para o motor
  valor = 105;
  ServoMotor.write(valor);
  //delay(2000);
  //delay(2000);
  //ServoMotor.write(0);
  //delay(2000);
}
