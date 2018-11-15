double channel;
void setup() {
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(4, INPUT);
  Serial.begin(9600);

}

void loop() {
  channel[0] = pulseIn(2, HIGH);
  channel[1] = pulseIn(3, HIGH);
  channel[2] = pulseIn(4, HIGH);
  Serial.println(channel);
}
