/*
 * Code associated to the circuit schematic in https://github.com/Natalnet/nboat/blob/sailboat_mini/sailboatSchematics.fzz
 */

#include "SensorManager.h"
#include "SailboatControl.h"
#include "Navigation.h"

SailboatControl *movementControl;
SensorManager sensors;
WindData wind;
Navigation sailboatNavigation;
//GPS_EM506 gps;
//WeatherSensors windSensors;

vector<Location> waypoints, tackWaypoints;

Location nextLocation, lastLocation, currentLocation, tempLocation;
int waypoints_id, waypointsT_id, bugHandler;
float startTime, endTime, travelledDistance, distanceToTarget, lastDistanceToTarget, desiredDistance, timeInterval;
bool isTacking;

//task scheduler
typedef struct t  {
    unsigned long tStart;
    unsigned long tTimeout;
};

//Tasks and their Schedules.
t t_func1 = {0, 200}; //Run every 100ms
//t t_func2 = {0, 2000}; //Run every 2 seconds.

bool tCheck (struct t *t ) {
  if (millis() > t->tStart + t->tTimeout){
    return true;    
  } else {
    return false;
  }
}

void tRun (struct t *t) {
    t->tStart = millis();
}

void setup() {
  movementControl = new SailboatControl(1,0);
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
    // run sensors.read() at 10Hz
    if (tCheck(&t_func1)) {
      sensors.read();
      sensors.logState();
      tRun(&t_func1);
    }
    
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
      movementControl->rudderHeadingControl(sensors, nextLocation);
      movementControl->sailControl(sensors);

      // keep track of distance to target
      lastDistanceToTarget = distanceToTarget;
      distanceToTarget = sailboatNavigation.findDistance(currentLocation, nextLocation);
      travelledDistance += sailboatNavigation.findDistance(lastLocation, currentLocation);
      
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

       // check if it needs to tack
      wind = sensors.getWind();
      if (fabs(wind.direction) < 30 && !isTacking) {
        isTacking = true;
        tackWaypoints = sailboatNavigation.findTackingPoints(sensors, lastLocation, nextLocation);
      }
      //Serial.print("TEMPO: ");
      //Serial.println(millis()-startTime);
      
      //record and send data to base station
      //salvar_dados();
    }
  }
}
