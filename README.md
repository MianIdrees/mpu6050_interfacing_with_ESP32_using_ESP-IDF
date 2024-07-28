# **MPU6050 ESP32 Sensor Interface Project**

---

## Author Information

- **Author**: Muhammad Idrees
- **Email**: [idreesmian6781@gmail.com](mailto:idreesmian6781@gmail.com)
- **Degree**: Bachelor's in Electrical and Electronics Engineering
- **Institution**: Institute of Space Technology, Islamabad

---

## **Overview**

This project provides a comprehensive library for interfacing the MPU6050 sensor with the ESP32 using the ESP-IDF framework. The library facilitates reading and processing acceleration and gyroscope data from the MPU6050 sensor, and provides accurate angle estimation using both traditional methods and quaternion-based computations. The library supports calculating roll, pitch, and yaw angles, offering a robust solution for motion detection and analysis in various applications, such as robotics, drones, and motion-tracking devices.

## Features
### **1. Read Acceleration and Gyroscope Data**
   Acceleration Data: The library can read raw acceleration data from the MPU6050 sensor, convert it to physical units (m/s²), and apply calibration biases to ensure accuracy.

   Gyroscope Data: Similarly, the library reads raw gyroscope data and converts it to degrees per second (°/s), allowing for precise motion detection.

### **2. Roll and Pitch Calculation (Complementary Filter)**
Roll and Pitch: Using a complementary filter, the library calculates roll and pitch angles based on the accelerometer and gyroscope data. This method blends both sensor readings to provide smooth and reliable angle estimates.

  Complementary Filter: The complementary filter uses a weighted average to combine the faster gyroscope readings with the more stable accelerometer data, mitigating noise and drift 
    over time.

### **3. Quaternion-Based Angle Estimation**
Quaternion Representation: The library includes quaternion-based calculations for roll, pitch, and yaw angles, providing a more robust and gimbal-lock-free method of orientation estimation.

  Full Range of Motion: By using quaternions, the library supports a full range of motion for yaw (0 to 360 degrees) and accurate roll and pitch measurements (-180 to 180 degrees).

  Stability and Smoothness: Quaternions help in maintaining stability and smoothness in angle estimation, especially for applications involving 3D motion.

### **4. I2C Communication with MPU6050**
ESP32 I2C Interface: The project employs the ESP32's I2C interface to communicate with the MPU6050 sensor. This setup involves configuring I2C parameters such as clock speed, data and clock pins, and pull-up settings.

  Driver Integration: The library utilizes ESP-IDF's I2C driver for seamless communication, ensuring efficient data transfer between the ESP32 and MPU6050.

### **5. Calibration and Bias Correction**
Sensor Calibration: The library includes functions to calibrate the MPU6050, determining biases for accelerometer and gyroscope readings to improve accuracy.

  Bias Adjustment: Calibration is crucial for compensating for sensor imperfections and external influences, allowing for more precise measurements.



## Main Components and files
### 1) Main Application or example program (main.c)

1)Initializes the I2C interface and MPU6050 sensor.     
2)Manages data acquisition and calls functions for calculating roll, pitch, and yaw.    
3)Outputs sensor readings and calculated angles to the console for real-time monitoring.    

### 2) MPU6050 Component (mpu6050.c, mpu6050.h)

1)Provides functions for initializing and communicating with the MPU6050.      
2)Handles reading of raw data and conversion to physical units.      
3)Includes calibration routines to adjust for sensor biases.    

### 3) Roll and Pitch Calculation (roll_pitch.c, roll_pitch.h)

1)Implements the complementary filter approach for roll and pitch calculations.     
2)Blends accelerometer and gyroscope data to achieve smooth and accurate results.     

### 4) Quaternion Calculations (quaternions.c, quaternions.h)

1)Implements quaternion mathematics for angle estimation.    
2)Provides functions to calculate roll, pitch, and yaw angles using quaternion representations.   



  ## How to Use This Library

To use this library for interfacing the MPU6050 sensor with the ESP32, follow the steps below:

### 1. Clone the Repository

Start by cloning the repository to your local machine:

```bash
git clone https://github.com/MianIdrees/mpu6050_interfacing_with_ESP32_using_ESP-IDF
cd mpu6050_interfacing_with_ESP32_using_ESP-IDF.git
idf.py menuconfig    //configure the board or any other setting like enable i2c
idf.py build
idf.py -p COM5 flash    //change the com port according to yours
idf.py -p COM5 monitor
 ```

## Hardware Setup

To successfully interface the MPU6050 sensor with the ESP32, ensure the following hardware connections and components are in place. This guide will help you set up your hardware correctly.

### Required Components

- **ESP32 Development Board**
- **MPU6050 Sensor Module**
- **Connecting Wires**
- **Breadboard (Optional)**
- **Power Supply (3.3V or 5V, depending on your setup)**

### Pinout Connections

Connect the MPU6050 sensor to the ESP32 as follows:

| **MPU6050 Pin** | **ESP32 Pin** | **Description**               |
|-----------------|---------------|-------------------------------|
| VCC             | 3.3V or 5V    | Power supply for the MPU6050. |
| GND             | GND           | Ground connection.            |
| SDA             | GPIO 21       | I2C Data Line (SDA).          |
| SCL             | GPIO 22       | I2C Clock Line (SCL).         |
| AD0             | GND           | Set I2C address (optional).   |
| INT             | Not Connected | Interrupt pin (optional).     |


### Notes:

- **Power Supply**: The MPU6050 can typically operate at both 3.3V and 5V, but ensure compatibility with your specific module's requirements.
  
- **I2C Address**: The MPU6050's I2C address is determined by the AD0 pin. Connecting it to GND sets the address to `0x68`. If connected to VCC, the address changes to `0x69`.

- **Pull-Up Resistors**: In most setups, pull-up resistors are necessary on the SDA and SCL lines. Many breakout boards include these, but check your module's datasheet to be sure.

- **Interrupt Pin**: The INT pin is optional and can be used for advanced features like interrupt-driven data reads, but it's not required for basic functionality.

### Setting Up the ESP32 and MPU6050

1. **Connect the Pins**: Use the provided pinout connections to wire the MPU6050 to the ESP32 using jumper wires.

2. **Power the Devices**: Ensure that the power supply matches your MPU6050 module's requirements.

3. **Verify Connections**: Double-check all connections to prevent issues like data loss or incorrect readings.

4. **Prepare for Programming**: Once the connections are verified, you can proceed with uploading the code to the ESP32 and monitoring the output.

---

### Conclusion

With the correct hardware setup, you'll be able to take full advantage of the MPU6050 library for the ESP32. This setup provides a stable foundation for reading sensor data and performing accurate motion calculations. For additional assistance or troubleshooting, consult the datasheets of the MPU6050 and ESP32.







