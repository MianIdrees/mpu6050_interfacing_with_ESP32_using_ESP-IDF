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

