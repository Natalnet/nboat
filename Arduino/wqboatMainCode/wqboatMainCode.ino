#include "BoatControl.h"
#include "Navigation.h"

BoatControl movementControl;
GPS gps;
WeatherSensors windSensors;
vector<Location> waypoints, tackWaypoints;


Location nextLocation, lastLocation, currentLocation;
int waypoints_id, waypointsT_id, bugManager;
float startTime, endTime, travelledDistance, distanceToTarget, lastDistanciaDestino, desiredDistance;
bool isTacking;

void setup() {
  desiredDistance = 10;
  //waypoint 1
  //waypoint 2

}

void loop() {
  
  // check the availability of the sensors
  // gps.isWorking(); compass.isWorking();
  // recieve a target position
  // adjust rudder and thruster accordingly
  // store boat state (position, velocity, orientation, actuators position)
  // check if the desired point was achieved
  // if positive, go to next target point

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

      // adjust rudder and thruster power accordingly
      movementControl.rudderHeadingControl(nextLocation);
      movementControl.thrusterControl(nextLocation);

      // keep track of distance to target
      lastDistanciaDestino = distanceToTarget;
      distanceToTarget = gps.computeDistance(currentLocation, nextLocation);
      travelledDistance += gps.computeDistance(lastLocation, currentLocation);
      
      // in case the boat isnt getting closer to the desired target -> select the next one
      if(distanceToTarget >= lastDistanciaDestino){
        if(bugManager == 0){
          startTime = millis();
          bugManager = 1;
        }
      } else {
        bugManager = 0;
      }
      
      endTime = millis();

      // if 20 seconds passes and the boat isnt advancing to the target, go to the next one
      if((endTime - startTime) > 20000){
        distanceToTarget = 0; //TODO generate error message
      }
      
      lastLocation = currentLocation;
      
      //record and send data to base station
      //salvar_dados();
    }
  }
}
