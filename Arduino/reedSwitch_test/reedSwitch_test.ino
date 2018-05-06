/******************************************************************************
Reed_Switch_Example.ino
Example sketch for SparkFun's Reed Switch
  (https://www.sparkfun.com/products/8642)
Jim Lindblom @ SparkFun Electronics
May 3, 2016

The reed switch is a two-terminal, magnetically-actuated, normally-open switch.
Connect one end of the switch to ground, and the other to Arduino's D2 pin.

The D2 pin's internal pull-up resistor is used to bias the pin high. When the
switch closes, the pin should go low.

Development environment specifics:
Arduino 1.6.7
******************************************************************************/
const int REED_PIN = 8; // Pin connected to reed switch
const int LED_PIN = 13; // LED pin - active-high

void setup() 
{
  Serial.begin(9600);
  // Since the other end of the reed switch is connected to ground, we need
  // to pull-up the reed switch pin internally.
  pinMode(REED_PIN, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);
}

void loop() 
{
  int proximity = digitalRead(REED_PIN); // Read the state of the switch
  if (proximity == LOW) // If the pin reads low, the switch is closed.
  {
    Serial.println("Switch closed");
    digitalWrite(LED_PIN, HIGH); // Turn the LED on
  }
  else
  {
    digitalWrite(LED_PIN, LOW); // Turn the LED off
  }
}
