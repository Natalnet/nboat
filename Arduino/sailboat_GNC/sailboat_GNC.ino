#include "SailingControl.h"
#include "Navigation.h"

SailingControl movementControl;
Navigation sailboatNavigation;
GPS gps;
WeatherSensors windSensors;
vector<Location> waypoints, tackWaypoints;


Location nextLocation, lastLocation, currentLocation;
int waypoints_id, waypointsT_id, contador_bug;
float start, tempo, distanciaPercorrida, distanceToTarget, lastDistanciaDestino;
bool isTacking;

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:
  
  // check the availability of the sensors
  // gps.isWorking(); compass.isWorking();
  // recieve a target position
  // adjust rudder and sail accordingly
  // store sailboat state
  // send sailboat state to base
  // check if the desired point was achieved
  // if yes, go to next target point

  while (1) {
    // navigation control (current waypoint)
    if (waypoints.size() != 0) {
      if (distanceToTarget < 10) { //in meters
        if (isTacking) {
          if (waypointsT_id < tackWaypoints.size() - 1) {
            waypointsT_id += 1;
            nextLocation = tackWaypoints.at(waypointsT_id);
          } else {
            isTacking = false;
            waypointsT_id = 0;
          }
        } else {
          waypoints_id += 1;
          waypoints_id = waypoints_id % waypoints.size();
          nextLocation = waypoints.at(waypoints_id);          
        }
      } else {
        if (isTacking) {
          nextLocation = tackWaypoints.at(waypointsT_id);
        } else {
          nextLocation = waypoints.at(waypoints_id);
        }
      }

      // adjust rudder and sail accordingly
      movementControl.rudderHeadingControl(nextLocation);
      movementControl.sailControl();

      // keep track of distance to target
      lastDistanciaDestino = distanceToTarget;
      distanceToTarget = gps.computeDistance(currentLocation, nextLocation);

      distanciaPercorrida += gps.computeDistance(lastLocation, currentLocation);
      
      // caso o veleiro não esteja avançando ao destino. solução: selecionar outro waypoint
      if(distanceToTarget >= lastDistanciaDestino){
        if(contador_bug == 0){
          start = millis();
          contador_bug = 1;
        }
      } else {
        contador_bug = 0;
      }

      tempo = millis();

      if((tempo - start) > 20000){
        distanceToTarget = 0;
      }

      // check if it needs to tack
      if (fabs(windSensors.readWindDirection()) < 30 && !isTacking) {
        isTacking = true;
        tackWaypoints = sailboatNavigation.findTackingPoints(lastLocation, nextLocation);
      }
      
      lastLocation = currentLocation;
      
      //record and send data do base station
      //salvar_dados();
    }
  }
}
