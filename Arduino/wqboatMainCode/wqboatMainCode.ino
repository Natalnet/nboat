#include "BoatControl.h"
#include "Navigation.h"

BoatControl movementControl;
GPS gps;
WeatherSensors windSensors;
vector<Location> waypoints, tackWaypoints;


Location nextLocation, lastLocation, currentLocation;
int waypoints_id, waypointsT_id, contador_bug;
float start, tempo, distanciaPercorrida, distanceToTarget, lastDistanciaDestino, desiredDistance;
bool isTacking;

void setup() {
  desiredDistance = 10;
  //waypoint 1
  //waypoint 2

}

void loop() {
  // put your main code here, to run repeatedly:
  
  // check the availability of the sensors
  // gps.isWorking(); compass.isWorking();
  // recieve a target position
  // adjust rudder and thruster accordingly
  // store boat state (position, velocity, orientation, actuators position)
  // check if the desired point was achieved
  // if yes, go to next target point

  while (1) {
    // navigation control (current waypoint)
    if (waypoints.size() != 0) {
      if (distanceToTarget < desiredDistance) { //in meters
          waypoints_id += 1;
          waypoints_id = waypoints_id % waypoints.size();
          nextLocation = waypoints.at(waypoints_id);          
      } else {
          nextLocation = waypoints.at(waypoints_id);
      }

      // adjust rudder and sail accordingly
      movementControl.rudderHeadingControl(nextLocation);
      movementControl.thrusterControl(nextLocation);
      //control done by the arduino uno on the sail actuator compartiment
      //movementControl.sailControl();

      // keep track of distance to target
      lastDistanciaDestino = distanceToTarget;
      distanceToTarget = gps.computeDistance(currentLocation, nextLocation);

      distanciaPercorrida += gps.computeDistance(lastLocation, currentLocation);
      
      // caso o barco não esteja avançando ao destino. solução: selecionar outro waypoint
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
      
      lastLocation = currentLocation;
      
      //record and send data to base station
      //salvar_dados();
    }
  }
}
