# CASA0016 —— PomodoZone

<div style="display: flex; justify-content: space-between;">
  <img src="https://github.com/hml1688/CASA0016---Sensor-Systems---Assignment/blob/main/Images/device%20display2.jpg" alt="device display2" style="width: 280px; height: 220px;">
  <img src="https://github.com/hml1688/CASA0016---Sensor-Systems---Assignment/blob/main/Images/device%20display1.jpg" alt="device display1" style="width: 220px; height: 220px;">
  <img src="https://github.com/hml1688/CASA0016---Sensor-Systems---Assignment/blob/main/Images/Success%20interface.jpg" alt="success" style="width: 320px; height: 220px;">
</div>

## Project Overview

I created this device called PomodoZone using the Arduino Uno, an LCD screen, a DHT-22 sensor, an Ultrasonic rangefinder, a Neopixel stick and a buzzer. It is designed to enhance focus and self-discipline, inspired by the Pomodoro Technique. It serves as both an environment monitor and a Promodoro timer that guides users in setting aside their phones and achieving work in a comfortable and motivating environment.

## Background & Inspiration

The reason why l choose this topic is that in today's fast-paced world, staying focused has become increasingly challenging. On the one hand, research shows that environmental factors significantly affect academic performance. On the other hand, smartphones and digital distractions constantly pull us away from deep work. For example, for me, any change in the environment will make me unable to calm down, and my phone is so interesting that I always want to pick it up and play with it from time to time :(

So to address this problem, my device continuously monitors temperature and humidity data and alerts users when it is time to adjust their environment for better focus. Meanwhile, the user must set their phone aside to start the timer.

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

<div style="display: flex; justify-content: space-between;">
  <img src="https://github.com/hml1688/CASA0016---Sensor-Systems---Assignment/blob/main/Images/Countdown%20interface.jpg" alt="countdown" style="width: 300px; height: auto;">
  <img src="https://github.com/hml1688/CASA0016---Sensor-Systems---Assignment/blob/main/Images/countdown.gif" alt="countdown gif" style="width: 300px; height: auto;">
</div>

<br>

<div style="display: flex; justify-content: space-between;">
  <img src="https://github.com/hml1688/CASA0016---Sensor-Systems---Assignment/blob/main/Images/Success%20interface.jpg" alt="success interface" style="width: 300px; height: auto;">
  <img src="https://github.com/hml1688/CASA0016---Sensor-Systems---Assignment/blob/main/Images/Fail%20interface.jpg" alt="task fail" style="width: 300px; height: auto;">
</div>

<br>

If the user places his phone on the top of the PromodoZone for three seconds, the Timer mode will activated. The screen displays real-time temperature, humidity, and the countdown.  
**(NOTICE: For test and demonstration purposes, l've set the timer to 8 minutes instead of the standard 60 minutes.)**

As time progresses, the Neopixel LEDs gradually turn off, visually indicating the passage of time. And the ultrasonic rangefinder has been detecting whether the phone is properly placed. 

If the phone is picked up during the process of concentration --->  The timer stops, the buzzer sounds, and NeoPixels turn red.  
When the phone disappears more than 10s, the task fails ---> The LCD Screen flashes yellow and displays "Task Fail! Work harder!", then revers to the environmental monitoring mode.  
When the countdown ends successfully ---> the LCD Screen turns green, flashes for 5 seconds and displays "Success! Good Job!"
  
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

