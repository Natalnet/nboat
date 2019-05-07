#include "DualVNH5019MotorShield.h" //drive motor
#include "Wire.h"
DualVNH5019MotorShield md;

//recebe um ângulo de leme (deg)
//lê potenciometro do leme
//mapeia o valor do potenciometro para ângulo do leme (posição atual)
//compara o leme desejado ao atual e encontra um erro
//aplica um ganho nesse erro
//manda esse sinal para o driver do motor

//ATUADOR LINEAR
//velocidade positiva -> indo para -90
//velocidade negativa -> indo para 90

float Kp = 10;
float Ki = 0.5;
float I_prior = 0;

float _endtime, _starttime;

int pinoPot = A2;
byte angulo_recebido;

int range = 40;

void setup() {
  md.init();
  Serial.begin(9600);
  _starttime = millis();
  Wire.begin(8);                // join i2c bus with address #8
  Wire.onReceive(receiveEvent); // register event
}


void loop() {
}


void leme_controle(int theta_r_desejado){  
  //verifica posição atual
  int theta_r_atual = ler_angulo_atual();
  
  int erro = theta_r_desejado - theta_r_atual;
  erro = -erro;
  
  //comando do motor
  int velocidade_motor = P(erro) + I(erro);

  /*if (erro > range) {
  velocidade_motor = 400;
  } else if (erro < range){
  velocidade_motor = -400;
  } else {
  velocidade_motor = 0;
  }*/
  Serial.println(erro);

  velocidade_motor = constrain(velocidade_motor, -400, 400);
  md.setM1Speed(velocidade_motor); //-400 <-> +400
  //Serial.println(velocidade_motor);
}


int ler_angulo_atual(){
  int potenciometro = analogRead(pinoPot);

  //Serial.println(map(potenciometro, 495, 125, -90, 90));
  
  //medir pot atuador linear
  return map(potenciometro, 495, 125, -90, 90);
}

// function that runs whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent() {  
  int x;
  if (Wire.available()) { // loop through all but the last
    x = Wire.read();    // receive byte as an integer
  }
  x = map(x, 0, 179, -90, 90);
  //Serial.println(x);
  leme_controle(x);
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
  I_prior = constrain(I_prior, -200, 200);
  return I_prior;
}
