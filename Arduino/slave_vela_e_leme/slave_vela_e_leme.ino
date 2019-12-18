#include "DualVNH5019MotorShield.h" //drive motor
#include "Wire.h"
#include "mavlink.h"
#include <SoftwareSerial.h>

DualVNH5019MotorShield md;
SoftwareSerial ss(5, 3);

//recebe um ângulo de leme (deg)
//lê potenciometro do leme
//mapeia o valor do potenciometro para ângulo do leme (posição atual)
//compara o leme desejado ao atual e encontra um erro
//aplica os ganhos nesse erro
//manda esse sinal para o driver do motor
//envia estado para a pixhawk

//ATUADOR LINEAR
//velocidade positiva -> indo para -90
//velocidade negativa -> indo para 90

//GUINCHO
//velocidade positiva (+400) -> vela FECHA
//velocidade negativa (-400) -> vela ABRE

float Kp_r = 30;
float Ki_r = 0.1;
float I_prior_r = 0;

float Kp_s = 30;
float Ki_s = 1;
float I_prior_s = 0;

float _endtime_r, _starttime_r, _endtime_s, _starttime_s;

int pinoPot_r = A2;
int pinoPot_s = A3;

int range = 40;

int pot_min_r = 723; // leme -90 graus (faz o veleiro virar no sentido horário)
int pot_max_r = 335; // leme 90 graus (faz o veleiro virar no sentido anti-horário)

//valor do pot quando a vela está no max e no min
//int pot_min_s = 500; // leme -90 graus (faz o veleiro virar no sentido horário)
//int pot_max_s = 900; // leme 90 graus (faz o veleiro virar no sentido anti-horário)

int pot_min_s = 150; // leme -90 graus (faz o veleiro virar no sentido horário)
int pot_max_s = 850; // leme 90 graus (faz o veleiro virar no sentido anti-horário)

const int corrente_leme = 1;
const int corrente_vela = 2;
const int posicao_leme = 3;
const int posicao_vela = 4;
const int motor_leme = 5;
const int motor_vela = 6;

void setup() {
  md.init();
  ss.begin(115200);
  _starttime_r = millis();
  _starttime_s = millis();
  Wire.begin(8);                // join i2c bus with address #8
  Wire.onReceive(receiveEvent); // register event
  Serial.begin(9600);
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
    //verifica posição atual do leme
  int theta_r_atual = ler_angulo_atual_r();

    //calcula o erro com o angulo desejado
  int erro = theta_r_desejado - theta_r_atual;
  erro = -erro;

  Serial.println(theta_r_desejado);
  
    //calcula os valores do controlador
  int velocidade_motor = P_r(erro) + I_r(erro);

    //satura valores max e min de pwm
  velocidade_motor = constrain(velocidade_motor, -400, 400);

    //satura para o motor para não ficar consumindo corrente para valores baixos de pwm
  /*int vel_limite = 20;
  if(velocidade_motor < vel_limite && velocidade_motor > 0){
    velocidade_motor = 0;
  }
  if(velocidade_motor > -vel_limite && velocidade_motor < 0){
    velocidade_motor = 0;
  }*/

    //envia comando para o motor
  md.setM1Speed(velocidade_motor); //-400 <-> +400
  //Serial.println(velocidade_motor);  

    //envia os dados para a pixhawk
  send_mavlink(corrente_leme, md.getM1CurrentMilliamps()/1000.);
  send_mavlink(posicao_leme, theta_r_atual);
  //Serial.println(theta_r_atual);
  send_mavlink(motor_leme, velocidade_motor);
}

void vela_controle(int theta_s_desejado){  
    //verifica posição atual da vela
  int theta_s_atual = ler_angulo_atual_s();

    //calcula o erro com o angulo desejado
  int erro = theta_s_desejado - theta_s_atual;
  erro = -erro;

    //encontra valores do controlador
  int velocidade_motor = P_s(erro) + I_s(erro);

    //satura pwm para max e min
  velocidade_motor = constrain(velocidade_motor, -400, 400);

    //satura para o motor para não ficar consumindo corrente para valores baixos de pwm
  int vel_limite = 100;
  if(velocidade_motor < vel_limite && velocidade_motor > 0){
    velocidade_motor = 0;
  }
  if(velocidade_motor > -vel_limite && velocidade_motor < 0){
    velocidade_motor = 0;
  }

    //envia comando do motor
  md.setM2Speed(velocidade_motor); //-400 <-> +400

  //Serial.println(velocidade_motor);
  //Serial.println(md.getM1CurrentMilliamps() + md.getM2CurrentMilliamps());

    //envia mensagem para a pixhawk
  send_mavlink(corrente_vela, md.getM2CurrentMilliamps()/1000.);
  send_mavlink(posicao_vela, theta_s_atual);
  //Serial.println(theta_s_atual);
  send_mavlink(motor_vela, velocidade_motor);
}
