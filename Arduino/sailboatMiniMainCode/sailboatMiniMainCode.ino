/*
 * Code associated to the circuit schematic in https://github.com/Natalnet/nboat/blob/sailboat_mini/sailboatSchematics.fzz
 */

#include "SailboatControl.h"
#include "Navigation.h"

SailboatControl movementControl;
GPS_EM506 gps;
WeatherSensors windSensors;
vector<Location> waypoints, tackWaypoints;

Location nextLocation, lastLocation, currentLocation, tempLocation;
int waypoints_id, waypointsT_id, bugHandler;
float startTime, endTime, travelledDistance, distanceToTarget, lastDistanceToTarget, desiredDistance, timeInterval;
bool isTacking;

void setup() {
  desiredDistance = 10;
  //add waypoints example:
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

  // program flow:
  // initialize and check the availability of the sensors (inside libraries) --> OdometrySensors.isWorking() gps.isWorking(); compass.isWorking();
  // recieve a target position
  // adjust rudder and sail accordingly
  // store sailboat state (gps info, imu info, actuators position, wind velocity, wind direction, batery charge)
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
      movementControl.sailControl();

      // keep track of distance to target
      lastDistanceToTarget = distanceToTarget;
      distanceToTarget = gps.computeDistance(currentLocation, nextLocation);
      travelledDistance += gps.computeDistance(lastLocation, currentLocation);
      
      // in case the boat isnt getting closer to the desired target -> select the next one
      if(distanceToTarget >= lastDistanceToTarget){
        if(bugHandler == 0){
          startTime = millis();
          bugHandler = 1;
        }
      } else {
        bugHandler = 0;
      }
      
      endTime = millis();
      timeInterval = endTime - startTime;
      
      if((timeInterval > 20000)){
        distanceToTarget = 0;
      }
           
      lastLocation = currentLocation;
      
      //record and send data to base station
      //salvar_dados();
    }
  }
}
