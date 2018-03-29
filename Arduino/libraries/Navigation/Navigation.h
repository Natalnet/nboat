/*

  Compass.h - Library for getting curent heading from compass.
  Created by Davi H. dos Santos, March 25, 2018.
  BSD license, all text above must be included in any redistribution.

*/

#ifndef Navigation_h
#define Navigation_h

#include "Arduino.h"
#include "Location.h"

class Navigation
{
  public:
    Location(float gridNorth);
    vector<Location> bordejar(Location atual, Location destino, float heeling, float angulo_bordejo = 60, float taxa_dist = 0.2);
  private:
    float x0, y0, x, y, a_A, b_A, thetaAB, a_B, b_B, d, d_p0, latBord, lonBord, latProj, lonProj, latIni, lonIni, latFim, lonFim, latMedia, lonMedia, b_linha1, y_tira_teima1, x_tira_teima1, b_linha2, delta_x, delta_y, tt_x, tt_y, lat_temp, lon_temp, aux, delta_xaux, delta_yaux, d_p0_pu, d_p0_pd, _heading, a_aux, b_aux, teste;
    int num_pontos, bom, ruim, tamanho_pontos_bordejo, distancia_inicial;
    Location aux_loc, controle_loc, controle1, p0l1, p0l2, p0m, ponto_projetado, pontoProj, temp1, temp2;
    vector<Location> pontos_bordejo;

};

#endif
