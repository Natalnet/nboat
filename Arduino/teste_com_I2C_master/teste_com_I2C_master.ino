// Wire Master Writer
// by Nicholas Zambetti <http://www.zambetti.com>

// Demonstrates use of the Wire library
// Writes data to an I2C/TWI slave device
// Refer to the "Wire Slave Receiver" example for use with this

// Created 29 March 2006

// This example code is in the public domain.


#include <Wire.h>

void setup() {
  Wire.begin(); // join i2c bus (address optional for master)
  Serial.begin(9600);
}

int x = 0;
int y = 0;

void loop() {
  Wire.beginTransmission(8); // transmit to device #8
  Wire.write("x is ");        // sends five bytes
  Wire.write(x);              // sends one byte
  Wire.endTransmission();    // stop transmitting

  Wire.beginTransmission(10); // transmit to device #8
  Wire.write("y is ");        // sends five bytes
  Wire.write(y);              // sends one byte
  Wire.endTransmission();    // stop transmitting

  x++;
  y = y + 10;

  Serial.println(x);
  
  delay(500);
}
