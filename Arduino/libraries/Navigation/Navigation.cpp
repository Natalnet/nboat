/*

  Compass.cpp - Library for getting curent heading from compass.
  Created by Davi H. dos Santos, March 25, 2018.
  BSD license, all text above must be included in any redistribution.

*/

#include "Arduino.h"
#include "Location.h"
#include "Navigation.h"
#include "GPS.h"
#include "Compass.h"
#include "TinyGPS.h"

//preciso inicializar alguma coisa?
Navigation::Navigation(){
}

vector<Location> Navigation::bordejar(Location atual, Location destino, float angulo_bordejo, float taxa_dist)
{
  // getting curent heeling value
  _heading = Compass::readHeading();
  _biruta = weatherSensors::readWindVane(); //TODO
  _heeling = _biruta - _heading;

  x0 = atual.latitude;
  y0 = atual.longitude;
  x = destino.latitude;
  y = destino.longitude;

  distanciaInicial = GPS::computeDistance(atual, destino);
  distancia_bordejar = taxa_dist * distanciaInicial;

  //calcula a reta entre o ponto inicial e de destino
  a_A = (y - y0) / (x - x0);
  b_A = y0 - (a_A * x0);
  //float x_temp = x0;
  //float y_temp = a_A * x_temp + b_A;

  //muda a direção do bordejo
  if (heeling - _heading < 0){
     angulo_bordejo = -angulo_bordejo;
  }

  //float thetaAB = abs(saturador(biruta)) - angulo_bordejo;
  thetaAB = angulo_bordejo;
  thetaAB = Navigation::saturador(thetaAB);
  
  //encontra a reta B tal que thetaAB = 45º - biruta e a interseção seja o ponto inicial
  tan_thetaAB = (float)tan((thetaAB) * (PI / 180));
  a_B = (a_A - tan_thetaAB) / (tan_thetaAB * a_A + 1);

  b_B = y0 - (a_B * x0);

  //inicialização de variáveis auxiliares
  d = distanciaInicial;
  d_p0 = 9999999;

  latBord = x;
  lonBord = y;

  //pointBord.latitude = x; TODO
  //pointBord.longitude = y;
  //pointProj = pointBord;

  latProj = x;
  lonProj = y;

  latIni = x0;
  lonIni = y0;
  latFim = x;
  lonFim = y;

  while (abs(d - distancia_bordejar) > 1) {
    latMedia = (latFim + latIni) / 2;
    lonMedia = (lonFim + lonIni) / 2;

    pontoProj = projecao2d_mod(latMedia, lonMedia, a_A, b_A, a_B, b_B);
    
    d = (float)GPS::distance_between(latMedia, lonMedia, pontoProj.latitude, pontoProj.longitude);

    if (d > distancia_bordejar){
      latFim = latMedia;
      lonFim = lonMedia;
    } else if (d < distancia_bordejar){
      latIni = latMedia;
      lonIni = lonMedia;
    }

    latBord = latMedia;
    lonBord = lonMedia;
  }

  ponto_projetado = angleToLocation(latBord, lonBord);

  latProj = pontoProj.latitude;
  lonProj = pontoProj.longitude;

  location p0m = projecao2d(latProj, lonProj, a_A, b_A);
  d_p0 = (float)TinyGPS::distance_between(p0m.latitude, p0m.longitude, x0, y0);

  //insere o ponto encontrado no vetor com os pontos do bordejo
  pontos_bordejo.push_back(angleToLocation(latProj, lonProj));

  //encontra as retas paralelas a reta A, onde estão localizados os pontos de bordejo
  b_linha1 = (-a_A * pontos_bordejo.at(0).latitude + pontos_bordejo.at(0).longitude);
  y_tira_teima1 = (a_A * pontos_bordejo.at(0).latitude + b_linha1);
  x_tira_teima1 = (pontos_bordejo.at(0).longitude - b_linha1) / a_A;
  b_linha2 = 0;

  if (b_linha1 > b_A)
  {
    b_linha2 = b_A - (b_linha1 - b_A);
  }
  else
  {
    b_linha2 = b_A + (b_A - b_linha1);
  }

  //encontrando o número total de pontos de bordejo
  num_pontos = (int)floor((float)TinyGPS::distance_between(x0, y0, x, y) / d_p0);
  teste = (float)TinyGPS::distance_between(x0, y0, x, y);

  delta_x = (p0m.latitude - x0);
  delta_y = (p0m.longitude - y0);

  tt_x = x0 + delta_x;
  tt_y = y0 + delta_y;

  //encontra a projeção dos pontos iniciais nas duas retas paralelas
  p0l1 = projecao2d(p0m.latitude, p0m.longitude, a_A, b_linha1);
  p0l2 = projecao2d(p0m.latitude, p0m.longitude, a_A, b_linha2);
  bom = 1;
  ruim = 1;

  for (int z = 1; z < num_pontos; z++)
  {

    delta_x_temp = z * delta_x;
    delta_y_temp = z * delta_y;

    if (z % 2 == 0)
    {
      controle1 = pontos_bordejo.at(z-1);
      lat_temp = (float)p0l1.latitude + delta_x_temp;
      lon_temp = (float)p0l1.longitude + delta_y_temp;
      controle_loc = angleToLocation(lat_temp, lon_temp);
      pontos_bordejo.push_back(controle_loc);
      bom = z;
    }
    else {
      location controle1 = pontos_bordejo.at(z-1);
      aux = abs((heeling - abs(saturador(sp))));
      delta_xaux = aux * delta_x / 31;
      delta_yaux = aux * delta_y / 31;
      lat_temp = p0l2.latitude + delta_x_temp - delta_xaux;
      lon_temp = p0l2.longitude + delta_y_temp - delta_yaux;
      controle_loc = angleToLocation(lat_temp, lon_temp);
      pontos_bordejo.push_back(controle_loc);
      ruim = z;
    }
  }
  
  tamanho_pontos_bordejo = pontos_bordejo.size();

  d_p0_pu = (float)TinyGPS::distance_between(pontos_bordejo.at(tamanho_pontos_bordejo-1).latitude, pontos_bordejo.at(tamanho_pontos_bordejo-1).longitude, atual->latitude, atual->longitude);
  d_p0_pd = (float)TinyGPS::distance_between(x0, y0, x, y);

  aux_loc.latitude = destino->latitude;
  aux_loc.longitude = destino->longitude;

  if(d_p0_pu > d_p0_pd){
    pontos_bordejo.at(tamanho_pontos_bordejo-1) = aux_loc;
  } else {
    pontos_bordejo.push_back(aux_loc);
  } 
  
  return pontos_bordejo;
}

