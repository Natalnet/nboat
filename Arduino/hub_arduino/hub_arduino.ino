void setup()
{
  //Define o pino 13 - LED embutido no Arduino - como saida
  pinMode(13, OUTPUT);
  Serial.begin(9600);
  Serial2.begin(9600);
  delay(2000);
}
  
void loop()
{
  //Aguarda dados na serial
  if (Serial2.available() > 0)
  {
    Serial.write(Serial2.read()); 
  }
}
