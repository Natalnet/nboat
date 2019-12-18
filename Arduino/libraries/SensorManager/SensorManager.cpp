/*

  SensorManager.cpp - Library for getting curent heading from Compass model HMC6352.
  Created by Davi H. dos Santos, March 25, 2018.
  BSD license, all text above must be included in any redistribution.

*/


#include "Arduino.h"
#include "SensorManager.h"

SensorManager::SensorManager(){
  SD.begin(48);
  pinMode(LED_BUILTIN, OUTPUT); 
}

void SensorManager::readFromSerial(){
  Serial1.begin(115200);
  while(Serial1.available() <= 0){
    Serial1.println("f");
  }
  delay(200);
  if(Serial1.available() > 5){
    call[0] = Serial1.parseFloat();   //lat
    call[1] = Serial1.parseFloat();   //lon
    call[2] = Serial1.parseFloat();   //course
    call[3] = Serial1.parseFloat();   //speed
    call[4] = Serial1.parseFloat();   //altitude

    call[5] = Serial1.parseFloat();   //roll
    call[6] = Serial1.parseFloat();   //pitch
    call[7] = Serial1.parseFloat();   //yaw
    call[8] = Serial1.parseFloat();   //accel_x
    call[9] = Serial1.parseFloat();   //accel_y
    call[10] = Serial1.parseFloat();  //accel_z
    call[11] = Serial1.parseFloat();  //gyro x
    call[12] = Serial1.parseFloat();  //gyro y
    call[13] = Serial1.parseFloat();  //gyro z
    call[14] = Serial1.parseFloat();  //mag x
    call[15] = Serial1.parseFloat();  //mag y
    call[16] = Serial1.parseFloat();  //mag z
    call[17] = Serial1.parseFloat();  //temperature
    call[18] = Serial1.parseFloat();  //pressure
    call[19] = Serial1.parseFloat();  //altitude

    call[20] = Serial1.parseFloat();  //wind dir

    _date = Serial1.parseFloat();     //date
  }
  Serial1.end();
  setGPSData(call[0], call[1], call[2], call[3], call[4], _date);
  setIMUData(call[5], call[6], call[7], call[8], call[9], call[10], call[11], call[12], call[13], call[14], call[15], call[16], call[17], call[18], call[19]);
  setWindData(call[20]);
}

void SensorManager::setGPSData(float lat, float lon, float course, float speed, float altitude, String date){
  _GPSData.location.latitude = lat;
  _GPSData.location.longitude = lon;
  _GPSData.course = course;
  _GPSData.speed = speed;
  _GPSData.altitude = altitude;
  _GPSData.date = date;
}

void SensorManager::setIMUData(float roll, float pitch, float yaw, float accel_x, float accel_y, float accel_z, float gyro_x, float gyro_y, float gyro_z, float mag_x, float mag_y, float mag_z, float temperature, float pressure, float altitude){
  _IMUData.eulerAngles.roll = roll;
  _IMUData.eulerAngles.pitch = pitch;
  _IMUData.eulerAngles.yaw = yaw;
  _IMUData.accel_x = accel_x;
  _IMUData.accel_y = accel_y;
  _IMUData.accel_z = accel_z;
  _IMUData.gyro_x = gyro_x;
  _IMUData.gyro_y = gyro_y;
  _IMUData.gyro_z = gyro_z;
  _IMUData.mag_x = mag_x;
  _IMUData.mag_y = mag_y;
  _IMUData.mag_z = mag_z;
  _IMUData.temperature = temperature;
  _IMUData.pressure = pressure;
  _IMUData.altitude = altitude;
}

void SensorManager::setWindData(float windDir){
  _windData.direction = windDir;
}

GPSData SensorManager::getGPS(){
  return _GPSData;
}

Pose SensorManager::getMagnetometer(){
//  return magnetometer1.get();
}

float SensorManager::getCompass(){
 // return compass1.getHeading();
}

WindData SensorManager::getWind(){
  return _windData;
}

IMUData SensorManager::getIMU(){
  return _IMUData;
}

void SensorManager::setThrusterPower(float thrusterPower){
  _thrusterPower = thrusterPower;
}

void SensorManager::setRudderAngle(float rudderAngle){
  _rudderAngle = rudderAngle;
}

void SensorManager::setWindSpeed(float windSpeed){
  _windData.speed = windSpeed;
}

void SensorManager::setTack(bool isTack){
  _isTack = isTack;
}

void SensorManager::setWaypointId(int waypointId){
  _waypointId = waypointId;
}

void SensorManager::setAutoPilot(int autoPilot){
  _autoPilot = autoPilot;
}

