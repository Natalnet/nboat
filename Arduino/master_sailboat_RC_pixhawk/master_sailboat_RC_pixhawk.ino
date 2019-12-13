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

int Pixhawk_sail_low = 993;
int Pixhawk_sail_high = 1986;

int Pixhawk_rudder_low = 993;
int Pixhawk_rudder_high = 1986;

void setup() {
  pinMode(2, INPUT); //vela
  pinMode(3, INPUT); //leme
  //pinMode(13, INPUT); //gear (controle de automático/manual
  //Serial.begin(9600);

  //delay(5000);

  Wire.begin();
}

void loop() {
  //lê sinal do rádio
  channel[0] = pulseIn(2, HIGH); //canal da vela
  channel[1] = pulseIn(3, HIGH); //canal do leme
  //channel[2] = pulseIn(13, HIGH);

  //Serial.print("VELA: "); Serial.println(channel[0]);
  //Serial.print("LEME: "); Serial.println(channel[1]);
  //Serial.print("GEAR: "); Serial.println(channel[2]);
  //Serial.println();

  //delay(500);

  //mapeia de sinal de rádio para ângulo do leme
  int theta_s = map(channel[0], Pixhawk_sail_low, Pixhawk_sail_high, 0, 90); //aileron
  int theta_r = map(channel[1],  Pixhawk_rudder_low, Pixhawk_rudder_high, -90, 90); //aileron
  
  //envia ângulo desejado pro arduino uno do leme
  //send_wire(map(theta_r, -90, 90, 0, 179), 8); //mapeamento pra poder enviar byte
  //send_wire(theta_s, 8);

  //theta_r += 95;

  //saturadores
  if(theta_s > 90){
    theta_s = 90;
  }
  if(theta_s < 0){
    theta_s = 0;
  }

  if(theta_r > 90){
    theta_r = 90;
  }
  if(theta_r < -90){
    theta_r = -90;
  }

  Wire.beginTransmission(8);           // transmit to device #8
  Wire.write(map(theta_r, -90, 90, 0, 179));   // sends one byte
  Wire.write(theta_s);   // sends one byte
  Wire.endTransmission();                    // stop transmitting
  
  //Serial.print("LEME: "); Serial.println(theta_r);
  //Serial.print("VELA: "); Serial.println(theta_s);
  //Serial.println();
  //delay(500);
  //Serial.println(channel[1]);
}

void send_wire(int theta, int address){
  Wire.beginTransmission(address);           // transmit to device #8
  Wire.write(theta);   // sends one byte
  Wire.endTransmission();                    // stop transmitting
}
