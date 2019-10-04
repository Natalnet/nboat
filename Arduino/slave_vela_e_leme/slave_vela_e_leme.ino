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

//GUINCHO
//velocidade positiva (+400) -> vela FECHA
//velocidade negativa (-400) -> vela ABRE

float Kp_r = 30;
float Ki_r = 0.05;
float I_prior_r = 0;

float Kp_s = 10;
float Ki_s = 0.1;
float I_prior_s = 0;

float _endtime_r, _starttime_r, _endtime_s, _starttime_s;

int pinoPot_r = A2;
int pinoPot_s = A3;

int range = 40;

int pot_min_r = 660; // leme -90 graus (faz o veleiro virar no sentido horário)
int pot_max_r = 360; // leme 90 graus (faz o veleiro virar no sentido anti-horário)

//valor do pot quando a vela está no max e no min
int pot_min_s = 500; // leme -90 graus (faz o veleiro virar no sentido horário)
int pot_max_s = 900; // leme 90 graus (faz o veleiro virar no sentido anti-horário)

void setup() {
  md.init();
  Serial.begin(9600);
  _starttime_r = millis();
  _starttime_s = millis();
  Wire.begin(8);                // join i2c bus with address #8
  Wire.onReceive(receiveEvent); // register event
}


void loop() {
}


// function that runs whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent() {  
  int angle_r;
  int angle_s;
  if (Wire.available()) { // loop through all but the last
    angle_r = Wire.read();    // receive byte as an integer
    angle_s = Wire.read();    // receive byte as an integer
  }
  //angle_r = map(angle_r, 0, 179, -90, 90);
  angle_r -= 95;
  //Serial.println(angle_r);
  leme_controle(constrain(angle_r, -90, 90));
  vela_controle(constrain(angle_s, 0, 90));
  //Serial.println(angle_s);
  //Serial.println();
  //delay(1000);
}


void leme_controle(int theta_r_desejado){  
  //verifica posição atual
  int theta_r_atual = ler_angulo_atual_r();
  
  int erro = theta_r_desejado - theta_r_atual;
  erro = -erro;
  
  //comando do motor
  int velocidade_motor = P_r(erro) + I_r(erro);

  /*if (erro > range) {
  velocidade_motor = 400;
  } else if (erro < range){
  velocidade_motor = -400;
  } else {
  velocidade_motor = 0;
  }*/
  
  //Serial.println(erro);

  velocidade_motor = constrain(velocidade_motor, -400, 400);
  md.setM1Speed(velocidade_motor); //-400 <-> +400
  //Serial.println(velocidade_motor);
}

int ler_angulo_atual_r(){
  int pot_r = analogRead(pinoPot_r);

  //Serial.println(pot_r);

  //Serial.println(map(pot_r, pot_min_r, pot_max_r, -90, 90));
  
  //medir pot atuador linear
  return map(pot_r, pot_min_r, pot_max_r, -90, 90);
}



void vela_controle(int theta_s_desejado){  
  //verifica posição atual
  int theta_s_atual = ler_angulo_atual_s();

  //encontra erro
  int erro = theta_s_desejado - theta_s_atual;
  erro = -erro;
  
  //comando do motor
  int velocidade_motor = P_s(erro) + I_s(erro);

  /*if (erro > range) {
  velocidade_motor = 400;
  } else if (erro < range){
  velocidade_motor = -400;
  } else {
  velocidade_motor = 0;
  }*/

  velocidade_motor = constrain(velocidade_motor, -400, 400);
  md.setM2Speed(velocidade_motor); //-400 <-> +400
  //Serial.println(velocidade_motor);
}

int ler_angulo_atual_s(){
  int pot_s = analogRead(pinoPot_s);
  
  //medir pot guincho
  return map(pot_s, pot_min_s, pot_max_s, 0, 90);
}


float P_r(float currentError)
{
  return Kp_r * currentError;
}

float I_r(float currentError)
{
  _endtime_r = millis();
  float _cycleTime = (_endtime_r - _starttime_r)/1000;
  _starttime_r = millis();
  if ((I_prior_r > 0 && currentError < 0) || (I_prior_r < 0 && currentError > 0))
  {
    I_prior_r = I_prior_r + Ki_r * currentError * _cycleTime;
  }
  else
  {
    I_prior_r = I_prior_r + Ki_r * currentError * _cycleTime;
  }
  I_prior_r = constrain(I_prior_r, -200, 200);
  return I_prior_r;
}

float P_s(float currentError)
{
  return Kp_s * currentError;
}

float I_s(float currentError)
{
  _endtime_s = millis();
  float _cycleTime = (_endtime_s - _starttime_s)/1000;
  _starttime_s = millis();
  if ((I_prior_s > 0 && currentError < 0) || (I_prior_s < 0 && currentError > 0))
  {
    I_prior_s = I_prior_s + Ki_s * currentError * _cycleTime;
  }
  else
  {
    I_prior_s = I_prior_s + Ki_s * currentError * _cycleTime;
  }
  I_prior_s = constrain(I_prior_s, -200, 200);
  return I_prior_s;
}
