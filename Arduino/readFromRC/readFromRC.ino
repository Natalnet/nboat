double channel[3];

void setup() {
  pinMode(34, INPUT);
  pinMode(35, INPUT);
  pinMode(36, INPUT);
  Serial.begin(9600);
}

void loop() {

  channel[0] = pulseIn(34, HIGH);
  channel[1] = pulseIn(35, HIGH);
  channel[2] = pulseIn(36, HIGH);
  Serial.println("Canal 0: "+String(channel[0]));
  //Serial.println("Canal 1: "+String(channel[1]));
  //Serial.println("Canal 2: "+String(channel[2]));
  
}
