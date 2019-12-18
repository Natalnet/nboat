/*
  DigitalReadSerial

  Reads a digital input on pin 2, prints the result to the Serial Monitor

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/DigitalReadSerial
*/

int pushButton = 2;
String a;
float tst;

void setup() {
  //Serial1.begin(9600);
  Serial.begin(9600);
}

void loop() {
  int i = 10;
  Serial.println(float(i), 2);
  Serial.println(int(float(i)), 2);
  static float call[4];
  Serial2.begin(57600);
  while(Serial2.available() <= 0){
    Serial2.println("f");
  }
  delay(100);
  if(Serial2.available() > 0){
//    tst = Serial2.parseFloat();
    call[0] = Serial2.parseFloat();
    call[1] = Serial2.parseFloat();
    call[2] = Serial2.parseFloat();
    call[3] = Serial2.parseFloat();
   
    Serial.print(call[0],4); Serial.print(" ");
    Serial.print(call[1],4); Serial.print(" ");
    Serial.print(call[2],4); Serial.print(" ");
    Serial.println(call[3],4);
//    Serial.println(tst,4);
    Serial2.end();
  }
}
