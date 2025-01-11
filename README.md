# CASA0016 —— PomodoZone

<div style="display: flex; justify-content: space-between;">
  <img src="https://github.com/hml1688/CASA0016---Sensor-Systems---Assignment/blob/main/Images/device%20display2.jpg" alt="device display2" style="width: 280px; height: 220px;">
  <img src="https://github.com/hml1688/CASA0016---Sensor-Systems---Assignment/blob/main/Images/device%20display1.jpg" alt="device display1" style="width: 220px; height: 220px;">
  <img src="https://github.com/hml1688/CASA0016---Sensor-Systems---Assignment/blob/main/Images/Success%20interface.jpg" alt="success" style="width: 320px; height: 220px;">
</div>

## Project Overview



## Background & Inspiration

## Detail Instructions

<img src="https://github.com/hml1688/CASA0016---Sensor-Systems---Assignment/blob/main/Images/flow%20chart.jpg" alt="flow chart" style="width: 280px; height: auto;">

This device has two modes —— Environment Monitoring mode and Pomodoro Timer mode.

**1. Environment Monitoring (Basic Mode)**
<div style="display: flex; justify-content: space-between;">
  <img src="https://github.com/hml1688/CASA0016---Sensor-Systems---Assignment/blob/main/Images/temperature%26humidity.jpg" alt="tem&hunidity" style="width: 260px; height: auto;">
  <img src="https://github.com/hml1688/CASA0016---Sensor-Systems---Assignment/blob/main/Images/humidity%20sensor.gif" alt="humidity alert" style="width: 250px; height: auto;">
</div>
<br>
This device continuously monitors temperature and humidity using the DHT-22 sensor, and displays their specific values on the screen. If these values exceed predefined ranges (temperature between 0°C and 30°C, humidity between 25% and 60%), the device alerts users by flashing a red light, encouraging them to adjust their environment for better focus.  

<br> **2. Pomodoro Timer**

The Neopixel stick 8 provides a visual countdown, the LCD screen shows the remaining time.  
  Check the phone's position every second, if it disappears ---> the Pixel stick flashes red + a buzzer sounds.  
  When the phone disappears more than 10s, fail ---> the LCD Screen flashes yellow and displays "Task Fail! Work harder!"  
  When the countdown ends sucessfully ---> the LCD Screen turns green, flashes for 5 seconds and displays "Success! Good Job!"
  
## Equipment

(1) Arduino Uno  
(2) LCD Screen  
(3) DHT-22 Temperature and Humidity sensor  
(4) Ultrasonic rangefinder  
(5) Neopixel stick 8  
(6) PKM 22EPP-40 buzzer  

## Architecture




### 2. Two Functions:  
#### (1) Basic Mode (Environment Monitoring):
Assesses temperature and humidity every second.
Display: LCD Screen  
#### (2) Focus Timer Mode:
The Neopixel stick 8 provides a visual countdown, the LCD screen shows the remaining time.  
  Check the phone's position every second, if it disappears ---> the Pixel stick flashes red + a buzzer sounds.  
  When the phone disappears more than 10s, fail ---> the LCD Screen flashes yellow and displays "Task Fail! Work harder!"  
  When the countdown ends sucessfully ---> the LCD Screen turns green, flashes for 5 seconds and displays "Success! Good Job!"

