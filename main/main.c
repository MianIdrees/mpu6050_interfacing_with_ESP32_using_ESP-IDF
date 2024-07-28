#include <stdio.h>
#include "driver/i2c.h"
#include "esp_log.h"
#include "mpu6050.h"
#include "roll_pitch.h"
#include "quaternions.h"

#define I2C_MASTER_SCL_IO    22 // SCL pin
#define I2C_MASTER_SDA_IO    21 // SDA pin
#define I2C_MASTER_FREQ_HZ   400000
#define I2C_MASTER_NUM       I2C_NUM_0
#define ESP_INTR_FLAG_DEFAULT 0

void app_main(void) {
    esp_err_t ret;
    int16_t accel_x, accel_y, accel_z;
    int16_t gyro_x, gyro_y, gyro_z;
    float accel_x_g, accel_y_g, accel_z_g;
    float gyro_x_dps, gyro_y_dps, gyro_z_dps;
    float accel_bias[3] = {0.00f, 0.00f, 0.00f};
    float gyro_bias[3] = {0.00f, 0.00f, 0.00f};

    // Initialize I2C
    i2c_config_t conf = {
        .mode = I2C_MODE_MASTER,
        .sda_io_num = I2C_MASTER_SDA_IO,
        .sda_pullup_en = GPIO_PULLUP_ENABLE,
        .scl_io_num = I2C_MASTER_SCL_IO,
        .scl_pullup_en = GPIO_PULLUP_ENABLE,
        .master.clk_speed = I2C_MASTER_FREQ_HZ,
    };
    ret = i2c_param_config(I2C_MASTER_NUM, &conf);
    if (ret != ESP_OK) {
        ESP_LOGE("I2C", "I2C param config failed");
        return;
    }
    ret = i2c_driver_install(I2C_MASTER_NUM, conf.mode, 0, 0, ESP_INTR_FLAG_DEFAULT);
    if (ret != ESP_OK) {
        ESP_LOGE("I2C", "I2C driver install failed");
        return;
    }

    // Initialize MPU6050
    ret = mpu6050_init(I2C_MASTER_NUM);
    if (ret != ESP_OK) {
        ESP_LOGE("MPU6050", "Initialization failed");
        return;
    }

    // Calibrate the MPU6050
    mpu6050_calibrate(I2C_MASTER_NUM, accel_bias, gyro_bias);
    ESP_LOGI("MPU6050", "Calibration complete");

    // Initialize roll and pitch calculations
    roll_pitch_init();

    // Initialize Quaternion
    Quaternion q;
    quaternion_init(&q);

    while (1) {
        // Read raw data
        ret = mpu6050_read_raw_data(I2C_MASTER_NUM, &accel_x, &accel_y, &accel_z, &gyro_x, &gyro_y, &gyro_z);
        if (ret != ESP_OK) {
            ESP_LOGE("MPU6050", "Read failed");
            return;
        }

        // Convert raw data to physical values
        mpu6050_convert_accel(accel_x, accel_y, accel_z, &accel_x_g, &accel_y_g, &accel_z_g);
        mpu6050_convert_gyro(gyro_x, gyro_y, gyro_z, &gyro_x_dps, &gyro_y_dps, &gyro_z_dps);

        // Update roll and pitch
        roll_pitch_update(accel_x_g, accel_y_g, accel_z_g, gyro_x_dps, gyro_y_dps, gyro_z_dps);

        // Update Quaternion
        quaternion_update(&q, gyro_x_dps, gyro_y_dps, gyro_z_dps, accel_x_g, accel_y_g, accel_z_g, 0.01f); // 10 ms time step

        // Print results
        printf("Accel: X=%0.2f m/s^2, Y=%0.2f m/s^2, Z=%0.2f m/s^2\n", accel_x_g, accel_y_g, accel_z_g);
        printf("Gyro: X=%0.2f deg/s, Y=%0.2f deg/s, Z=%0.2f deg/s\n", gyro_x_dps, gyro_y_dps, gyro_z_dps);
        printf("Roll: %0.2f degrees\n", roll_get());
        printf("Pitch: %0.2f degrees\n", pitch_get());

        // Print Quaternion-based Roll, Pitch, Yaw
        printf("Quaternion Roll: %0.2f degrees\n", quaternion_get_roll(&q));
        printf("Quaternion Pitch: %0.2f degrees\n", quaternion_get_pitch(&q));
        printf("Quaternion Yaw: %0.2f degrees\n", quaternion_get_yaw(&q));

        vTaskDelay(200 / portTICK_PERIOD_MS);
    }
}

