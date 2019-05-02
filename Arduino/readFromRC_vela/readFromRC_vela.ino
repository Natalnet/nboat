#include "Wire.h"
#include "DualVNH5019MotorShield.h" //drive motor
DualVNH5019MotorShield md(2, 7, 6, A0, 2, 7, 12, A1);

//recebe um ângulo do leme
//lê potenciometro da vela
//mapeia esse valor para ângulo da vela (posição atual)
//compara a vela desejada à atual e encontra um erro
//aplica um ganho nesse erro
//aplica esse sinal como velocidade do motor

float Kp = 2;
float Ki = 0.005;
float I_prior = 0;

float _endtime, _starttime;

int pinoPot = A3;

byte angulo_recebido;

void setup()
{
  md.init();
  Serial.begin(9600);
  _starttime = millis();
  Wire.begin(10);                // join i2c bus with address #8
  Wire.onReceive(receiveEvent); // register event
}

void loop() {
  vela_controle(angulo_recebido);
}

void vela_controle(byte theta_s_desejado){
  //verifica posição atual
  int theta_s_atual = ler_angulo_atual();
  
  int erro = theta_s_desejado - theta_s_atual;
  
  //comando do motor
  int velocidade_motor = P(erro) + I(erro);

  constrain(velocidade_motor, -400, 400);
  md.setM1Speed(velocidade_motor); //-400 <-> +400
  
//  if(erro > 20){
//    md.setM1Speed(-200);
//  } else if(erro < -20){
//    md.setM1Speed(200);
//  } else if ((erro >= 0 && erro <= 30) || (erro <= 0 && erro >= -30)){
//    md.setM1Speed(0);
//  } else {
//    md.setM1Speed(0);
//  }
}

int ler_angulo_atual(){
  int potenciometro = analogRead(pinoPot);
  
  //medir pot guincho
  return map(potenciometro, 0, 100, 0, 90);
}

// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent() {
  byte x;
  if (Wire.available()) { // loop through all but the last
    x = Wire.read();    // receive byte as an integer
  }
  vela_controle(x);
}

float P(float currentError)
{
  return Kp * currentError;
}

float I(float currentError)
{
  _endtime = millis();
  float _cycleTime = (_endtime - _starttime)/1000;
  _starttime = millis();
  if ((I_prior > 0 && currentError < 0) || (I_prior < 0 && currentError > 0))
  {
    I_prior = I_prior + Ki * currentError * 1 * _cycleTime;
  }
  else
  {
    I_prior = I_prior + Ki * currentError * _cycleTime;
  }
  if (I_prior > 30){
    I_prior = 30;
  }
  if (I_prior < -30){
    I_prior = -30;
  }
  return I_prior;
}
