/* Sweep
 by BARRAGAN <http://barraganstudio.com>
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Sweep
*/

#include <Servo.h>

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position

void setup() {
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  myservo.write(30);
  delay(3000);
<<<<<<< HEAD
=======
  Serial.begin(9600);
>>>>>>> b492afe35b15e4a98938dde89765ba0162371230
  myservo.write(0);
}

void loop() {
<<<<<<< HEAD
  //float test = 15;
  //myservo.write(test);              // tell servo to go to position in variable 'pos'
  //delay(15);                       // waits 15ms for the servo to reach the position
=======
//  for(int i=50; i < 150; i = i+10){
//    myservo.write(i);              // tell servo to go to position in variable 'pos'
//    delay(1000);                       // waits 15ms for the servo to reach the position
//    Serial.println(i);
//  }
>>>>>>> b492afe35b15e4a98938dde89765ba0162371230
}

