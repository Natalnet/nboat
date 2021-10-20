#include "DualVNH5019MotorShield.h" //drive motor
#include "Wire.h"

DualVNH5019MotorShield md(2, 7, 6, A0, 2, 7, 12, A1);

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
float Kp_s = 15;
float Ki_s = 0.1;
float I_prior_s = 0;

float _endtime_s, _starttime_s;

// pinos dos potenciometros do leme e da vela
int pinoPot_s = A3;

int range = 40;

// RECALIBRAR
//valor do pot quando a vela está no max e no min
int pot_min_s = 850; // leme -90 graus (faz o veleiro virar no sentido horário)
int pot_max_s = 250; // leme 90 graus (faz o veleiro virar no sentido anti-horário)

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
int cont_iic = 0;


// evita uso excessivo dos atuadores
int vel_limite_vela = 100;
int vel_limite_leme = 50;

int cont_limite = 100;
int cont_iic_limite = 20;

// Variáveis do read_radio
int channel[2];

int radio_vela, radio_leme;

int angulo_leme, angulo_vela;
int corrente, posicao, velocidade;

void setup() {
  md.init();
  _starttime_s = millis();
  Serial.begin(9600);
  pinMode(13, INPUT); //vela
  Wire.begin();
}

void loop() {
  // garantir que o código não vai ficar preso no read_radio()
  read_radio();
  vela_controle(constrain(angulo_vela, 0, 90));
  // conta o número de comandos enviados. isso é usado para limitar o envio de mensagens para a pixhawk
  send_data_master(corrente, posicao, velocidade);
  cont++;
  cont_iic++;
}

void vela_controle(int theta_s_desejado){  
  // verifica posição atual da vela
  int theta_s_atual = ler_angulo_atual_s();

  posicao = theta_s_atual;

  // calcula o erro com o angulo desejado
  int erro = theta_s_desejado - theta_s_atual;
  erro = -erro;

  // encontra valores do controlador
  int velocidade_motor = P_s(erro) + I_s(erro);
  //int velocidade_motor = P_s(erro);

  // satura pwm para max e min
  velocidade_motor = constrain(velocidade_motor, -100, 100);

  

  // satura para o motor para não ficar consumindo corrente para valores baixos de pwm
  if(velocidade_motor < vel_limite_vela && velocidade_motor > 0){
    velocidade_motor = 0;
  }
  if(velocidade_motor > -vel_limite_vela && velocidade_motor < 0){
    velocidade_motor = 0;
  }
  

  // envia comando do motor
  md.setM1Speed(velocidade_motor); //-400 <-> +400

  Serial.print("set_point: ");
  Serial.println(angulo_vela);
  Serial.print("angulo_atual: ");
  Serial.println(theta_s_atual);
  Serial.print("velocidade_motor: ");
  Serial.println(velocidade_motor);
  Serial.println();
  
  //Serial.println(md.getM2CurrentMilliamps() + md.getM2CurrentMilliamps());
  /*float corrente_motor = md.getM1CurrentMilliamps()/1000.;

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
  }*/

  delay(10);
}
