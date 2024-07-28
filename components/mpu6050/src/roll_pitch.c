#include "roll_pitch.h"
#include <math.h>

#define GYRO_SCALE 131.0f
#define ACCEL_SCALE 16384.0f
#define GRAVITY 9.8f
#define DT 0.0001f // Time step in seconds

static float roll = 0.0f;
static float pitch = 0.0f;

// Complementary filter coefficients
#define ALPHA 0.7f // The weight for the gyroscope data

void roll_pitch_init(void) {
    roll = 0.0f;
    pitch = 0.0f;
}

void roll_pitch_update(float accel_x, float accel_y, float accel_z, float gyro_x, float gyro_y, float gyro_z) {
    // Calculate roll and pitch from accelerometer data
    float accel_roll = atan2f(accel_y, accel_z) * 180.0f / M_PI;
    float accel_pitch = atan2f(-accel_x, sqrtf(accel_y * accel_y + accel_z * accel_z)) * 180.0f / M_PI;

    // Gyroscope readings in degrees per second
    float roll_rate = gyro_x / GYRO_SCALE;
    float pitch_rate = gyro_y / GYRO_SCALE;

    // Update roll and pitch using gyroscope data
    roll += roll_rate * DT;
    pitch += pitch_rate * DT;

    // Complementary filter to combine accelerometer and gyroscope data
    roll = ALPHA * roll + (1.0f - ALPHA) * accel_roll;
    pitch = ALPHA * pitch + (1.0f - ALPHA) * accel_pitch;
}

float roll_get(void) {
    return roll;
}

float pitch_get(void) {
    return pitch;
}

