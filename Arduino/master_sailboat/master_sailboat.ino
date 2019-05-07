#include <Wire.h>
#include "SensorManager.h"
#include "Navigation.h"
#include "SailboatControl.h"
double channel[3];

//recebe sinal do rádio
//mapeia para ângulo de leme e vela
//esse é o ângulo desejado
//envia angulo por i2c pros servos

//leme -> aileron -> direito esq-dir -> porta 3
//vela -> trotle -> esquerdo cima-baixo -> porta 2

//INSTATIATING LIBS
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
  
  pinMode(2, INPUT); //vela
  pinMode(3, INPUT); //leme
  pinMode(13, INPUT); //gear (controle de automático/manual

  sensors = new SensorManager();

  Serial.begin(9600);

  //delay(5000);

  Wire.begin();
}

void loop() {
  //lê sinal do rádio
  sensors->read();
  channel[0] = pulseIn(2, HIGH); //canal da vela
  channel[1] = pulseIn(3, HIGH); //canal do leme
  channel[2] = pulseIn(13, HIGH);

  double gear = channel[2];

  
  if (tCheck(&t_func1)) {
      sensors->logState();
      sensors->sendState(); 
      //sensors->printState();
      
      tRun(&t_func1);
    }

  //controle manual
  if(gear > 1500){
    
    //mapeia de sinal de rádio para ângulo do leme
    int theta_s = map(channel[0], 1093, 1887, 0, 90);
    int theta_r = map(channel[1],  2088, 894, -90, 90);
    
    //envia ângulo desejado pro arduino uno do leme
    send_wire(map(theta_r, -90, 90, 0, 179), 8); //mapeamento pra poder enviar byte
  
    //envia ângulo desejado pro arduino uno da vela
    send_wire(theta_s, 10);

  //controle automático
  } else {
    auto_control();
  }
}

void send_wire(int theta, int address){
  Wire.beginTransmission(address);           // transmit to device #8
  Wire.write(theta);   // sends one byte
  Wire.endTransmission();                    // stop transmitting
}

void auto_control(){
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
    
    // adjust rudder and sail accordingly
    if(currentLocation.latitude != 0 && currentLocation.longitude != 0){
      movementControl->rudderHeadingControl(sensors, nextLocation);
    }
    //movementControl->rudderVelocityControl(sensors, nextLocation);
    movementControl->sailControl(sensors);

    // keep track of distance to target
    lastDistanceToTarget = distanceToTarget;
    distanceToTarget = sailboatNavigation.findDistance(currentLocation, nextLocation);
    travelledDistance += sailboatNavigation.findDistance(lastLocation, currentLocation);
    
    // in case the boat isnt getting closer to the desired target
    //bugCheck();     

    // check if it needs to tack
    tack();
    
    sensors->setWaypointId(waypoints_id);
    
    lastLocation = currentLocation;
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
