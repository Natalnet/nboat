/*

  SensorManagerNano.cpp - Library for getting curent heading from Compass model HMC6352.
  Created by Davi H. dos Santos, March 25, 2018.
  BSD license, all text above must be included in any redistribution.

*/


#include "Arduino.h"
#include "SensorManagerNano.h"

SensorManagerNano::SensorManagerNano(){
  SD.begin(48);
  imu1 = new IMU_GY80();
}

//TODO
bool SensorManagerNano::checkSensors(){
}

void SensorManagerNano::read(){
  gps1.read();
  //compass1.read();
  wind.read();
  //magnetometer1.read();
  imu1->read();
}

void SensorManagerNano::readImu(){
  imu1->read();
}

//posição (lat, lon), velocidade do vento (direção, speed), posição dos atuadores (leme, vela), velocidade (speed) e orientação do gps (course), orientação da bussola (heading), informações do IMU (R, P, Y).
void SensorManagerNano::logState(){

//gps1.get().location.latitude != 0 && gps1.get().location.longitude != 0 && 
  if (gpsDateCtrl == 0) {
    _experimentName = String(gps1.get().date+".csv");
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
      dataFile.print(gps1.get().dateFull);                  dataFile.print(",");
      dataFile.print(timeStamp, 2);                         dataFile.print(",");
      dataFile.print(gps1.get().location.latitude, 6);      dataFile.print(",");
      dataFile.print(gps1.get().location.longitude, 6);     dataFile.print(",");
      dataFile.print(wind.get().direction, 2);              dataFile.print(",");
      dataFile.print(_windData.speed, 2);                   dataFile.print(",");
      dataFile.print(_rudderAngle, 2);                      dataFile.print(",");
      dataFile.print(_thrusterPower, 2);                    dataFile.print(",");
      dataFile.print(gps1.get().course, 2);                 dataFile.print(",");
      dataFile.print(gps1.get().speed, 2);                  dataFile.print(",");
      dataFile.print(imu1->get().eulerAngles.yaw, 2);       dataFile.print(",");
      dataFile.print(imu1->get().eulerAngles.pitch, 2);     dataFile.print(",");
      dataFile.print(imu1->get().eulerAngles.roll, 2);      dataFile.print(",");
      dataFile.print(imu1->get().heading, 2);               dataFile.print(",");
      dataFile.print(imu1->get().temperature, 2);           dataFile.print(",");      
      dataFile.print(imu1->get().pressure, 2);              dataFile.print(",");
      dataFile.print(imu1->get().altitude, 2);              dataFile.print(",");
      dataFile.print(imu1->get().accel_x, 2);               dataFile.print(",");
      dataFile.print(imu1->get().accel_y, 2);               dataFile.print(",");
      dataFile.print(imu1->get().accel_z, 2);               dataFile.print(",");
      dataFile.print(imu1->get().gyro_x, 2);                dataFile.print(",");
      dataFile.print(imu1->get().gyro_y, 2);                dataFile.print(",");
      dataFile.print(imu1->get().gyro_z, 2);                dataFile.print(",");
      dataFile.print(imu1->get().mag_x, 2);                 dataFile.print(",");
      dataFile.print(imu1->get().mag_y, 2);                 dataFile.print(",");
      dataFile.print(imu1->get().mag_x, 2);                 dataFile.print(",");
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

void SensorManagerNano::printState()
{
  Serial.print(gps1.get().dateFull); 
 	Serial.print(" ");
	Serial.print(gps1.get().location.latitude, 6);
	Serial.print(" ");
	Serial.print(gps1.get().location.longitude, 6);
	Serial.print(" ");
//	Serial.print(wind.get().direction, 2);
	Serial.print(wind.getDirectionSigned(), 2);
	Serial.print(" ");
	Serial.print(_windData.speed, 2);
	Serial.print(" ");
	Serial.print(_rudderAngle, 2);
	Serial.print(" ");
	Serial.print(_thrusterPower, 2);
	Serial.print(" ");
	Serial.print(gps1.get().course, 2);
	Serial.print(" ");
	Serial.print(gps1.get().speed, 2); 
	Serial.print(" ");
	Serial.print(imu1->get().eulerAngles.yaw, 2);
	Serial.print(" ");
	Serial.print(imu1->get().eulerAngles.pitch, 2);
	Serial.print(" ");
	Serial.print(imu1->get().eulerAngles.roll, 2);
	Serial.print(" ");
	Serial.print(imu1->get().heading, 2);
	Serial.print(" ");
	Serial.println(_waypointId); 
}

void SensorManagerNano::sendStateToMaster()
{
  Serial.println(gps1.get().location.latitude, 6);
  Serial.println(gps1.get().location.longitude, 6);
  Serial.println(imu1->get().eulerAngles.yaw, 2);
  Serial.println(gps1.get().course, 2);
  Serial.println(gps1.get().speed, 2);
  Serial.println(wind.getDirectionSigned(), 2);
  Serial.println(float(gpsDateCtrl), 2);
}
