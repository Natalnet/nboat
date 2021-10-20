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
float Kp_r = 20;
float Ki_r = 0.2;
float I_prior_r = 0;
float I_max_r = 50;

float Kp_s = 20;
float Ki_s = 0.5;
float I_prior_s = 0;
float I_max_s = 200;

float Kp_m = 1;
float Ki_m = 0;
float I_prior_m = 0;
float I_max_m = 200;

float _endtime_r, _starttime_r, _endtime_s, _starttime_s, _endtime_m, _starttime_m;

// pinos dos potenciometros do leme e da vela
int pinoPot_r = A2;
int pinoPot_s = A3;

int range = 40;

// RECALIBRAR
int pot_min_r = 80; // leme -90 graus (faz o veleiro virar no sentido horário)
int pot_max_r = 640; // leme 90 graus (faz o veleiro virar no sentido anti-horário)

//valor do pot quando a vela está no max e no min
int pot_min_s = 850; // leme -90 graus (faz o veleiro virar no sentido horário)
int pot_max_s = 250; // leme 90 graus (faz o veleiro virar no sentido anti-horário)

// mapeamento das mensagens mavlink
const int corrente_leme = 1;
const int corrente_vela = 2;
const int posicao_leme = 3;
const int posicao_vela = 4;
const int motor_leme_com = 5;
const int motor_vela_com = 6;

// mapeamento dos motores
const int motor_leme = 1;
const int motor_vela = 2;

float _corrente_vela_ant = 0;
float _posicao_vela_ant = 0;
float _motor_vela_ant = 0;

float _corrente_leme_ant = 0;
float _posicao_leme_ant = 0;
float _motor_leme_ant = 0;

int cont = 0;
int cont_limite = 100;

// evita uso excessivo dos atuadores. corta comandos menos que os limites.
int vel_limite_vela = 50;
int vel_limite_leme = 50;

// Variáveis do read_radio
int channel[2];

int radio_vela, radio_leme;

int angulo_leme, angulo_vela;

int vel_acc;
int vel_incremento = 80;

void setup() {
  md.init();
  ss.begin(115200);
  _starttime_r = millis();
  _starttime_s = millis();
  _starttime_m = millis();
  Serial.begin(9600);
  pinMode(11, INPUT); //leme
  pinMode(13, INPUT); //vela
}

void loop() {
  // garantir que o código não vai ficar preso no read_radio()
  read_radio();
  leme_controle(constrain(angulo_leme, -90, 90));
  vela_controle(constrain(angulo_vela, 0, 90));
  // conta o número de comandos enviados. isso é usado para limitar o envio de mensagens para a pixhawk
  cont++;
  delay(100);
}

void leme_controle(int theta_r_desejado){  
  // verifica posição atual do leme
  int theta_r_atual = ler_angulo_atual_r();

  // calcula o erro com o angulo desejado
  int erro = theta_r_desejado - theta_r_atual;
  //erro = -erro
  
  // calcula os valores PID
  int velocidade_motor = P_r(erro) + I_r(erro);

  // satura valores max e min de pwm
  velocidade_motor = constrain(velocidade_motor, -400, 400);

  // corta velocidades baixas (evita uso desnecessário)
  velocidade_motor = satura_motor(velocidade_motor, vel_limite_leme);

  // envia comando para o motor
  //set_speed_suave(velocidade_motor, _motor_leme_ant, motor_leme);
  md.setM1Speed(velocidade_motor); //-400 <-> +400

  // mede a corrente
  float corrente_motor = get_corrente(motor_leme);

  // manda sinais para a pixhawk
  com_pixhawk_leme(corrente_motor, theta_r_atual, velocidade_motor);

  // debuga
  debug_leme(theta_r_atual, angulo_leme, velocidade_motor, corrente_motor);

  //delay(10);
}

void vela_controle(int theta_s_desejado){  
  // verifica posição atual da vela
  int theta_s_atual = ler_angulo_atual_s();

  // calcula o erro com o angulo desejado
  int erro = theta_s_desejado - theta_s_atual;
  erro = -erro;

  erro = constrain(erro, -100, 100);

  // encontra valores do controlador
  int velocidade_motor = P_s(erro) + I_s(erro);
  //int velocidade_motor = P_s(erro);

  // satura pwm para max e min
  velocidade_motor = constrain(velocidade_motor, -400, 400);

  velocidade_motor = satura_motor(velocidade_motor, vel_limite_vela);

  // envia comando do motor
  // set_speed_suave(velocidade_motor, _motor_vela_ant, motor_vela);
  // md.setM2Speed(velocidade_motor); //-400 <-> +400
  set_speed_incremental(velocidade_motor);
  
  //set_speed_suave(velocidade_motor); //-400 <-> +400

  _motor_vela_ant = velocidade_motor;
   
  float corrente_motor = get_corrente(motor_vela);

  com_pixhawk_vela(corrente_motor, theta_s_atual, velocidade_motor);

  debug_vela(theta_s_atual, angulo_vela, velocidade_motor, corrente_motor);
  
  //delay(10);
}
