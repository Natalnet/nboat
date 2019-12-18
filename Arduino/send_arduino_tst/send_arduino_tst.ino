float a = 1.2345;
float b = 1.3345;
float c = 1.4345;
float d = 1.5345;

void setup() {
  // initialize serial communication at 9600 bits per second:
  
  Serial.begin(57600);
  // make the pushbutton's pin an input:
  //pinMode(pushButton, INPUT);
}

// the loop routine runs over and over again forever:
void loop() {
  if(Serial.available() > 0){
    if(Serial.read() == 'f'){
      Serial.println(a,4);
      Serial.println(b,4);
      Serial.println(c,4);
      Serial.println(d,4);
    }
  }
}
