/*

  IMU_GY80Nano.h - Library for getting curent heading from Compass HMC6352.
  Created by Davi H. dos Santos, March 25, 2018.
  BSD license, all text above must be included in any redistribution.

*/

#ifndef IMU_GY80Nano_h
#define IMU_GY80Nano_h

#include "Arduino.h"
#include "IMUData.h"
#include <L3G4200D.h>
#include <Adafruit_BMP085.h>
#include "Wire.h"

// Set your serial port baud rate used to send out data here!
#define OUTPUT_BAUD_RATE 115200

// Sensor data output interval in milliseconds
// This may not work, if faster than 20ms (=50Hz)
// Code is tuned for 20ms, so better leave it like that
#define OUTPUT_DATA_INTERVAL 20  // in milliseconds

// Altymeter
#define ALT_SEA_LEVEL_PRESSURE 102133

// Sensor I2C addresses
#define ACCEL_ADDRESS ((int) 0x53) // 0x53 = 0xA6 / 2
#define MAGN_ADDRESS  ((int) 0x1E) // 0x1E = 0x3C / 2
#define GYRO_ADDRESS  ((int) 0x68) // 0x68 = 0xD0 / 2

// Arduino backward compatibility macros
#define WIRE_SEND(b) Wire.write((byte) b) 
#define WIRE_RECEIVE() Wire.read() 


class IMU_GY80Nano
{
  public:
    IMU_GY80Nano();
    void IMU_GY80Nano::read();
    IMUData IMU_GY80Nano::get();

  private:
    void IMU_GY80Nano::Read_Pressure();
    void IMU_GY80Nano::Pressure_Init();
    void IMU_GY80Nano::Read_Gyro();
    void IMU_GY80Nano::Gyro_Init();
    void IMU_GY80Nano::Read_Magn();
    void IMU_GY80Nano::Magn_Init();
    void IMU_GY80Nano::Read_Accel();
    void IMU_GY80Nano::Accel_Init();
    void IMU_GY80Nano::I2C_Init();
    void IMU_GY80Nano::read_sensors();
    float adjustFrame(float angle);
    
    // RAW sensor data
    float accel[3];  // Actually stores the NEGATED acceleration (equals gravity, if board not moving).
    //float accel_min[3];
    //float accel_max[3];
    
    float magnetom[3];
    //float magnetom_min[3];
    //float magnetom_max[3];
    
    float gyro[3];
    //float gyro_average[3];
    //int gyro_num_samples = 0;
    
    float temperature;
    float pressure;
    float altitude;

    int num_accel_errors = 0;
    int num_magn_errors = 0;
    
    L3G4200D gyroscope;
    Adafruit_BMP085 press;
    IMUData _imuData;  
};

#endif

