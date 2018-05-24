/*
 * Code associated to the circuit schematic in https://github.com/Natalnet/nboat/blob/sailboat_mini/sailboatSchematics.fzz
 */

#include "SensorManager.h"
#include "SailboatControl.h"
#include "Navigation.h"
#include <medianFilter.h>

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


//INSTANTIATING LIBS
  SailboatControl *movementControl;
  SensorManager *sensors;
  WindData wind;
  Navigation sailboatNavigation;


//WAYPOINTS SETUP
  vector<Location> waypoints, tackWaypoints;
  Location nextLocation, lastLocation, currentLocation, tempLocation;
  int waypoints_id, waypointsT_id, bugManager;
  float startTime, endTime, travelledDistance, distanceToTarget = 999999, lastDistanceToTarget, desiredDistance, timeInterval;
  double distanceTravelled;
  bool isTacking;
  
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

void setup() {
  movementControl = new SailboatControl(1,0);
  desiredDistance = 10;

  //add waypoints
  //experiment1();
  testExperiment();

  sensors = new SensorManager();
  
  Serial.begin(9600);

  //pinMode(2, INPUT_PULLUP);
  pinMode(2, INPUT_PULLUP);
  //attachInterrupt(0, rpm_fan, FALLING);
  attachInterrupt(0, wSpeedIRQ, FALLING);
  //interrupts();
  testTimer = millis();
}

void experiment1(){
  setWaypoint(-5.76458, -35.20402);
  setWaypoint(-5.76502, -35.20439);
  setWaypoint(-5.76462, -35.20442);
}

void testExperiment(){
  setWaypoint(-5.842880, -35.197379);
  setWaypoint(-5.841493, -35.197436);
}


void loop() {

  // program flow:
  // initialize and check the availability of the sensors (inside libraries) --> Odometrysensors->isWorking() gps.isWorking(); compass.isWorking();
  // recieve a target position
  // adjust rudder and sail accordingly
  // store sailboat state (gps info, imu info, actuators position, wind velocity, wind direction, batery charge)
  // check if the desired point was achieved
  // if positive, go to next target point

  while (1) {
    // run sensors->read() at 10Hz
    sensors->read();
    sensors->setTack(isTacking);

    if (tCheck(&t_func2)){
      windSpd = get_wind_speed();
      sensors->setWindSpeed(windSpd);
      tRun(&t_func2);
    }    
    //sensors->setWindSpeed(mps);
    
    if (tCheck(&t_func1)) {
      
      sensors->logState();
      
      //sensors->printState();

      //printLocation();

      /*Serial.print("wind clicks: "); Serial.print(windClickNo); Serial.print("----");
      Serial.print("windspeed: "); Serial.println(windSpd);*/
      
      tRun(&t_func1);
    }
    
    // waypoints control
    if (waypoints.size() != 0) {
      if (distanceToTarget < desiredDistance) {
        if (isTacking) {
          if (waypointsT_id < tackWaypoints.size() - 1) {
            waypointsT_id += 1;
            nextLocation = tackWaypoints.at(waypointsT_id);
          } else {
            isTacking = false;
            waypointsT_id = 0;
            flag = true;
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

      currentLocation = sensors->getGPS().location;
      
      // adjust rudder and thruster power accordingly
      movementControl->rudderHeadingControl(sensors, nextLocation);
      //movementControl->rudderVelocityControl(sensors, nextLocation);
      movementControl->sailControl(sensors);

      // keep track of distance to target
      lastDistanceToTarget = distanceToTarget;
      distanceToTarget = sailboatNavigation.findDistance(currentLocation, nextLocation);
      travelledDistance += sailboatNavigation.findDistance(lastLocation, currentLocation);
      
      // in case the boat isnt getting closer to the desired target
      bugCheck();     

      // check if it needs to tack
      tack();
      
      lastLocation = currentLocation;
    }
  }
}

void tack(){
  wind = sensors->getWind();
  heeling = wind.direction + sensors->getIMU().eulerAngles.yaw;
  nextWindDir = fabs(heeling) - fabs(sailboatNavigation.findHeading(currentLocation, nextLocation));
  
  if (nextWindDir < 30 && !isTacking) {
    isTacking = true;
    tackWaypoints = sailboatNavigation.findTackingPoints(sensors, lastLocation, nextLocation);
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
  windSpeed = windSpeed/10;
  //windSpeed *= 0.15;                               //Calculates the actual wind speed in mph (2 * 1.492 = 2.984mph)    
  return(windSpeed);
}

void wSpeedIRQ()
{
  if (!millis()-lastWindIRQ<10)                      //Debounce the wind interrupt switch for 10ms after contact
  {
    lastWindIRQ = millis();                          //Set up last wind interrupt for the next interrupt
    windClickNo++;                                   //Each click per second is 1.492MPH
  }
}

void readWindSpeed(){
    detachInterrupt(0);//Disable interrupt when calculating
    revolutions=Filter.run(revolutions);
    rpm = revolutions * 120; // Convert frequency to RPM, note: 60 works for one interruption per full rotation. For two interrupts per full rotation use half_revolutions * 30.
    revolutions = 0; // Restart the RPM counter
    attachInterrupt(0, rpm_fan, FALLING); //enable interrupt
    mps = 2*3.14*radius*rpm / 60;
    mps = mps * 0.3; // calibration factor for anemometer accuracy, adjust as necessary
    mps = mps/2;
}

void rpm_fan() {
  revolutions++;
}

void setWaypoint(float latitude, float longitude){
  tempLocation.latitude = latitude;
  tempLocation.longitude = longitude;
  waypoints.push_back(tempLocation);
}

void printLocation(){
      Serial.print("MeasureTime: ");
      Serial.print(millis() - testTimer); Serial.print("  ");
      Serial.print("Current: ");
      Serial.print(currentLocation.latitude, 6); Serial.print(", ");
      Serial.print(currentLocation.longitude, 6); Serial.print("---");
      Serial.print("Next: ");
      Serial.print(nextLocation.latitude, 6); Serial.print(", ");
      Serial.print(nextLocation.longitude, 6); Serial.print("---");
      Serial.print("Distance: "); 
      Serial.print(distanceToTarget); Serial.print("---");
      Serial.print("Waypoint: "); 
      Serial.print(waypoints_id); Serial.print("---");
      Serial.print("WaypointTack: "); 
      Serial.print(waypointsT_id); Serial.print("---");
      Serial.print("Waypoint Size: "); 
      Serial.println(tackWaypoints.size());
}

void bugCheck(){
      if(distanceToTarget >= lastDistanceToTarget){
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
      if(timeInterval > 20000){
        distanceToTarget = 0; //TODO generate error message
        startTime = millis();
      }
}
