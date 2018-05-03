char test[32];
String test1;

void setup() {
  Serial.begin(9600);
}

void loop() {
  test1 = String(test);
  test1 += ".txt";
  if (test1 != "") {
    Serial.println(test1);
  } else {
    Serial.println("NULL");
  }
}
