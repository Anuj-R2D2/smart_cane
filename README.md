# Smart Cane Project

## Overview  
An assistive smart cane for visually impaired users. It uses ultrasonic sensors to detect obstacles within 40 cm and vibrates the handle to alert the user. Includes fall detection with MPU6050 and buzzer alerts.

## Components  
- ESP32  
- HC-SR04 Ultrasonic sensor  
- MPU6050 accelerometer and gyroscope  
- Vibration motor  
- Buzzer  

## Features  
- Obstacle detection within 40 cm  
- Vibration alert on obstacle detection  
- Fall detection alert via buzzer  
- SOS messaging planned (future upgrade)  

## Code  
See the `Code/` folder for Arduino sketches.

## Notes  
Calibration may be required for MPU6050 thresholds.
