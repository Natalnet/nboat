/*

  Navigation.cpp - Library that compile multiple navigation behavior necessary for proper sailboat movement.
  Created by Davi H. dos Santos, March 28, 2018.
  BSD license, all text above must be included in any redistribution.

*/

#include "Arduino.h"
#include "Navigation.h"

//preciso inicializar alguma coisa?
Navigation::Navigation(){
}

vector<Location> Navigation::findTackingPoints(SensorManager sensors, Location current, Location target, float tackingAngle, float tackingWidenessRate)
{
  // getting curent heeling value
  _heading = sensors.getCompass();
  _windDirection = sensors.getWind().direction;
  _heeling = _windDirection - _heading;
  _sp = findHeading(current, target);

  x0 = current.latitude;
  y0 = current.longitude;
  x = target.latitude;
  y = target.longitude;

  initialDistance = findDistance(current, target);
  tackingWideness = tackingWidenessRate * initialDistance;

  //finds the line between inital and target
  a_A = (y - y0) / (x - x0);
  b_A = y0 - (a_A * x0);
  //float x_temp = x0;
  //float y_temp = a_A * x_temp + b_A;

  //muda a direção do bordejo
  if (_heeling - _heading < 0){
     tackingAngle = -tackingAngle;
  }

  //float thetaAB = abs(adjustFrame(windDirection)) - tackingAngle;
  thetaAB = tackingAngle;
  thetaAB = adjustFrame(thetaAB);
  
  //encontra a reta B tal que thetaAB = 45º - windDirection e a interseção seja o ponto inicial
  tan_thetaAB = (float)tan((thetaAB) * (PI / 180));
  a_B = (a_A - tan_thetaAB) / (tan_thetaAB * a_A + 1);

  b_B = y0 - (a_B * x0);

  //inicialização de variáveis auxiliares
  d = initialDistance;
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

  while (fabs(d - tackingWideness) > 1) {
    latMedia = (latFim + latIni) / 2;
    lonMedia = (lonFim + lonIni) / 2;

    pontoProj = projection2dMod(latMedia, lonMedia, a_A, b_A, a_B, b_B);
    
    d = (float)TinyGPS::distance_between(latMedia, lonMedia, pontoProj.latitude, pontoProj.longitude);

    if (d > tackingWideness){
      latFim = latMedia;
      lonFim = lonMedia;
    } else if (d < tackingWideness){
      latIni = latMedia;
      lonIni = lonMedia;
    }

    latBord = latMedia;
    lonBord = lonMedia;
  }

  ponto_projetado = angleToLocation(latBord, lonBord);

  latProj = pontoProj.latitude;
  lonProj = pontoProj.longitude;

  p0m = projection2d(latProj, lonProj, a_A, b_A);
  d_p0 = (float)TinyGPS::distance_between(p0m.latitude, p0m.longitude, x0, y0);

  //insere o ponto encontrado no vetor com os pontos do bordejo
  TackingPointsVector.push_back(angleToLocation(latProj, lonProj));

  //encontra as retas paralelas a reta A, onde estão localizados os pontos de bordejo
  b_linha1 = (-a_A * TackingPointsVector.at(0).latitude + TackingPointsVector.at(0).longitude);
  y_tira_teima1 = (a_A * TackingPointsVector.at(0).latitude + b_linha1);
  x_tira_teima1 = (TackingPointsVector.at(0).longitude - b_linha1) / a_A;
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
  p0l1 = projection2d(p0m.latitude, p0m.longitude, a_A, b_linha1);
  p0l2 = projection2d(p0m.latitude, p0m.longitude, a_A, b_linha2);
  bom = 1;
  ruim = 1;

  for (int z = 1; z < num_pontos; z++)
  {

    delta_x_temp = z * delta_x;
    delta_y_temp = z * delta_y;

    if (z % 2 == 0)
    {
      controle1 = TackingPointsVector.at(z-1);
      lat_temp = (float)p0l1.latitude + delta_x_temp;
      lon_temp = (float)p0l1.longitude + delta_y_temp;
      controle_loc = angleToLocation(lat_temp, lon_temp);
      TackingPointsVector.push_back(controle_loc);
      bom = z;
    }
    else {
      controle1 = TackingPointsVector.at(z-1);
      aux = fabs((_heeling - fabs(adjustFrame(_sp))));
      delta_xaux = aux * delta_x / 31;
      delta_yaux = aux * delta_y / 31;
      lat_temp = p0l2.latitude + delta_x_temp - delta_xaux;
      lon_temp = p0l2.longitude + delta_y_temp - delta_yaux;
      controle_loc = angleToLocation(lat_temp, lon_temp);
      TackingPointsVector.push_back(controle_loc);
      ruim = z;
    }
  }
  
  numberOfTackingPoints = TackingPointsVector.size();

  d_p0_pu = (float)TinyGPS::distance_between(TackingPointsVector.at(numberOfTackingPoints-1).latitude, TackingPointsVector.at(numberOfTackingPoints-1).longitude, current.latitude, current.longitude);
  d_p0_pd = (float)TinyGPS::distance_between(x0, y0, x, y);

  aux_loc.latitude = target.latitude;
  aux_loc.longitude = target.longitude;

  if(d_p0_pu > d_p0_pd){
    TackingPointsVector.at(numberOfTackingPoints-1) = aux_loc;
  } else {
    TackingPointsVector.push_back(aux_loc);
  } 
  
  return TackingPointsVector;
}

float Navigation::adjustFrame(float sensor) {
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

Location Navigation::projection2dMod(float lat, float lon, float a, float b, float a_p, float b_p)
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

Location Navigation::projection2d(float lat, float lon, float a, float b)
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

float Navigation::findDistance(Location p1, Location p2){
  return TinyGPS::distance_between(p1.latitude, p1.longitude, p2.latitude, p2.longitude);
}

float Navigation::findHeading(Location p1, Location p2){
  headingTmp = TinyGPS::course_to(p1.latitude, p1.longitude, p2.latitude, p2.longitude);
  if(headingTmp > 180){
    headingTmp = headingTmp-360;
  }
  if(headingTmp < -180){
    headingTmp = headingTmp+360;
  }
  return headingTmp;
}
