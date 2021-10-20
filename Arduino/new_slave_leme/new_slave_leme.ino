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
float Ki_r = 0.001;
float I_prior_r = 0;

float _endtime_r, _starttime_r;

// pinos dos potenciometros do leme e da vela
int pinoPot_r = A2;

int range = 40;

// RECALIBRAR
int pot_min_r = 80; // leme -90 graus (faz o veleiro virar no sentido horário)
int pot_max_r = 640; // leme 90 graus (faz o veleiro virar no sentido anti-horário)

// mapeamento das mensagens mavlink
const int corrente_leme = 1;
const int corrente_vela = 2;
const int posicao_leme = 3;
const int posicao_vela = 4;
const int motor_leme = 5;
const int motor_vela = 6;

float corrente_vela_send, posicao_vela_send, velocidade_vela_send;

float _corrente_vela_ant = 0;
float _posicao_vela_ant = 0;
float _motor_vela_ant = 0;

float _corrente_leme_ant = 0;
float _posicao_leme_ant = 0;
float _motor_leme_ant = 0;

int cont = 0;

int cont_limite = 100;

// Variáveis do read_radio
int channel[2];

int radio_vela, radio_leme;

int angulo_leme, angulo_vela;

int y1, y2, y3;

int vel_limite_leme = 50;

void setup() {
  md.init();
  ss.begin(115200);
  _starttime_r = millis();
  Serial.begin(9600);
  pinMode(11, INPUT); //leme
  Wire.begin(10);
  Wire.onReceive(receiveEvent);
}

void loop() {
  // garantir que o código não vai ficar preso no read_radio()
  read_radio();
  leme_controle(constrain(angulo_leme, -90, 90));
  cont++;
}

void leme_controle(int theta_r_desejado){  
  // verifica posição atual do leme
  int theta_r_atual = ler_angulo_atual_r();

  // calcula o erro com o angulo desejado
  int erro = theta_r_desejado - theta_r_atual;
  //erro = -erro;
  
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
  //md.setM2Speed(velocidade_motor); //-400 <-> +400

  //positivo aumenta, negativo diminui

  float corrente_motor = md.getM1CurrentMilliamps()/1000.;
  /*
  Serial.print("angulo_atual: ");
  Serial.println(theta_r_atual);
  Serial.print("set_point: ");
  Serial.println(angulo_leme);
  Serial.print("velocidade_motor: ");
  Serial.println(velocidade_motor);
  Serial.print("corrente motor: ");
  Serial.println(corrente_motor);
  Serial.println();
  */

  bool aux = (corrente_motor != _corrente_leme_ant || theta_r_atual != _posicao_leme_ant || velocidade_motor != _motor_leme_ant);

  // envia os dados para a pixhawk quando dados mudam
  if(cont % cont_limite == 0 && aux){
    send_mavlink(corrente_leme, corrente_motor);
    send_mavlink(posicao_leme, theta_r_atual);
    send_mavlink(motor_leme, velocidade_motor);

    send_mavlink(corrente_vela, corrente_vela_send);
    send_mavlink(posicao_vela, posicao_vela_send);
    send_mavlink(motor_vela, velocidade_vela_send);

    _corrente_leme_ant = corrente_motor;
    _posicao_leme_ant = theta_r_atual;
    _motor_leme_ant = velocidade_motor;
    cont = 0;
  }

  delay(10);
}
