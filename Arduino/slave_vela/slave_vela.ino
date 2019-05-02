#include "DualVNH5019MotorShield.h" //drive motor
#include "Wire.h"
DualVNH5019MotorShield md(2, 7, 6, A0, 2, 7, 12, A1);

//recebe um ângulo de vela (deg)
//lê potenciometro da vela
    //medir pot da vela
//mapeia o valor do potenciometro para ângulo da vela (posição atual)
//compara a vela desejada à atual e encontra um erro
//aplica um ganho nesse erro
//manda esse sinal para o driver
    //testar driver guincho


//GUINCHO
//velocidade positiva -> indo para 
//velocidade negativa -> indo para 

float Kp = 3;
float Ki = 0;
float I_prior = 0;

float _endtime, _starttime;

int pinoPot = A3;
byte angulo_recebido;

int range = 5;

void setup() {
  md.init();
  Serial.begin(9600);
  _starttime = millis();
  Wire.begin(10);                // join i2c bus with address #10
  Wire.onReceive(receiveEvent); // register event
}

void loop() {
}

// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent() {  
  int x;
  if (Wire.available()) { // loop through all but the last
    x = Wire.read();      // receive byte as an integer
  }
  vela_controle(x);
}

void vela_controle(int theta_r_desejado){  
  //verifica posição atual
  int theta_r_atual = ler_angulo_atual();
  
  int erro = theta_r_desejado - theta_r_atual;
  erro = -erro;
  
  //comando do motor
  int velocidade_motor = P(erro) + I(erro);

  if (erro > range) {
  velocidade_motor = 400;
  } else if (erro < range){
  velocidade_motor = -400;
  } else {
  velocidade_motor = 0;
  }

  velocidade_motor = constrain(velocidade_motor, -400, 400);
  md.setM1Speed(velocidade_motor); //-400 <-> +400
  //Serial.println(velocidade_motor);
}

int ler_angulo_atual(){
  int potenciometro = analogRead(pinoPot);
  
  //medir pot guincho
  return map(potenciometro, 495, 125, 0, 90);
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
