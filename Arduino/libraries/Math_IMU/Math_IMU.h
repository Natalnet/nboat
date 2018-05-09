/*

  Math_IMU.h - Library for getting curent heading from Compass HMC6352.
  Created by Davi H. dos Santos, March 25, 2018.
  BSD license, all text above must be included in any redistribution.

*/

#ifndef Math_IMU_h
#define Math_IMU_h

#include "Arduino.h"
#include "Wire.h"

class Math_IMU
{
  public:
     Math_IMU();
     void get();
 
  private:
    void Math_IMU::init_rotation_matrix(float m[3][3], float yaw, float pitch, float roll);
    void Math_IMU::Matrix_Vector_Multiply(const float a[3][3], const float b[3], float out[3]);
    void Math_IMU::Matrix_Multiply(const float a[3][3], const float b[3][3], float out[3][3]);
    void Math_IMU::Vector_Add(float out[3], const float v1[3], const float v2[3]);
    void Math_IMU::Vector_Scale(float out[3], const float v[3], float scale);
    void Math_IMU::Vector_Cross_Product(float out[3], const float v1[3], const float v2[3]);
    float Vector_Dot_Product(const float v1[3], const float v2[3]);
    void Math_IMU::Euler_angles(void);
    void Math_IMU::Matrix_update(void);
    void Math_IMU::Drift_correction(void);
    void Math_IMU::Normalize(void);
    void Math_IMU::Compass_Heading();
};

#endif
