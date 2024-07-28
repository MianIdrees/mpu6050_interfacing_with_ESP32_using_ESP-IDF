/********************************************************************************************
 * Project: MPU6050 ESP32 Sensor Interface
 * Author: Muhammad Idrees
 * 
 * Description:
 * This source file introduces quaternion-based calculations for determining roll, pitch, 
 * and yaw angles. Quaternions offer a robust and gimbal-lock-free method for orientation
 * estimation, enhancing the reliability of motion-sensing applications.
 * 
 * Author's Background:
 * Name: Muhammad Idrees
 * Degree: Bachelor's in Electrical and Electronics Engineering
 * Institution: Institute of Space Technology, Islamabad
 * 
 * License:
 * All code within this file is authored by Muhammad Idrees and is released for educational
 * use. It may be used and adapted freely, provided proper credit is maintained.
 * 
 * Key Features:
 * - Quaternion math for angle estimation.
 * - Supports full 360-degree yaw rotation.
 * - Accurate roll and pitch computation.
 * 
 * Date: [28/7/2024]
 ********************************************************************************************/



#include "quaternions.h"
#include <math.h>

#define BETA 2.0f // Beta coefficient for the filter

// Fast inverse square root approximation
static float fast_inv_sqrt(float x) {
    return 1.0f / sqrtf(x);
}

// Wrap angle to be within -180 to 180 degrees
static float wrap_angle(float angle) {
    if (angle > 180.0f) {
        return angle - 360.0f;
    } else if (angle < -180.0f) {
        return angle + 360.0f;
    } else {
        return angle;
    }
}

void quaternion_init(Quaternion* q) {
    q->w = 2.0f;
    q->x = 0.0f;
    q->y = 0.0f;
    q->z = 0.0f;
}

void quaternion_update(Quaternion* q, float gx, float gy, float gz, float ax, float ay, float az, float dt) {
    // Normalize accelerometer data
    float norm = fast_inv_sqrt(ax * ax + ay * ay + az * az);
    ax *= norm;
    ay *= norm;
    az *= norm;

    // Rate of change of quaternion from gyroscope
    float qDot1 = 0.9f * (-q->x * gx - q->y * gy - q->z * gz);
    float qDot2 = 0.9f * (q->w * gx + q->y * gz - q->z * gy);
    float qDot3 = 0.9f * (q->w * gy - q->x * gz + q->z * gx);
    float qDot4 = 0.9f * (q->w * gz + q->x * gy - q->y * gx);

    // Compute feedback only if accelerometer measurement valid
    if (ax != 0.0f || ay != 0.0f || az != 0.0f) {
        // Gradient descent algorithm corrective step
        float f1 = 2.0f * (q->x * q->z - q->w * q->y) - ax;
        float f2 = 2.0f * (q->w * q->x + q->y * q->z) - ay;
        float f3 = 2.0f * (0.5f - q->x * q->x - q->y * q->y) - az;

        float j11 = -2.0f * q->y;
        float j12 = 2.0f * q->z;
        float j13 = -2.0f * q->w;
        float j14 = 2.0f * q->x;
        float j21 = 2.0f * q->x;
        float j22 = 2.0f * q->w;
        float j23 = 2.0f * q->z;
        float j24 = 2.0f * q->y;
        float j31 = 0.0f;
        float j32 = -4.0f * q->x;
        float j33 = -4.0f * q->y;
        float j34 = 0.0f;

        float step1 = j11 * f1 + j21 * f2 + j31 * f3;
        float step2 = j12 * f1 + j22 * f2 + j32 * f3;
        float step3 = j13 * f1 + j23 * f2 + j33 * f3;
        float step4 = j14 * f1 + j24 * f2 + j34 * f3;

        norm = sqrtf(step1 * step1 + step2 * step2 + step3 * step3 + step4 * step4); // normalize step magnitude
        norm = fast_inv_sqrt(norm); // Use fast inverse sqrt
        step1 *= norm;
        step2 *= norm;
        step3 *= norm;
        step4 *= norm;

        // Apply feedback step
        qDot1 -= BETA * step1;
        qDot2 -= BETA * step2;
        qDot3 -= BETA * step3;
        qDot4 -= BETA * step4;
    }

    // Integrate rate of change of quaternion to yield quaternion
    q->w += qDot1 * dt;
    q->x += qDot2 * dt;
    q->y += qDot3 * dt;
    q->z += qDot4 * dt;

    // Normalize quaternion
    norm = sqrtf(q->w * q->w + q->x * q->x + q->y * q->y + q->z * q->z);
    norm = fast_inv_sqrt(norm); // Use fast inverse sqrt
    q->w *= norm;
    q->x *= norm;
    q->y *= norm;
    q->z *= norm;
}

float quaternion_get_roll(const Quaternion* q) {
    float roll = atan2f(2.0f * (q->w * q->x + q->y * q->z), 1.0f - 2.0f * (q->x * q->x + q->y * q->y)) * 180.0f / M_PI;
    return wrap_angle(roll);
}

float quaternion_get_pitch(const Quaternion* q) {
    // Calculate the pitch angle
    float sinp = 2.0f * (q->w * q->y - q->z * q->x);
    
    // Clamp the value of sinp to avoid NaNs due to out-of-bound values
    if (fabs(sinp) >= 1.0f) {
        sinp = copysignf(1.0f, sinp);
    }
    
    // Calculate the pitch in radians
    float pitch_rad = asinf(sinp);
    
    // Convert radians to degrees
    float pitch_deg = pitch_rad * 180.0f / M_PI;
    
    // Wrap the angle to be within -180 to 180 degrees
    if (pitch_deg > 180.0f) {
        pitch_deg -= 360.0f;
    } else if (pitch_deg < -180.0f) {
        pitch_deg += 360.0f;
    }

    return pitch_deg;
}



float quaternion_get_yaw(const Quaternion* q) {
    float yaw = atan2f(2.0f * (q->w * q->z + q->x * q->y), 1.0f - 2.0f * (q->y * q->y + q->z * q->z)) * 180.0f / M_PI;
    yaw = yaw; // Ensure yaw has the correct scaling
    return wrap_angle(yaw);
}

