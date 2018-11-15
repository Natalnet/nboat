#include "BoatControl.h"
#include "SensorManager.h"
#include "NavigationFunctions.h"
#include <medianFilter.h>

double channel[3];

//ANEMOMETER SETUP
  medianFilter Filter;
  float radius = 0.055; //m from center pin to middle of cup
  float mps;
  int revolutions = 0;
  int rpm = 0;
  unsigned long lastmillis = 0;
  
  long lastWindIRQ=0;
  long lastWindChk=0;
  long windClickNo=0;


//INSTATIATING LIBS
  BoatControl *movementControl;
  SensorManager *sensors;
  WindData wind;
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
  
  movementControl = new BoatControl(3,0);
  //movementControl = new BoatControl(2,0.2);
  //movementControl = new BoatControl(2,1);
  movementControl->initThruster();
  delay(5000);
  
  desiredDistance = 5;
  headingControlDistance = 15;
  wqMeasureTime = -1;
  wqMeasureTime *= 1000;  //from ms to s

  experiment_reitoria();
  //angles_test();
  //experiment_tst();
  //experiment1();
  //experiment2();
  

  sensors = new SensorManager();
  Serial.begin(9600);
  //initImu();
  //Serial1.begin(9600);
  
  //pinMode(2, INPUT_PULLUP);
  //attachInterrupt(0, rpm_fan, FALLING);
  //attachInterrupt(0, wSpeedIRQ, FALLING);
  //interrupts();
  testTimer = millis();
}

void initImu(){
  float t = millis();
  float t_1;
  while((t_1 - t) > 2000){
    Serial.println("reading IMu");
    sensors->read();
    t_1 = millis();
  }
}

void experiment_reitoria(){
  setWaypoint(-5.839327, -35.201395);
  setWaypoint(-5.839559, -35.201395);
  setWaypoint(-5.839327, -35.201395);
  setWaypoint(-5.839559, -35.201395);
  setWaypoint(-5.839327, -35.201395);
  setWaypoint(-5.839573, -35.201287);
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
    sensors->read();
    channel[0] = pulseIn(34, HIGH);
    channel[1] = pulseIn(35, HIGH);
    channel[2] = pulseIn(36, HIGH);
    //readWindSpeed();

    if (tCheck(&t_func2)){
      windSpd = get_wind_speed();
      sensors->setWindSpeed(windSpd);
      tRun(&t_func2);
    }
    
    if (tCheck(&t_func1)) {
      /*Serial.print("Channel 0 "); Serial.println(channel[0]);
      Serial.print("Channel 1 "); Serial.println(channel[1]);
      Serial.print("Channel 2 "); Serial.println(channel[2]);*/
      sensors->logState();
      sensors->sendState();
      
      //sensors->printState();

      
      
      //printLocation();
      
      tRun(&t_func1);
    }
    
    // waypoints control
    if (waypoints.size() != 0) {
      //changeControlStrategy();
      if (distanceToTarget < desiredDistance) {
        /*if(!stationKeeping){
          stationKeepTime = millis();
          stationKeeping = true;
        }
        if((millis() - stationKeepTime) > wqMeasureTime){*/
          waypoints_id += 1;
          waypoints_id = waypoints_id % waypoints.size(); 
          //stationKeeping = false;
        //}
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
      } else {
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

void wSpeedIRQ()
{
  if (!millis()-lastWindIRQ<10)                      //Debounce the wind interrupt switch for 10ms after contact
  {
    lastWindIRQ = millis();                          //Set up last wind interrupt for the next interrupt
    windClickNo++;                                   //Each click per second is 1.492MPH
  }
}

float get_wind_speed()
{
  float windSpeed = 0;
  float dTime = millis()-lastWindChk;    
  dTime /= 1000.0;                                  //Covert ms to sec    
  windSpeed = (float)windClickNo / dTime;           //3 / 0.750s = 4    
  windClickNo = 0;                                  //Reset and start watching for new wind
  lastWindChk = millis();    
  //windSpeed *= 1.492;                               //Calculates the actual wind speed in mph (2 * 1.492 = 2.984mph)    
  return(windSpeed);
}

void readWindSpeed(){
    if (millis() - lastmillis == 1000) { //Update every one second, this will be equal to reading frequency (Hz).
    detachInterrupt(0);//Disable interrupt when calculating
    
    revolutions=Filter.run(revolutions);
    rpm = revolutions * 120; // Convert frequency to RPM, note: 60 works for one interruption per full rotation. For two interrupts per full rotation use half_revolutions * 30.
    revolutions = 0; // Restart the RPM counter
    lastmillis = millis(); // Update lastmillis
    attachInterrupt(0, rpm_fan, FALLING); //enable interrupt
    mps = 2*3.14*radius*rpm / 60;
    mps = mps * 0.3; // calibration factor for anemometer accuracy, adjust as necessary
  }
  sensors->setWindSpeed(mps);
}

void rpm_fan() {
  revolutions++;
}

void bugCheck(){
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
      
      // if 20 seconds passes and the boat isnt advancing to the target, go to the next one
      if(timeInterval > 10000){
        distanceToTarget = 0; //TODO generate error message
        startTime = millis();
      }
}

void setWaypoint(float latitude, float longitude){
  tempLocation.latitude = latitude;
  tempLocation.longitude = longitude;
  waypoints.push_back(tempLocation);
}
