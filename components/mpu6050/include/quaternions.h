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

