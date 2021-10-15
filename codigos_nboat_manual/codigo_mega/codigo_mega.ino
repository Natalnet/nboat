#include <Wire.h>
double channel[3];

//recebe sinal do rádio
//mapeia para ângulo de leme e vela
//esse é o ângulo desejado
//envia angulo por i2c pros servos

//leme -> aileron -> direito esq-dir -> porta 3
//vela -> trotle -> esquerdo cima-baixo -> porta 2

int RC_sail_low = 1085;
int RC_sail_high = 1885;

int RC_rudder_low = 1093;
int RC_rudder_high = 1885;

int Pixhawk_sail_low = 1000;
int Pixhawk_sail_high = 2000;

int Pixhawk_rudder_low = 993;
int Pixhawk_rudder_high = 1986;

void setup() {
  pinMode(2, INPUT); //vela
  pinMode(3, INPUT); //leme
  //pinMode(13, INPUT); //gear (controle de automático/manual
  Serial.begin(9600);

  //Wire.begin();
}

void loop() {
  //lê sinal do rádio
  channel[0] = pulseIn(2, HIGH); //canal da vela
  channel[1] = pulseIn(3, HIGH); //canal do leme
  //channel[2] = pulseIn(13, HIGH);

  Serial.print("PWM: "); Serial.println(channel[0]);
  Serial.print("LEME: "); Serial.println(channel[1]);
//  Serial.print("GEAR: "); Serial.println(channel[2]);

  int theta_r = map(channel[0],  Pixhawk_rudder_low, Pixhawk_rudder_high, -90, 90); //aileron

  //Serial.print("ANGLE: ");Serial.println(theta_r);
  Serial.println();

  //mapeia de sinal de rádio para ângulo do leme
  //byte theta_r = map(channel, 894, 2088, -90, 90); //aileron
  //byte theta_r_desejado = map(channel, 1093, 1887, 0, 90); //aileron
  
  //envia ângulo desejado pro arduino uno do leme
  //send_wire(theta_r, 8);
  //send_wire(theta_s_desejado, 10);
  
  //Serial.println(channel);
}

void send_wire(byte theta, int address){
  Wire.beginTransmission(address); // transmit to device #8
  Wire.write(theta);        // sends one byte
  Wire.endTransmission();              // stop transmitting
}
