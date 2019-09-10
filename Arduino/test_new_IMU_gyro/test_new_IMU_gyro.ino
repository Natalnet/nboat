//Programa : Teste MPU6050 e LCD 20x4
//Alteracoes e adaptacoes : FILIPEFLOP
//
//Baseado no programa original de JohnChi
 
//Carrega a biblioteca Wire
#include<Wire.h>
#include<IMU_NEW.h>
//Carrega a biblioteca do LCD
#include <LiquidCrystal.h>
 
// Inicializa o LCD
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
 
//Endereco I2C do MPU6050
const int MPU=0x68;  
//Variaveis para armazenar valores dos sensores
int AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;
void setup()
{
  Serial.begin(9600);
  //Inicializa o LCD
  lcd.begin(20, 4);
  Wire.begin();
  Wire.beginTransmission(MPU);
  Wire.write(0x6B); 
   
  //Inicializa o MPU-6050
  Wire.write(0); 
  Wire.endTransmission(true);
     
  //Informacoes iniciais do display
  lcd.setCursor(0,0);
  lcd.print("Acelerometro");
  lcd.setCursor(0,2);
  lcd.print("Giroscopio");
}
void loop()
{
  Wire.beginTransmission(MPU);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  //Solicita os dados do sensor
  Wire.requestFrom(MPU,14,true);  
  //Armazena o valor dos sensores nas variaveis correspondentes
  AcX=Wire.read()<<8|Wire.read();  //0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)     
  AcY=Wire.read()<<8|Wire.read();  //0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZ=Wire.read()<<8|Wire.read();  //0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  Tmp=Wire.read()<<8|Wire.read();  //0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
  GyX=Wire.read()<<8|Wire.read();  //0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  GyY=Wire.read()<<8|Wire.read();  //0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  GyZ=Wire.read()<<8|Wire.read();  //0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)
   
  //Envia valor X do acelerometro para a serial e o LCD
  Serial.print("AcX = "); Serial.print(AcX);
  lcd.setCursor(0,1);
  lcd.print("X=");
  lcd.print(AcX);
   
  //Envia valor Y do acelerometro para a serial e o LCD
  Serial.print(" | AcY = "); Serial.print(AcY);
  lcd.setCursor(7,1);
  lcd.print("Y=");
  lcd.print(AcY);
   
  //Envia valor Z do acelerometro para a serial e o LCD
  Serial.print(" | AcZ = "); Serial.print(AcZ);
  lcd.setCursor(13,1);
  lcd.print("Z=");
  lcd.print(AcZ);
   
  //Envia valor da temperatura para a serial e o LCD
  //Calcula a temperatura em graus Celsius
  Serial.print(" | Tmp = "); Serial.print(Tmp/340.00+36.53);
  lcd.setCursor(13,0);
  lcd.print("T:");
  lcd.print(Tmp/340.00+36.53);
   
  //Envia valor X do giroscopio para a serial e o LCD
  Serial.print(" | GyX = "); Serial.print(GyX);
  lcd.setCursor(0,3);
  lcd.print("X=");
  lcd.print(GyX);
   
  //Envia valor Y do giroscopio para a serial e o LCD  
  Serial.print(" | GyY = "); Serial.print(GyY);
  lcd.setCursor(7,3);
  lcd.print("Y=");
  lcd.print(GyY);
   
  //Envia valor Z do giroscopio para a serial e o LCD
  Serial.print(" | GyZ = "); Serial.println(GyZ);
  lcd.setCursor(13,3);
  lcd.print("Z=");
  lcd.print(GyZ);
   
  //Aguarda 300 ms e reinicia o processo
  delay(300);
}

void writeReg(byte reg, byte value)
{
  Wire.beginTransmission(MPU);
  Wire.write(reg);
  Wire.write(value);
  Wire.endTransmission();
}
