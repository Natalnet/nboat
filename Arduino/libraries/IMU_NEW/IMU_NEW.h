/*

  IMU_NEW.h - Library for getting curent heading from Compass HMC6352.
  Created by Davi H. dos Santos, March 25, 2018.
  BSD license, all text above must be included in any redistribution.

*/

#ifndef IMU_NEW_h
#define IMU_NEW_h

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

// SENSOR CALIBRATION
/*****************************************************************/
// How to calibrate? Read the tutorial at http://dev.qu.tu-berlin.de/projects/sf-razor-9dof-ahrs
// Put MIN/MAX and OFFSET readings for your board here!
// Accelerometer
// "accel x,y,z (min/max) = X_MIN/X_MAX  Y_MIN/Y_MAX  Z_MIN/Z_MAX"
#define ACCEL_X_MIN (-250.0f)
#define ACCEL_X_MAX (255.0f)
#define ACCEL_Y_MIN (-275.0f)
#define ACCEL_Y_MAX (235.0f)
#define ACCEL_Z_MIN (-269.0f)
#define ACCEL_Z_MAX (228.0f)

// Magnetometer
// "magn x,y,z (min/max) = X_MIN/X_MAX  Y_MIN/Y_MAX  Z_MIN/Z_MAX"
/*
#define MAGN_X_MIN (-542.0f)
#define MAGN_X_MAX (-47.0f)
#define MAGN_Y_MIN (-421.0f)
#define MAGN_Y_MAX (75.0f)
#define MAGN_Z_MIN (-178.0f)
#define MAGN_Z_MAX (260.0f)
*/

#define MAGN_X_MIN (-547.0f)
#define MAGN_X_MAX (-75.0f)
#define MAGN_Y_MIN (-421.0f)
#define MAGN_Y_MAX (61.0f)
#define MAGN_Z_MIN (-217.0f)
#define MAGN_Z_MAX (259.0f)

// Gyroscope
// "gyro x,y,z (current/average) = .../OFFSET_X  .../OFFSET_Y  .../OFFSET_Z
/*
#define GYRO_AVERAGE_OFFSET_X (3.9f)
#define GYRO_AVERAGE_OFFSET_Y (-1.7f)
#define GYRO_AVERAGE_OFFSET_Z (6.25f)
*/

#define GYRO_AVERAGE_OFFSET_X (3.0f)
#define GYRO_AVERAGE_OFFSET_Y (-2.0f)
#define GYRO_AVERAGE_OFFSET_Z (3.67f)

// Sensor calibration scale and offset values
#define ACCEL_X_OFFSET ((ACCEL_X_MIN + ACCEL_X_MAX) / 2.0f)
#define ACCEL_Y_OFFSET ((ACCEL_Y_MIN + ACCEL_Y_MAX) / 2.0f)
#define ACCEL_Z_OFFSET ((ACCEL_Z_MIN + ACCEL_Z_MAX) / 2.0f)
#define ACCEL_X_SCALE (GRAVITY / (ACCEL_X_MAX - ACCEL_X_OFFSET))
#define ACCEL_Y_SCALE (GRAVITY / (ACCEL_Y_MAX - ACCEL_Y_OFFSET))
#define ACCEL_Z_SCALE (GRAVITY / (ACCEL_Z_MAX - ACCEL_Z_OFFSET))

#define MAGN_X_OFFSET ((MAGN_X_MIN + MAGN_X_MAX) / 2.0f)
#define MAGN_Y_OFFSET ((MAGN_Y_MIN + MAGN_Y_MAX) / 2.0f)
#define MAGN_Z_OFFSET ((MAGN_Z_MIN + MAGN_Z_MAX) / 2.0f)
#define MAGN_X_SCALE (100.0f / (MAGN_X_MAX - MAGN_X_OFFSET))
#define MAGN_Y_SCALE (100.0f / (MAGN_Y_MAX - MAGN_Y_OFFSET))
#define MAGN_Z_SCALE (100.0f / (MAGN_Z_MAX - MAGN_Z_OFFSET))

// Gain for gyroscope
#define GYRO_GAIN 0.06957 // Same gain on all axes
#define GYRO_SCALED_RAD(x) (x * TO_RAD(GYRO_GAIN)) // Calculate the scaled gyro readings in radians per second

