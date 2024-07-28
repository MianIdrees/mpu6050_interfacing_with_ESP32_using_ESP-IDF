/********************************************************************************************
 * Project: MPU6050 ESP32 Sensor Interface
 * Author: Muhammad Idrees
 * 
 * Description:
 * This header file defines the quaternion structure and functions for quaternion-based 
 * angle estimation. It provides an interface for initializing, updating, and retrieving 
 * quaternion-based roll, pitch, and yaw.
 * 
 * Author's Background:
 * Name: Muhammad Idrees
 * Degree: Bachelor's in Electrical and Electronics Engineering
 * Institution: Institute of Space Technology, Islamabad
 * 
 * License:
 * Written by Muhammad Idrees, this header file supports quaternion calculations in the 
 * MPU6050 interface project. You are encouraged to use and adapt the code with credit 
 * to the original author.
 * 
 * Key Features:
 * - Quaternion structure and math functions.
 * - Interfaces for roll, pitch, and yaw computation.
 * 
 * Date: [28/7/2024]
 ********************************************************************************************/



#ifndef QUATERNIONS_H
#define QUATERNIONS_H

#include <math.h>

// Quaternion structure
typedef struct {
    float w;
    float x;
    float y;
    float z;
} Quaternion;

// Function prototypes
void quaternion_init(Quaternion* q);
void quaternion_update(Quaternion* q, float gx, float gy, float gz, float ax, float ay, float az, float dt);
float quaternion_get_roll(const Quaternion* q);
float quaternion_get_pitch(const Quaternion* q);
float quaternion_get_yaw(const Quaternion* q);

#endif // QUATERNIONS_H

