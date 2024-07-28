/********************************************************************************************
 * Project: MPU6050 ESP32 Sensor Interface
 * Author: Muhammad Idrees
 * 
 * Description:
 * This header file declares the functions required for roll and pitch calculations using
 * complementary filters. It provides the necessary prototypes for initializing and updating
 * angle calculations.
 * 
 * Author's Background:
 * Name: Muhammad Idrees
 * Degree: Bachelor's in Electrical and Electronics Engineering
 * Institution: Institute of Space Technology, Islamabad
 * 
 * License:
 * This header file is part of the MPU6050 interface project authored by Muhammad Idrees.
 * It is intended for educational purposes and may be used with acknowledgment of the author.
 * 
 * Key Features:
 * - Complementary filter setup and update functions.
 * 
 * Date: [28/7/2024]
 ********************************************************************************************/



#ifndef ROLL_PITCH_H
#define ROLL_PITCH_H

#include "driver/i2c.h"
#include "esp_err.h"

// Function prototypes
void roll_pitch_init(void);
void roll_pitch_update(float accel_x, float accel_y, float accel_z, float gyro_x, float gyro_y, float gyro_z);
float roll_get(void);
float pitch_get(void);

#endif // ROLL_PITCH_H

