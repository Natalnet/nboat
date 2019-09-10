#include <Wire.h>
#include <Servo.h>
double channel[3];

//pega sinal do rádio
//transforma em sinal de servo
//manda pro servo

Servo sail_servo;
Servo rudder_servo;

int sail_max, sail_min;
int rudder_max, rudder_min;

void setup() {
  pinMode(2, INPUT); //vela
  pinMode(3, INPUT); //leme
  pinMode(4, INPUT); //gear (controle de automático/manual

  sail_max = 45;
  sail_min = 0;
  rudder_max = 20;
  rudder_min = 60;
  
  Serial.begin(9600);

  sail_servo.attach(8);  //vela
  rudder_servo.attach(9); //leme
  
  Wire.begin();

}

void loop() {
  channel[0] = pulseIn(2, HIGH); //canal da vela
  channel[1] = pulseIn(3, HIGH); //canal do leme
  //channel[2] = pulseIn(4, HIGH);

  int theta_s = map(channel[0], 1093, 1887, 0, 90); 
  int theta_r = map(channel[1],  2088, 894, -90, 90); 

  /*Serial.print("Valor de rádio: ");
  Serial.print(theta_s);
  Serial.print("    ");
  Serial.println(theta_r);*/

  sail_servo.write(map(theta_s, 0, 90, sail_min, sail_max));
  rudder_servo.write(map(theta_r, -90, 90, rudder_min, rudder_max));

  /*Serial.print("Valor de servo: ");
  Serial.print(map(theta_s, 0, 90, sail_min, sail_max));
  Serial.print("    ");
  Serial.println(map(theta_r, -90, 90, rudder_min, rudder_max));*/
  
}

