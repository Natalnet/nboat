/*

  Navigation.h -Library that compile multiple navigation behavior necessary for proper sailboat movement.
  Created by Davi H. dos Santos, March 28, 2018.
  BSD license, all text above must be included in any redistribution.

*/

#ifndef Navigation_h
#define Navigation_h

#include "Arduino.h"
#include "SensorManager.h"
#include <StandardCplusplus.h>
#include <vector>

using namespace std;

class Navigation
{
  public:
    Navigation();
    vector<Location> findTackingPoints(Location current, Location target, float tackingAngle = 60, float tackingWidenessRate = 0.2);
    float adjustFrame(float sensor);
    Location angleToLocation(float lat, float lon);
  private:
    float x0, y0, x, y, a_A, b_A, thetaAB, a_B, b_B, d, d_p0, latBord, lonBord, latProj, lonProj, latIni, lonIni, latFim, lonFim, latMedia, lonMedia, b_linha1, y_tira_teima1, x_tira_teima1, b_linha2, delta_x, delta_y, tt_x, tt_y, lat_temp, lon_temp, aux, delta_xaux, delta_yaux, d_p0_pu, d_p0_pd, _heading, a_aux, b_aux, teste, _windDirection, _heeling, tackingWideness, tan_thetaAB, delta_x_temp, delta_y_temp, _sp, initialDistance;
    int num_pontos, bom, ruim, numberOfTackingPoints;
    Location aux_loc, controle_loc, controle1, p0l1, p0l2, p0m, ponto_projetado, pontoProj, temp1, temp2;
    vector<Location> TackingPointsVector;
    Mag_HMC5883L _compass;
    WeatherSensors _weatherSensors;
    GPS_EM506 _gps;
    Location projection2dMod(float lat, float lon, float a, float b, float a_p, float b_p);
    Location projection2d(float lat, float lon, float a, float b);

};

#endif
