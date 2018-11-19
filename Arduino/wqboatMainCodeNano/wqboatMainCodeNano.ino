#include "BoatControl.h"
#include "SensorManager.h"
#include "NavigationFunctions.h"

//READ RC CHANNELS
double channel[3];


//INSTATIATING LIBS
  BoatControl *movementControl;
  SensorManager *sensors;
  NavigationFunctions navigationFunc;
  

//WAYPOINTS SETUP
  vector<Location> waypoints, tackWaypoints;
  Location nextLocation, lastLocation, currentLocation, tempLocation;
  int waypoints_id, waypointsT_id, bugManager;
  float startTime, endTime, distanceToTarget = 99999999, lastDistanciaDestino, desiredDistance, timeInterval;
  double distanceTravelled;

  float testTimer;
  bool flag = false;
  float heeling;
  float nextWindDir;
  float windSpd;


//TASK SCHEDULER
typedef struct t  {
    unsigned long tStart;
    unsigned long tTimeout;
};

t t_func1 = {0, 200}; //Run every 200ms
t t_func2 = {0, 200}; //Run every 1 seconds.

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

float stationKeepTime, wqMeasureTime;
bool stationKeeping = false;

char controlStrategy = 'h';
float headingControlDistance;

void setup() {
  pinMode(34, INPUT);
  pinMode(35, INPUT);
  pinMode(36, INPUT);
  
  movementControl = new BoatControl(5,0.5);
  //movementControl = new BoatControl(2,0.2);
  //movementControl = new BoatControl(2,1);

  movementControl->initThruster();
  //delay(5000);
  
  desiredDistance = 5;
  headingControlDistance = 15;

  experiment_reitoria();
  //angles_test();
  //experiment_tst();
  //experiment1();
  //experiment2();

  
  sensors = new SensorManager();
  Serial.begin(9600);
  Serial1.begin(115200);
}

void experiment_reitoria(){
  setWaypoint(-5.839327, -35.201395);
  setWaypoint(-5.839559, -35.201395);
  /*setWaypoint(-5.839327, -35.201395);
  setWaypoint(-5.839559, -35.201395);
  setWaypoint(-5.839327, -35.201395);
  setWaypoint(-5.839573, -35.201287);*/
}

void experiment_tst(){
  setWaypoint(-5.842024, -35.197436);
  setWaypoint(-5.842048, -35.196799);
}

void angles_test(){
  float lon_inc = 0.0002;
  float lat_inc = 0.0002;
  float lon_ini = -35.197389;
  float lat_ini = -5.842879;
  //lat = y
  //lon = x
  
  //0º
  setWaypoint(lat_ini + lat_inc, lon_ini);
  //45º
  setWaypoint(lat_ini + lat_inc, lon_ini + lon_inc);
  //90º
  setWaypoint(lat_ini, lon_ini + lon_inc);
  //135º
  setWaypoint(lat_ini - lat_inc, lon_ini + lon_inc);
  //180º
  setWaypoint(lat_ini - lat_inc, lon_ini);
  //-135º
  setWaypoint(lat_ini - lat_inc, lon_ini - lon_inc);
  //-90º
  setWaypoint(lat_ini, lon_ini - lon_inc);
  //-45º
  setWaypoint(lat_ini + lat_inc, lon_ini - lon_inc);
  
}

//-5.842868, -35.196047

void experiment1(){
  //add waypoints example:
  //waypoint 1
  setWaypoint(-5.76494, -35.20434);
  //waypoint 2
  setWaypoint(-5.76479, -35.20462);
  //waypoint 3
  setWaypoint(-5.76467, -35.20411);
}

void experiment2(){
  setWaypoint(-5.766648, -35.209942);
}

void loop() {

  // program flow:
  // check the availability of the sensors (inside libraries) --> OdometrySensors.isWorking() gps.isWorking(); compass.isWorking();
  // recieve a target position
  // adjust rudder and thruster accordingly
  // store boat state (position, velocity, orientation, actuators position, wind velocity, wind direction)
  // check if the desired point was achieved
  // if positive, go to next target point

  
  while (1) {
//    channel[0] = pulseIn(34, HIGH);
//    channel[1] = pulseIn(35, HIGH);
//    channel[2] = pulseIn(36, HIGH);
    Serial.println("tst");
    sensors->readFromSerial();
    sensors->printState();
    
    if (tCheck(&t_func1)) {      
      //sensors->sendStateToBase();
      
      //sensors->printState();
      
      //printLocation();
      
      tRun(&t_func1);
    }
    
    // waypoints control
    if (waypoints.size() != 0) {
      //changeControlStrategy();
      if (distanceToTarget < desiredDistance) {
          waypoints_id += 1;
          waypoints_id = waypoints_id % waypoints.size(); 
      }

      currentLocation = sensors->getGPS().location;
      nextLocation = waypoints.at(waypoints_id);

      //printLocation();

      // change control stragey with distance to target
      /*if (controlStrategy == 'h'){
        movementControl->rudderHeadingControl(sensors, nextLocation);
      } else if (controlStrategy == 'v'){
        movementControl->rudderVelocityControl(sensors, nextLocation);
      }*/
      
      //movementControl->rudderHeadingControl(sensors, nextLocation);
      //movementControl->thrusterControl(sensors, nextLocation);
      //movementControl->thrusterControl(sensors);

      if(channel[0] < 1500){
        if(currentLocation.latitude != 0 && currentLocation.longitude != 0){
          movementControl->rudderHeadingControl(sensors, nextLocation);
        }
        //movementControl->thrusterControl(sensors, nextLocation);
        movementControl->thrusterControlWind(sensors);
        sensors->setAutoPilot(1);
      } else {
        sensors->setAutoPilot(0);
        movementControl->thrusterRCControl(sensors, channel[1]);
        movementControl->rudderRCControl(sensors, channel[2]);
      }
      
      // keep track of distance to target
      lastDistanciaDestino = distanceToTarget;
      distanceToTarget = navigationFunc.findDistance(currentLocation, nextLocation);
      distanceTravelled += navigationFunc.findDistance(lastLocation, currentLocation);

      // in case the boat isnt getting closer to the desired target
      //bugCheck();

      sensors->setWaypointId(waypoints_id);
      
      lastLocation = currentLocation;
    }
  }
}

void changeControlStrategy(){
  if (distanceToTarget < headingControlDistance){
    controlStrategy = 'h';
  } else {
    controlStrategy = 'v';
  }
}

void printLocation(){
      Serial.print("MeasureTime: ");
      Serial.print(millis() - stationKeepTime); Serial.print("  ");
      Serial.print("Current: ");
      Serial.print(currentLocation.latitude, 6); Serial.print("  ");
      Serial.print(currentLocation.longitude, 6); Serial.print("---");
      Serial.print("Next: ");
      Serial.print(nextLocation.latitude, 6); Serial.print("  ");
      Serial.print(nextLocation.longitude, 6); Serial.print("---");
      Serial.print("Distance: "); 
      Serial.print(distanceToTarget); Serial.print("---");
      Serial.print("Waypoint: "); 
      Serial.print(waypoints_id); Serial.print("---");
      Serial.print("Waypoint Size: "); 
      Serial.println(waypoints.size());
}

void setWaypoint(float latitude, float longitude){
  tempLocation.latitude = latitude;
  tempLocation.longitude = longitude;
  waypoints.push_back(tempLocation);
}