//posição (lat, lon), velocidade do vento (direção, speed), posição dos atuadores (leme, vela), velocidade (speed) e orientação do gps (course), orientação da bussola (heading), informações do IMU (R, P, Y).
void SensorManager::logState(){

//_GPSData.location.latitude != 0 && _GPSData.location.longitude != 0 && 
  if (gpsDateCtrl == 0) {
    _experimentName = String(_GPSData.date+".csv");
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
      dataFile.print(_GPSData.dateFull);                  dataFile.print(",");
      dataFile.print(timeStamp, 2);                         dataFile.print(",");
      dataFile.print(_GPSData.location.latitude, 6);      dataFile.print(",");
      dataFile.print(_GPSData.location.longitude, 6);     dataFile.print(",");
      dataFile.print(_windData.direction, 2);              dataFile.print(",");
      dataFile.print(_windData.speed, 2);                   dataFile.print(",");
      dataFile.print(_rudderAngle, 2);                      dataFile.print(",");
      dataFile.print(_thrusterPower, 2);                    dataFile.print(",");
      dataFile.print(_GPSData.course, 2);                 dataFile.print(",");
      dataFile.print(_GPSData.speed, 2);                  dataFile.print(",");
      dataFile.print(_IMUData.eulerAngles.yaw, 2);       dataFile.print(",");
      dataFile.print(_IMUData.eulerAngles.pitch, 2);     dataFile.print(",");
      dataFile.print(_IMUData.eulerAngles.roll, 2);      dataFile.print(",");
      dataFile.print(_IMUData.heading, 2);               dataFile.print(",");
      dataFile.print(_IMUData.temperature, 2);           dataFile.print(",");      
      dataFile.print(_IMUData.pressure, 2);              dataFile.print(",");
      dataFile.print(_IMUData.altitude, 2);              dataFile.print(",");
      dataFile.print(_IMUData.accel_x, 2);               dataFile.print(",");
      dataFile.print(_IMUData.accel_y, 2);               dataFile.print(",");
      dataFile.print(_IMUData.accel_z, 2);               dataFile.print(",");
      dataFile.print(_IMUData.gyro_x, 2);                dataFile.print(",");
      dataFile.print(_IMUData.gyro_y, 2);                dataFile.print(",");
      dataFile.print(_IMUData.gyro_z, 2);                dataFile.print(",");
      dataFile.print(_IMUData.mag_x, 2);                 dataFile.print(",");
      dataFile.print(_IMUData.mag_y, 2);                 dataFile.print(",");
      dataFile.print(_IMUData.mag_x, 2);                 dataFile.print(",");
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

void SensorManager::printState()
{
  Serial.print(_GPSData.dateFull); 
 	Serial.print(" ");
	Serial.print(_GPSData.location.latitude, 6);
	Serial.print(" ");
	Serial.print(_GPSData.location.longitude, 6);
	Serial.print(" ");
//	Serial.print(wind.get().direction, 2);
	Serial.print(_windData.direction, 2);
	Serial.print(" ");
	Serial.print(_windData.speed, 2);
	Serial.print(" ");
	Serial.print(_rudderAngle, 2);
	Serial.print(" ");
	Serial.print(_thrusterPower, 2);
	Serial.print(" ");
	Serial.print(_GPSData.course, 2);
	Serial.print(" ");
	Serial.print(_GPSData.speed, 2); 
	Serial.print(" ");
	Serial.print(_IMUData.eulerAngles.yaw, 2);
	Serial.print(" ");
	Serial.print(_IMUData.eulerAngles.pitch, 2);
	Serial.print(" ");
	Serial.print(_IMUData.eulerAngles.roll, 2);
	Serial.print(" ");
	Serial.print(_IMUData.heading, 2);
	Serial.print(" ");
	Serial.println(_waypointId); 
}

void SensorManager::sendStateToBase()
{
  Serial.print("{");
  Serial.print(_GPSData.location.latitude, 6);
  Serial.print(",");
  Serial.print(_GPSData.location.longitude, 6);
  Serial.print(",");
  Serial.print(_IMUData.eulerAngles.yaw, 2);
  Serial.print(",");
  Serial.print(_GPSData.course, 2);
  Serial.print(",");
  Serial.print(_windData.direction, 2);
  Serial.print(",");
  Serial.print(_rudderAngle, 2);
  Serial.print(",");
  Serial.print(_thrusterPower, 2);
  Serial.print(",");
  Serial.print(_GPSData.speed, 2); 
  Serial.print(",");
  Serial.print(_waypointId); 
  Serial.print(",");
  Serial.print(gpsDateCtrl); 
  Serial.print(",");
  Serial.print(_autoPilot); 
  Serial.print("}");
}