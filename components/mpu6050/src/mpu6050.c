/********************************************************************************************
 * Project: MPU6050 ESP32 Sensor Interface
 * Author: Muhammad Idrees
 * 
 * Description:
 * This source file implements the functions required to interface with the MPU6050 sensor
 * using the ESP32. It handles sensor initialization, data reading, and conversion to 
 * physical units, along with calibration functions to correct sensor biases.
 * 
 * Author's Background:
 * Name: Muhammad Idrees
 * Degree: Bachelor's in Electrical and Electronics Engineering
 * Institution: Institute of Space Technology, Islamabad
 * 
 * License:
 * This code is created solely by Muhammad Idrees for educational and research purposes.
 * Redistribution and use in source and binary forms, with or without modification, are 
 * permitted provided that the above author information and this permission notice appear 
 * in all copies.
 * 
 * Key Features:
 * - I2C communication setup for MPU6050.
 * - Raw data acquisition and conversion.
 * - Calibration functions for accurate readings.
 * 
 * Date: [28/7/24]
 ********************************************************************************************/




/// mpu6050.c code starts 
#include "mpu6050.h"

#define ACCEL_SCALE 16384.0f // for ±2g range
#define GYRO_SCALE 131.0f // for ±250°/s range
#define GRAVITY 9.8f // m/s²

static float accel_bias[3] = {1.12f, -0.30f, -0.55f}; // Biases for accel X, Y, Z
static float gyro_bias[3] = {-0.27f, 0.24f, 0.16f}; // Biases for gyro X, Y, Z

esp_err_t mpu6050_init(i2c_port_t i2c_num) {
    uint8_t data = 0;
    esp_err_t ret;

    // Wake up the MPU6050
    data = 0x00; // Clear sleep bit
    ret = i2c_master_write_to_device(i2c_num, MPU6050_ADDR, &data, 1, 1000 / portTICK_PERIOD_MS);
    if (ret != ESP_OK) {
        return ret;
    }
    
    // Set to default settings if needed, e.g., set accelerometer and gyroscope configurations
    // Example: Set accelerometer to ±2g and gyroscope to ±250°/s

    return ESP_OK;
}

esp_err_t mpu6050_read_raw_data(i2c_port_t i2c_num, int16_t *accel_x, int16_t *accel_y, int16_t *accel_z, int16_t *gyro_x, int16_t *gyro_y, int16_t *gyro_z) {
    uint8_t data[14];
    esp_err_t ret;
    uint8_t reg_addr = MPU6050_REG_ACCEL_XOUT_H;

    // Write the register address to the device
    ret = i2c_master_write_to_device(i2c_num, MPU6050_ADDR, &reg_addr, 1, 1000 / portTICK_PERIOD_MS);
    if (ret != ESP_OK) {
        return ret;
    }

    // Read the data from the device
    ret = i2c_master_read_from_device(i2c_num, MPU6050_ADDR, data, sizeof(data), 1000 / portTICK_PERIOD_MS);
    if (ret != ESP_OK) {
        return ret;
    }

    *accel_x = (data[0] << 8) | data[1];
    *accel_y = (data[2] << 8) | data[3];
    *accel_z = (data[4] << 8) | data[5];
    *gyro_x  = (data[8] << 8) | data[9];
    *gyro_y  = (data[10] << 8) | data[11];
    *gyro_z  = (data[12] << 8) | data[13];

    return ESP_OK;
}

void mpu6050_convert_accel(int16_t raw_x, int16_t raw_y, int16_t raw_z, float *accel_x, float *accel_y, float *accel_z) {
    *accel_x = ((raw_x / ACCEL_SCALE) * GRAVITY) - accel_bias[0];
    *accel_y = ((raw_y / ACCEL_SCALE) * GRAVITY) - accel_bias[1];
    *accel_z = ((raw_z / ACCEL_SCALE) * GRAVITY) - accel_bias[2];
}

void mpu6050_convert_gyro(int16_t raw_x, int16_t raw_y, int16_t raw_z, float *gyro_x, float *gyro_y, float *gyro_z) {
    *gyro_x = (raw_x / GYRO_SCALE) - gyro_bias[0];
    *gyro_y = (raw_y / GYRO_SCALE) - gyro_bias[1];
    *gyro_z = (raw_z / GYRO_SCALE) - gyro_bias[2];
}

void mpu6050_calibrate(i2c_port_t i2c_num, float *accel_bias, float *gyro_bias) {
    int16_t accel_x, accel_y, accel_z;
    int16_t gyro_x, gyro_y, gyro_z;
    float accel_x_g, accel_y_g, accel_z_g;
    float gyro_x_dps, gyro_y_dps, gyro_z_dps;
    float accel_x_sum = 0.0f, accel_y_sum = 0.0f, accel_z_sum = 0.0f;
    float gyro_x_sum = 0.0f, gyro_y_sum = 0.0f, gyro_z_sum = 0.0f;
    int samples = 100;

    for (int i = 0; i < samples; i++) {
        mpu6050_read_raw_data(i2c_num, &accel_x, &accel_y, &accel_z, &gyro_x, &gyro_y, &gyro_z);
        mpu6050_convert_accel(accel_x, accel_y, accel_z, &accel_x_g, &accel_y_g, &accel_z_g);
        mpu6050_convert_gyro(gyro_x, gyro_y, gyro_z, &gyro_x_dps, &gyro_y_dps, &gyro_z_dps);

        accel_x_sum += accel_x_g;
        accel_y_sum += accel_y_g;
        accel_z_sum += accel_z_g;
        gyro_x_sum += gyro_x_dps;
        gyro_y_sum += gyro_y_dps;
        gyro_z_sum += gyro_z_dps;

        //vTaskDelay(5 / portTICK_PERIOD_MS);
    }

    // Compute biases
    accel_bias[0] = accel_x_sum / samples;
    accel_bias[1] = accel_y_sum / samples;
    accel_bias[2] = accel_z_sum / samples - GRAVITY; // Gravity should be considered for Z-axis

    gyro_bias[0] = gyro_x_sum / samples;
    gyro_bias[1] = gyro_y_sum / samples;
    gyro_bias[2] = gyro_z_sum / samples;
}
/// mpu6050.c code ends 