// DCM parameters
#define Kp_ROLLPITCH (0.02f)
#define Ki_ROLLPITCH (0.00002f)
#define Kp_YAW (1.2f)
#define Ki_YAW (0.00002f)

// Stuff
#define GRAVITY (256.0f) // "1G reference" used for DCM filter and accelerometer calibration
#define TO_RAD(x) (x * 0.01745329252)  // *pi/180
#define TO_DEG(x) (x * 57.2957795131)  // *180/pi


// Altymeter
#define ALT_SEA_LEVEL_PRESSURE 102133

// Sensor I2C addresses
#define ACCEL_ADDRESS ((int) 0x53) // 0x53 = 0xA6 / 2
#define MAGN_ADDRESS  ((int) 0x1E) // 0x1E = 0x3C / 2
#define GYRO_ADDRESS  ((int) 0x68) // 0x68 = 0xD0 / 2

// Arduino backward compatibility macros
#define WIRE_SEND(b) Wire.write((byte) b) 
#define WIRE_RECEIVE() Wire.read() 


class IMU_NEW
{
  public:
    IMU_NEW();
    void IMU_NEW::read();
    IMUData IMU_NEW::get();

  private:
    void IMU_NEW::Read_Pressure();
    void IMU_NEW::Pressure_Init();
    void IMU_NEW::Read_Gyro_Accel_Temp();
    void IMU_NEW::Gyro_Accel_Temp_Init();
    void IMU_NEW::Read_Gyro();
    void IMU_NEW::Gyro_Init();
    void IMU_NEW::Read_Magn();
    void IMU_NEW::Magn_Init();
    void IMU_NEW::Read_Accel();
    void IMU_NEW::Accel_Init();
    void IMU_NEW::I2C_Init();
    void IMU_NEW::init_rotation_matrix(float m[3][3], float yaw, float pitch, float roll);
    void IMU_NEW::Matrix_Multiply(float a[3][3], float b[3][3],float mat[3][3]);
    void IMU_NEW::Vector_Add(float vectorOut[3], float vectorIn1[3], float vectorIn2[3]);
    void IMU_NEW::Vector_Scale(float vectorOut[3], float vectorIn[3], float scale2);
    void IMU_NEW::Vector_Cross_Product(float vectorOut[3], float v1[3], float v2[3]);
    float IMU_NEW::Vector_Dot_Product(float vector1[3], float vector2[3]);
    void IMU_NEW::Euler_angles(void);
    void IMU_NEW::Matrix_update(void);
    void IMU_NEW::Drift_correction(void);
    void IMU_NEW::Normalize(void);
    void IMU_NEW::Compass_Heading();
    void IMU_NEW::ApplySensorMapping();
    void IMU_NEW::reset_sensor_fusion();
    void IMU_NEW::read_sensors();
    void IMU_NEW::compensate_sensor_errors();
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
    
    //SensorManager sensors;
    
    // DCM variables
    float MAG_Heading;
    float Magn_Vector[3]= {0, 0, 0}; // Store the magnetometer turn rate in a vector
    float Accel_Vector[3]= {0, 0, 0}; // Store the acceleration in a vector
    float Gyro_Vector[3]= {0, 0, 0}; // Store the gyros turn rate in a vector
    float Omega_Vector[3]= {0, 0, 0}; // Corrected Gyro_Vector data
    float Omega_P[3]= {0, 0, 0}; // Omega Proportional correction
    float Omega_I[3]= {0, 0, 0}; // Omega Integrator
    float Omega[3]= {0, 0, 0};
    float errorRollPitch[3] = {0, 0, 0};
    float errorYaw[3] = {0, 0, 0};
    float DCM_Matrix[3][3] = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
    float Update_Matrix[3][3] = {{0, 1, 2}, {3, 4, 5}, {6, 7, 8}};
    float Temporary_Matrix[3][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
  
    // Euler angles
    float yaw, pitch, roll;
    
    // DCM timing in the main loop
    long timestamp;
    long timestamp_old;
    float G_Dt; // Integration time for DCM algorithm
    
    // More output-state variables
    int num_accel_errors = 0;
    int num_magn_errors = 0;
    int num_gyro_errors = 0;
    
    L3G4200D gyroscope;
    Adafruit_BMP085 press;
    IMUData _imuData;

    float yaw_OFFSET = 118.4, pitch_OFFSET = -3.2, roll_OFFSET = 1.0;
    float yawWFrame, pitchWFrame, rollWFrame;
  
};

#endif

