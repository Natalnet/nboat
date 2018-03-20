void atualizar_posicao(struct location local){  
  unsigned long start = millis();
  unsigned long ms = 500;
  do 
  {
    while(Serial3.available())
    {
      int c = Serial3.read();
      if(gps.encode(c))
      {
        gps.f_get_position(&local.latitude, &local.longitude);
        direcao = gps.f_course();
        velocidade = gps.f_speed_kmph();
      }
    }
  } while (millis() - start < ms);
  //distanciaAoDestino = (int)TinyGPS::distance_between(latitudeBarco, longitudeBarco, latitudeDestino, longitudeDestino);  
}

int calcular_distancia(struct location p1, struct location p2){
  return (int)TinyGPS::distance_between(p1.latitude, p1.longitude, p2.latitude, p2.longitude);
}

float calcular_orientacao(struct location p1, struct location p2){
  float sp_aux = TinyGPS::course_to(p1.latitude, p1.longitude, p2.latitude, p2.longitude);
  /*Serial.print("p1->lat: ");
  Serial.print(p1.latitude, 6);
  Serial.print(" ");
  Serial.print("p1->lon: ");
  Serial.print(p1.longitude, 6);
  Serial.print(" ");
  Serial.print("p2->lat: ");
  Serial.print(p2.latitude, 6);
  Serial.print(" ");
  Serial.print("p2->lon: ");
  Serial.print(p2.longitude, 6);
  Serial.print(" ");
  Serial.print("Course to -> ");
  Serial.println(sp_aux);*/
  //float sp_aux = TinyGPS::course_to(-5.842960, -35.197244, -5.842988, -35.196384);
  if(sp_aux > 180){
    sp_aux = sp_aux-360;
  }
  if(sp_aux < -180){
    sp_aux = sp_aux+360;
  }
  return sp_aux;
}

static void smartdelay(unsigned long ms)
{
  unsigned long start = millis();
  do 
  {
    while (Serial3.available())
      gps.encode(Serial3.read());
  } while (millis() - start < ms);
}
