int incomingByte = 0;   // for incoming serial data
float incoming[3];

void setup() {
        Serial.begin(9600);     // opens serial port, sets data rate to 9600 bps
        Serial2.begin(57600);
}

void loop() {

        // send data only when you receive data:
        Serial2.print("#f");
        delay(20);
        if (Serial2.available() > 0) {
           incomingByte = Serial2.read();
           Serial.println(incomingByte);
        }
}
