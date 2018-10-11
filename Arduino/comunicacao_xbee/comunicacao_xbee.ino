//Programa : Comunicacao Xbee utilizando Arduino Xbee Shield
//Autor : FILIPEFLOP
 
//Armazena os valores recebidos da serial
int valores = 0;
//Armazena o estado do led
String estado;

float latitude = 15.123459;
float longitude = 16.0;
float heading = 10.0;
float curse = 0.0;
float windDir = 18.0;
float bateria = 18.0;
float rudderAngle = 18.0;
float sailAngle = 18.0;
float boatSpd = 1.2;
int waypointId = 1;

  
void setup()
{
  //Define o pino 13 - LED embutido no Arduino - como saida
  pinMode(13, OUTPUT);
  Serial2.begin(9600);
  delay(2000);
}
  
void loop()
{
  //Aguarda dados na serial
  //if (Serial.available() > 0)
  //{
//    valores = Serial.read(); 
//    //Caso seja recebido 0, apaga o led
//    if(valores == '0')
//    {
//      digitalWrite(13, LOW);
//      estado = "apagado";
//    }
//    //Caso seja recebido 1, acende o led
//    else if(valores == '1')
//    {
//      digitalWrite(13, HIGH);
//      estado = "aceso";
//    }    
    //Envia mensagem de confirmacao
    heading = heading+10;
    curse = curse+7;
    windDir = windDir+1;
    latitude = latitude +2;
    if (heading > 360){
      heading = 0;
      windDir = 0;
      longitude = 0;
      curse = 10;
    }

    Serial2.print("{");
    Serial2.print(latitude, 6); Serial2.print(",");
    Serial2.print(longitude); Serial2.print(",");
    Serial2.print(heading); Serial2.print(",");
    Serial2.print(curse); Serial2.print(",");
    Serial2.print(windDir); Serial2.print(",");
    Serial2.print(bateria); Serial2.print(",");
    Serial2.print(rudderAngle); Serial2.print(",");
    Serial2.print(sailAngle); Serial2.print(",");
    Serial2.print(boatSpd); Serial2.print(",");
    Serial2.print(waypointId); Serial2.print("}");
    delay(200);
    //Serial.print(estado);
    //Serial.write(10);
  //}
}
