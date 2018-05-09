#include "BoatControl.h"
#include "SensorManager.h"
#include "NavigationFunctions.h"


<<<<<<< HEAD:Arduino/wqboatMainCode/wqboatMainCode.ino
BoatControl *movementControl;

//go to SensorManager to setup sensors on the robot
SensorManager sensors;
=======
SailboatControl *movementControl;
SensorManager *sensors;
WindData wind;
Navigation sailboatNavigation;
//GPS_EM506 gps;
//WeatherSensors windSensors;
>>>>>>> sailboat_mini:Arduino/sailboatMiniMainCode/sailboatMiniMainCode.ino

NavigationFunctions navigationFunc;

vector<Location> waypoints;

Location nextLocation, lastLocation, currentLocation, tempLocation;
int waypoints_id, waypointsT_id, bugManager;
float startTime, endTime, travelledDistance, distanceToTarget, lastDistanciaDestino, desiredDistance, timeInterval;

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
<<<<<<< HEAD:Arduino/wqboatMainCode/wqboatMainCode.ino
  movementControl = new BoatControl(2,1);  
=======
  movementControl = new SailboatControl(1,0);
>>>>>>> sailboat_mini:Arduino/sailboatMiniMainCode/sailboatMiniMainCode.ino
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

<<<<<<< HEAD:Arduino/wqboatMainCode/wqboatMainCode.ino
=======
  sensors = new SensorManager();
  
>>>>>>> sailboat_mini:Arduino/sailboatMiniMainCode/sailboatMiniMainCode.ino
  Serial.begin(9600);

}

void loop() {

  // program flow:
<<<<<<< HEAD:Arduino/wqboatMainCode/wqboatMainCode.ino
  // check the availability of the sensors (inside libraries) --> OdometrySensors.isWorking() gps.isWorking(); compass.isWorking();
=======
  // initialize and check the availability of the sensors (inside libraries) --> Odometrysensors->isWorking() gps.isWorking(); compass.isWorking();
>>>>>>> sailboat_mini:Arduino/sailboatMiniMainCode/sailboatMiniMainCode.ino
  // recieve a target position
  // adjust rudder and thruster accordingly
  // store boat state (position, velocity, orientation, actuators position, wind velocity, wind direction)
  // check if the desired point was achieved
  // if positive, go to next target point

  while (1) {
<<<<<<< HEAD:Arduino/wqboatMainCode/wqboatMainCode.ino
    // run sensors.read() at 5Hz
=======
    // run sensors->read() at 10Hz
    sensors->read();
>>>>>>> sailboat_mini:Arduino/sailboatMiniMainCode/sailboatMiniMainCode.ino
    if (tCheck(&t_func1)) {
      sensors->logState();
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
      movementControl->thrusterControl(sensors, nextLocation);

      // keep track of distance to target
      lastDistanciaDestino = distanceToTarget;
      distanceToTarget = navigationFunc.findDistance(currentLocation, nextLocation);
      travelledDistance += navigationFunc.findDistance(lastLocation, currentLocation);
      
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
      timeInterval = endTime - startTime;

<<<<<<< HEAD:Arduino/wqboatMainCode/wqboatMainCode.ino
      // if 20 seconds passes and the boat isnt advancing to the target, go to the next one
      if(timeInterval > 20000){
        distanceToTarget = 0; //TODO generate error message
=======
       // check if it needs to tack
      wind = sensors->getWind();
      if (fabs(wind.direction) < 30 && !isTacking) {
        isTacking = true;
        tackWaypoints = sailboatNavigation.findTackingPoints(sensors, lastLocation, nextLocation);
>>>>>>> sailboat_mini:Arduino/sailboatMiniMainCode/sailboatMiniMainCode.ino
      }
      
      lastLocation = currentLocation;
    }
  }
}

