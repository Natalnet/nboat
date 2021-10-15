// Wire Slave Receiver
// by Nicholas Zambetti <http://www.zambetti.com>

// Demonstrates use of the Wire library
// Receives data as an I2C/TWI slave device
// Refer to the "Wire Master Writer" example for use with this

// Created 29 March 2006

// This example code is in the public domain.


#include <Wire.h>

void setup() {
  Wire.begin(8);                // join i2c bus with address #8
  Wire.onReceive(receiveEvent); // register event
  Serial.begin(9600);           // start serial for output
}

void loop() {
  delay(100);
}

// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent(int howMany) {
  int c;
  int a,b;
  while (Wire.available()) { // loop through all but the last
    a = Wire.read(); // receive byte as a character
    b = Wire.read(); // receive byte as a character
    Serial.println(a-95);
    //c = c >> 8;
    //Serial.println(map(c, 0, 179, -90, 90));         // print the character
  }
  //Serial.println(map(a, 0, 179, -90, 90));
//  Serial.println(a-95);         // print the character
//  Serial.println(b);         // print the character
//  Serial.println();         // print the character
}

