#include<Wire.h>

void setup()
{
  Wire.begin();
  Serial.begin(9600);
}

void loop()
{
  int a = 300;   //0x012C
  int b = 400; //0x0190
  int c = -500; //0x0190
  Wire.beginTransmission(10);  //slaveAddress
  Wire.write(highByte(a)); //I2C is byte oriented; write(a);
  Wire.write(lowByte(a));
  Wire.write(highByte(b)); //I2C is byte oriented; write(a);
  Wire.write(lowByte(b));
  Wire.write(highByte(c)); //I2C is byte oriented; write(a);
  Wire.write(lowByte(c));
  Wire.endTransmission();
  //delay(1000);

  //int b = 400;   //
  //Wire.beginTransmission(0x40);
  //Wire.write(b);
  //Wire.endTransmission();
  delay(100);
}
