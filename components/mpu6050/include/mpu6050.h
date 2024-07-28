#ifndef MPU6050_H
#define MPU6050_H

#include "driver/i2c.h"
#include "esp_err.h"

#define MPU6050_ADDR 0x68

// MPU6050 Register Addresses
#define MPU6050_REG_PWR_MGMT_1   0x6B
#define MPU6050_REG_ACCEL_XOUT_H 0x3B
#define MPU6050_REG_GYRO_XOUT_H  0x43

// Function prototypes
esp_err_t mpu6050_init(i2c_port_t i2c_num);
esp_err_t mpu6050_read_raw_data(i2c_port_t i2c_num, int16_t *accel_x, int16_t *accel_y, int16_t *accel_z, int16_t *gyro_x, int16_t *gyro_y, int16_t *gyro_z);
void mpu6050_convert_accel(int16_t raw_x, int16_t raw_y, int16_t raw_z, float *accel_x, float *accel_y, float *accel_z);
void mpu6050_convert_gyro(int16_t raw_x, int16_t raw_y, int16_t raw_z, float *gyro_x, float *gyro_y, float *gyro_z);
void mpu6050_calibrate(i2c_port_t i2c_num, float *accel_bias, float *gyro_bias);

// Roll and pitch calculation functions
void roll_pitch_init(void);
void roll_pitch_update(float accel_x, float accel_y, float accel_z, float gyro_x, float gyro_y, float gyro_z);
float roll_get(void);
float pitch_get(void);

#endif // MPU6050_H

