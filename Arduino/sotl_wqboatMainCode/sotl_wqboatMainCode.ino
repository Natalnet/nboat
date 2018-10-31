#include "BoatControl.h"
#include "NavigationFunctions.h"

BoatControl movementControl;
GPS_EM506 gps;
WeatherSensors windSensors;
vector<Location> waypoints, tackWaypoints;

Location nextLocation, lastLocation, currentLocation, tempLocation;
int waypoints_id, waypointsT_id, bugManager;
float startTime, endTime, travelledDistance, distanceToTarget, lastDistanciaDestino, desiredDistance, timeInterval;
bool isTacking;

void setup() {
  desiredDistance = 10;
  //add waypoints:
  //waypoint 1 - natalnet
  tempLocation.latitude = -5.842986;
  tempLocation.longitude = -35.197465;
  waypoints.push_back(tempLocation);
  
  //waypoint 2 - rua das engenharias
  tempLocation.latitude = -5.842044;
  tempLocation.longitude = -35.197449;
  waypoints.push_back(tempLocation);

  //waypoint 3 - larhisa
  tempLocation.latitude = -5.842544;
  tempLocation.longitude = -35.197839;
  waypoints.push_back(tempLocation);

  //waypoint 4 - pet elétrica
  tempLocation.latitude = -5.842417;
  tempLocation.longitude = -35.197069;
  waypoints.push_back(tempLocation);
  Serial.begin(9600);

}

void loop() {

  //TODO how to test this code on software? (Software on the Loope tests??)

  // program flow:
  // initialize and check the availability of the sensors (inside libraries) --> OdometrySensors.isWorking() gps.isWorking(); compass.isWorking();
  // recieve a target position
  // adjust rudder and thruster accordingly
  // store boat state (position, velocity, orientation, actuators position, wind velocity, wind direction)
  // check if the desired point was achieved
  // if positive, go to next target point

  while (1) {
    // navigation control (current waypoint)
    if (waypoints.size() != 0) {
      if (distanceToTarget < desiredDistance) { //in meters
          waypoints_id += 1;
          waypoints_id = waypoints_id % waypoints.size();
          nextLocation = waypoints.at(waypoints_id);
          delay(2000);
          startTime = millis();
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
      /*if(distanceToTarget >= lastDistanciaDestino){
        if(bugManager == 0){
          startTime = millis();
          bugManager = 1;
        }
      } else {
        bugManager = 0;
      }*/
      
      endTime = millis();
      timeInterval = endTime - startTime;

      // if 20 seconds passes and the boat isnt advancing to the target, go to the next one
      if(timeInterval > 10000){
        movementControl.setDistanceToTarget(0);
        distanceToTarget = 0;
        //distanceToTarget = 0; //TODO generate error message
      }
      if(timeInterval < 10000 && timeInterval > 5000){
        movementControl.setDistanceToTarget(9);
        //distanceToTarget = 9;
      }
      if(timeInterval < 5000){
        movementControl.setDistanceToTarget(15);
      }
      
      lastLocation = currentLocation;
      Serial.print("Going to waypoint -> ");
      Serial.println(waypoints_id);
      
      //record and send data to base station
      //salvar_dados();
    }
  }
}