float Navigation::saturador(float sensor) {
  if (sensor > 180) {
    sensor = sensor - 360;
  }
  if (sensor < -180) {
    sensor = sensor + 360;
  }
  return sensor;
}

Location Navigation::angleToLocation(float lat, float lon) {
  Location temp;
  temp.latitude = lat;
  temp.longitude = lon;
  return temp;
}

Location Navigation::projecao2d_mod(float lat, float lon, float a, float b, float a_p, float b_p)
{
  if (a == 0) {
    a = 0.00000001;
  }
  if (b == 0) {
    b = 0.00000001;
  }
  a_aux = -1 / a;
  b_aux = -a_aux * lat + lon;

  float latProj = (b_aux - b_p) / (a_p - a_aux);
  float lonProj = a_p * latProj + b_p;

  return Navigation::angleToLocation(latProj, lonProj);
}

Location Navigation::projecao2d(float lat, float lon, float a, float b)
{
  if (a == 0) {
    a = 0.00000001;
  }
  if (b == 0) {
    b = 0.00000001;
  }
  a_aux = -1 / a;
  b_aux = -a_aux * lat + lon;

  float latProj = (b_aux - b) / (a - a_aux);
  float lonProj = a * latProj + b;

  return Navigation::angleToLocation(latProj, lonProj);
}
