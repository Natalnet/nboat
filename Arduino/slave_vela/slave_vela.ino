#include "DualVNH5019MotorShield.h" //drive motor
#include "Wire.h"
DualVNH5019MotorShield md(2, 7, 6, A0, 2, 7, 12, A1);

//recebe um ângulo de vela (deg)
//lê potenciometro da vela
    //medir pot da vela (ver ler_angulo_atual())
//mapeia o valor do potenciometro para ângulo da vela (posição atual) -OK
//compara a vela desejada à atual e encontra um erro -OK
//aplica um ganho nesse erro -OK
//manda esse sinal para o driver
    //testar driver guincho


//GUINCHO
//velocidade positiva (+400) -> vela (?) (abre ou fecha?) FECHA
//velocidade negativa (-400) -> vela (?) (abre ou fecha?) ABRE

float Kp = 3;
float Ki = 0;
float I_prior = 0;

float _endtime, _starttime;

int pinoPot = A3;
byte angulo_recebido;

int range = 5;

//valor do pot quando a vela está no max e no min
int pot_min = 495; // vela 0 graus (fechada)
int pot_max = 125; // vela 90 graus (aberta perpendicular)

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
  vela_controle(constrain(x, 0, 90));
}


void vela_controle(int theta_s_desejado){  
  //verifica posição atual
  int theta_s_atual = ler_angulo_atual();

  //encontra erro
  int erro = theta_s_desejado - theta_s_atual;
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

  velocidade_motor = constrain(velocidade_motor, -400, 400);
  md.setM1Speed(velocidade_motor); //-400 <-> +400
  //Serial.println(velocidade_motor);
}


int ler_angulo_atual(){
  int potenciometro = analogRead(pinoPot);
  
  //medir pot guincho
  return map(potenciometro, pot_min, pot_max, 0, 90);
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
    I_prior = I_prior + Ki * currentError * _cycleTime;
  }
  else
  {
    I_prior = I_prior + Ki * currentError * _cycleTime;
  }
  I_prior = constrain(I_prior, -200, 200);
  return I_prior;
}
