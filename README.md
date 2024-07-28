MPU6050 ESP32 Sensor Interface Project
Overview
This project provides a comprehensive library for interfacing the MPU6050 sensor with the ESP32 using the ESP-IDF framework. The library facilitates reading and processing acceleration and gyroscope data from the MPU6050 sensor, and provides accurate angle estimation using both traditional methods and quaternion-based computations. The library supports calculating roll, pitch, and yaw angles, offering a robust solution for motion detection and analysis in various applications, such as robotics, drones, and motion-tracking devices.

Features
1. Read Acceleration and Gyroscope Data
Acceleration Data: The library can read raw acceleration data from the MPU6050 sensor, convert it to physical units (m/s²), and apply calibration biases to ensure accuracy.

Gyroscope Data: Similarly, the library reads raw gyroscope data and converts it to degrees per second (°/s), allowing for precise motion detection.

2. Roll and Pitch Calculation (Complementary Filter)
Roll and Pitch: Using a complementary filter, the library calculates roll and pitch angles based on the accelerometer and gyroscope data. This method blends both sensor readings to provide smooth and reliable angle estimates.

Complementary Filter: The complementary filter uses a weighted average to combine the faster gyroscope readings with the more stable accelerometer data, mitigating noise and drift over time.

3. Quaternion-Based Angle Estimation
Quaternion Representation: The library includes quaternion-based calculations for roll, pitch, and yaw angles, providing a more robust and gimbal-lock-free method of orientation estimation.

Full Range of Motion: By using quaternions, the library supports a full range of motion for yaw (0 to 360 degrees) and accurate roll and pitch measurements (-180 to 180 degrees).

Stability and Smoothness: Quaternions help in maintaining stability and smoothness in angle estimation, especially for applications involving 3D motion.

4. I2C Communication with MPU6050
ESP32 I2C Interface: The project employs the ESP32's I2C interface to communicate with the MPU6050 sensor. This setup involves configuring I2C parameters such as clock speed, data and clock pins, and pull-up settings.

Driver Integration: The library utilizes ESP-IDF's I2C driver for seamless communication, ensuring efficient data transfer between the ESP32 and MPU6050.

5. Calibration and Bias Correction
Sensor Calibration: The library includes functions to calibrate the MPU6050, determining biases for accelerometer and gyroscope readings to improve accuracy.

Bias Adjustment: Calibration is crucial for compensating for sensor imperfections and external influences, allowing for more precise measurements.
