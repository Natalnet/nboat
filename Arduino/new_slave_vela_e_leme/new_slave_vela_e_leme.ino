#include "DualVNH5019MotorShield.h" //drive motor
#include "Wire.h"
#include "mavlink.h"
#include <SoftwareSerial.h>

DualVNH5019MotorShield md;
SoftwareSerial ss(5, 3);

/*****************************
 
- recebe sinal pwm da pixhawk
- mapeia para ângulo de atuadores
- lê potenciometros
- mapeia o valor do potenciometro para ângulo do leme (saber a posição atual)
- compara o leme desejado ao atual e encontra um erro
- aplica os ganhos nesse erro
- manda esse sinal para o driver do motor
- envia estado para a pixhawk comunicação serial

*****************************/

//ATUADOR LINEAR
//velocidade positiva -> indo para -90
//velocidade negativa -> indo para 90

//GUINCHO
//velocidade positiva (+400) -> vela FECHA
//velocidade negativa (-400) -> vela ABRE

// variáveis PID
float Kp_r = 30;
float Ki_r = 0.1;
float I_prior_r = 0;

float Kp_s = 30;
float Ki_s = 1;
float I_prior_s = 0;

float _endtime_r, _starttime_r, _endtime_s, _starttime_s;

// pinos dos potenciometros do leme e da vela
int pinoPot_r = A2;
int pinoPot_s = A3;

int range = 40;

// RECALIBRAR
int pot_min_r = 640; // leme -90 graus (faz o veleiro virar no sentido horário)
int pot_max_r = 80; // leme 90 graus (faz o veleiro virar no sentido anti-horário)

//valor do pot quando a vela está no max e no min
int pot_min_s = 150; // leme -90 graus (faz o veleiro virar no sentido horário)
int pot_max_s = 850; // leme 90 graus (faz o veleiro virar no sentido anti-horário)

// mapeamento das mensagens mavlink
const int corrente_leme = 1;
const int corrente_vela = 2;
const int posicao_leme = 3;
const int posicao_vela = 4;
const int motor_leme = 5;
const int motor_vela = 6;

float _corrente_vela_ant = 0;
float _posicao_vela_ant = 0;
float _motor_vela_ant = 0;

float _corrente_leme_ant = 0;
float _posicao_leme_ant = 0;
float _motor_leme_ant = 0;

int cont = 0;

// evita uso excessivo dos atuadores
int vel_limite_vela = 100;
int vel_limite_leme = 50;

int cont_limite = 100;

// Variáveis do read_radio
double channel[2];

int angulo_leme, angulo_vela;

void setup() {
  md.init();
  ss.begin(115200);
  _starttime_r = millis();
  _starttime_s = millis();
  Serial.begin(9600);
  pinMode(11, INPUT); //vela
  //pinMode(13, INPUT); //leme (controle de automático/manual
}

void loop() {
  // garantir que o código não vai ficar preso no read_radio()
  read_radio();
  leme_controle(constrain(angulo_leme, -90, 90));
  //vela_controle(constrain(angulo_vela, 0, 90));
  // conta o número de comandos enviados. isso é usado para limitar o envio de mensagens para a pixhawk
  cont++;  
}

void leme_controle(int theta_r_desejado){  
  // verifica posição atual do leme
  int theta_r_atual = ler_angulo_atual_r();

  // calcula o erro com o angulo desejado
  int erro = theta_r_desejado - theta_r_atual;
  erro = -erro;
  
  // calcula os valores do controlador
  int velocidade_motor = P_r(erro) + I_r(erro);

  // satura valores max e min de pwm
  velocidade_motor = constrain(velocidade_motor, -400, 400);

  // satura para o motor para não ficar consumindo corrente para valores baixos de pwm
  if(velocidade_motor < vel_limite_leme && velocidade_motor > 0){
    velocidade_motor = 0;
  }
  if(velocidade_motor > -vel_limite_leme && velocidade_motor < 0){
    velocidade_motor = 0;
  }

  // envia comando para o motor
  md.setM1Speed(velocidade_motor); //-400 <-> +400
  
  //Serial.println(velocidade_motor);

  float corrente_motor = md.getM1CurrentMilliamps()/1000.;

  bool aux = (corrente_motor != _corrente_leme_ant || theta_r_atual != _posicao_leme_ant || velocidade_motor != _motor_leme_ant);

  // envia os dados para a pixhawk quando dados mudam
  if(cont % cont_limite == 0 && aux){
    send_mavlink(corrente_leme, corrente_motor);
    send_mavlink(posicao_leme, theta_r_atual);
    send_mavlink(motor_leme, velocidade_motor);

    _corrente_leme_ant = corrente_motor;
    _posicao_leme_ant = theta_r_atual;
    _motor_leme_ant = velocidade_motor;
    cont = 0;
  }
}

void vela_controle(int theta_s_desejado){  
  // verifica posição atual da vela
  int theta_s_atual = ler_angulo_atual_s();

  // calcula o erro com o angulo desejado
  int erro = theta_s_desejado - theta_s_atual;
  erro = -erro;

  // encontra valores do controlador
  int velocidade_motor = P_s(erro) + I_s(erro);

  // satura pwm para max e min
  velocidade_motor = constrain(velocidade_motor, -400, 400);

  // satura para o motor para não ficar consumindo corrente para valores baixos de pwm
  if(velocidade_motor < vel_limite_vela && velocidade_motor > 0){
    velocidade_motor = 0;
  }
  if(velocidade_motor > -vel_limite_vela && velocidade_motor < 0){
    velocidade_motor = 0;
  }

  // envia comando do motor
  md.setM2Speed(velocidade_motor); //-400 <-> +400

  //Serial.println(velocidade_motor);
  //Serial.println(md.getM1CurrentMilliamps() + md.getM2CurrentMilliamps());
  float corrente_motor = md.getM2CurrentMilliamps()/1000.;

  bool aux = (corrente_motor != _corrente_vela_ant || theta_s_atual != _posicao_vela_ant || velocidade_motor != _motor_vela_ant);
  
  // envia mensagem para a pixhawk
  if(cont % cont_limite == 0 && aux){
    send_mavlink(corrente_vela, corrente_motor);
    send_mavlink(posicao_vela, theta_s_atual);
    send_mavlink(motor_vela, velocidade_motor);

    _corrente_vela_ant = corrente_motor;
    _posicao_vela_ant = theta_s_atual;
    _motor_vela_ant = velocidade_motor;

    cont = 0;
  }
}
