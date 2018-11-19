#include "GPS_EM506.h"
#include "WindSensor.h"
#include "IMU_GY80.h"
#include <SD.h>


//LOG VARIABLES
//float _batCharge;
File dataFile;
bool gpsDateCtrl = 0;
String _experimentName;
float timeStamp = 0;
float _startTime, _endTime;
float _rudderAngle = 0;
float _thrusterPower = 0;
int _autoPilot = 1;
float _waypointId = 0;


//INSTATIATING LIBS
GPS_EM506 gps;
IMU_GY80 *imu;
WindSensor wind;

char t;


void setup() {
  imu = new IMU_GY80();
  Serial.begin(500000);
}

void loop() {
  readSensors();
  logState();
}

void readSensors(){
  gps.read();
  wind.read();
  imu->read();
}

void sendStateToMaster(char f)
{
  if(f == 'f'){
    Serial.println(gps.get().location.latitude, 6);
    Serial.println(gps.get().location.longitude, 6);
    Serial.println(gps.get().course, 2);
    Serial.println(gps.get().speed, 2);
    Serial.println(gps.get().altitude, 2);
  
    Serial.println(imu->get().eulerAngles.roll, 2);
    Serial.println(imu->get().eulerAngles.pitch, 2);
    Serial.println(imu->get().eulerAngles.yaw, 2);
    Serial.flush();
  }

  if(f == 'g'){
    Serial.println(imu->get().accel_x, 2);
    Serial.println(imu->get().accel_y, 2);
    Serial.println(imu->get().accel_z, 2);
    Serial.println(imu->get().gyro_x, 2);
    Serial.println(imu->get().gyro_y, 2);
    Serial.println(imu->get().gyro_z, 2);
    Serial.println(imu->get().mag_x, 2);
    Serial.println(imu->get().mag_y, 2);
    Serial.flush();
  }

  if(f == 'h'){
    Serial.println(imu->get().mag_z, 2);
    Serial.println(imu->get().temperature, 2);
    Serial.println(imu->get().pressure, 2);
    Serial.println(imu->get().altitude, 2);
    Serial.println(wind.getDirectionSigned(), 2);
    Serial.println(gps.get().date);
    Serial.flush();
  }
}

void logState(){

//gps.get().location.latitude != 0 && gps.get().location.longitude != 0 && 
  if (gpsDateCtrl == 0) {
    _experimentName = String(gps.get().date+".csv");
    gpsDateCtrl = 1;
    _startTime = millis();

    dataFile = SD.open(_experimentName, FILE_WRITE);

    //first line of log file
    if (dataFile) {
      Serial.print("LOGGIN...");
      dataFile.print("Date");             dataFile.print(",");
      dataFile.print("TimeStamp");        dataFile.print(",");
      dataFile.print("Latitude");         dataFile.print(",");
      dataFile.print("Longitude");        dataFile.print(",");
      dataFile.print("Wind Direction");   dataFile.print(",");
      dataFile.print("Wind Speed");       dataFile.print(",");
      dataFile.print("Rudder Angle");     dataFile.print(",");
      dataFile.print("Thruster Power");   dataFile.print(",");
      dataFile.print("GPS Course");       dataFile.print(",");
      dataFile.print("GPS Speed");        dataFile.print(",");
      dataFile.print("Yaw");              dataFile.print(",");
      dataFile.print("Pitch");            dataFile.print(",");
      dataFile.print("Roll");             dataFile.print(",");
      dataFile.print("Magnetometer Heading");   dataFile.print(",");
      dataFile.print("Temperature");      dataFile.print(",");
      dataFile.print("Pressure");         dataFile.print(",");
      dataFile.print("Altitude");         dataFile.print(",");
      dataFile.print("Accel_x");          dataFile.print(",");
      dataFile.print("Accel_y");          dataFile.print(",");
      dataFile.print("Accel_z");          dataFile.print(",");
      dataFile.print("Gyro_x");           dataFile.print(",");
      dataFile.print("Gyro_y");           dataFile.print(",");
      dataFile.print("Gyro_z");           dataFile.print(",");
      dataFile.print("Mag_x");            dataFile.print(",");
      dataFile.print("Mag_y");            dataFile.print(",");
      dataFile.print("Mag_z");            dataFile.print(",");
      dataFile.print("Going to waypoint");   dataFile.print(",");
      dataFile.println("Autopilot on?");
      //dataFile.println("Tacking?");
      //digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
    }
    dataFile.close();
  }

  if (gpsDateCtrl == 1){
    dataFile = SD.open(_experimentName, FILE_WRITE);
    if (dataFile) {
      _endTime = millis();
      timeStamp += (_endTime-_startTime)/1000;
      dataFile.print(gps.get().dateFull);                  dataFile.print(",");
      dataFile.print(timeStamp, 2);                         dataFile.print(",");
      dataFile.print(gps.get().location.latitude, 6);      dataFile.print(",");
      dataFile.print(gps.get().location.longitude, 6);     dataFile.print(",");
      dataFile.print(wind.get().direction, 2);              dataFile.print(",");
      dataFile.print(wind.get().speed, 2);                   dataFile.print(",");
      dataFile.print(_rudderAngle, 2);                      dataFile.print(",");
      dataFile.print(_thrusterPower, 2);                    dataFile.print(",");
      dataFile.print(gps.get().course, 2);                 dataFile.print(",");
      dataFile.print(gps.get().speed, 2);                  dataFile.print(",");
      dataFile.print(imu->get().eulerAngles.yaw, 2);       dataFile.print(",");
      dataFile.print(imu->get().eulerAngles.pitch, 2);     dataFile.print(",");
      dataFile.print(imu->get().eulerAngles.roll, 2);      dataFile.print(",");
      dataFile.print(imu->get().heading, 2);               dataFile.print(",");
      dataFile.print(imu->get().temperature, 2);           dataFile.print(",");      
      dataFile.print(imu->get().pressure, 2);              dataFile.print(",");
      dataFile.print(imu->get().altitude, 2);              dataFile.print(",");
      dataFile.print(imu->get().accel_x, 2);               dataFile.print(",");
      dataFile.print(imu->get().accel_y, 2);               dataFile.print(",");
      dataFile.print(imu->get().accel_z, 2);               dataFile.print(",");
      dataFile.print(imu->get().gyro_x, 2);                dataFile.print(",");
      dataFile.print(imu->get().gyro_y, 2);                dataFile.print(",");
      dataFile.print(imu->get().gyro_z, 2);                dataFile.print(",");
      dataFile.print(imu->get().mag_x, 2);                 dataFile.print(",");
      dataFile.print(imu->get().mag_y, 2);                 dataFile.print(",");
      dataFile.print(imu->get().mag_x, 2);                 dataFile.print(",");
      dataFile.print(_waypointId);                          dataFile.print(",");
      dataFile.print(_autoPilot);                           dataFile.print("\n");
      delay(20);
     
      dataFile.close();
      //Serial.println(_endTime-_startTime);
      _startTime = millis();
    } else  {
      gpsDateCtrl = 0;
      dataFile.close();
    }
    dataFile.close();
  }
  dataFile.close();
}
