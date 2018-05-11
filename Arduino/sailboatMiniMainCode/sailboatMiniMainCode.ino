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
int waypoints_id, waypointsT_id, bugHandler;
float startTime, endTime, travelledDistance, distanceToTarget, lastDistanceToTarget, desiredDistance, timeInterval;
bool isTacking;


//TASK SCHEDULER
typedef struct t  {
    unsigned long tStart;
    unsigned long tTimeout;
};

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

  experiments1();

  sensors = new SensorManager();
  
  Serial.begin(9600);

  //pinMode(2, INPUT_PULLUP);
  attachInterrupt(0, rpm_fan, FALLING);
  //attachInterrupt(0, wSpeedIRQ, FALLING);
  //interrupts();
}

void experiment1(){
  //add waypoints example:
  //waypoint 1
  tempLocation.latitude = -5.764525;
  tempLocation.longitude = -35.204070;
  waypoints.push_back(tempLocation);
  
  //waypoint 2
  tempLocation.latitude = -5.765012;
  tempLocation.longitude = -35.204357;
  waypoints.push_back(tempLocation);

  //waypoint 3
  tempLocation.latitude = -5.764724;
  tempLocation.longitude = -35.204472;
  waypoints.push_back(tempLocation);
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
    readWindSpeed();
    sensors->setWindSpeed(mps);
    //float tst = get_wind_speed();
    //sensors->setWindSpeed(tst);
    if (tCheck(&t_func1)) {
      sensors->logState();
      //sensors->printState();
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
        startTime = millis();
      }
           
      lastLocation = currentLocation;

       // check if it needs to tack
      wind = sensors->getWind();
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
}

void rpm_fan() {
  revolutions++;
}
