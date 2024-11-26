# CASA0016---Sensor-Systems---Assignment
## PomodoZone
### 1. Materials:  
(1) Arduino Uno  
(2) LCD Screen  
(3) DHT-22 Temperature and Humidity sensor  
(4) Ultrasonic rangefinder  
(5) Neopixel stick 8  
(6) PKM 22EPP-40 buzzer  
### 2. Two Functions:  
#### (1) Basic Mode (Environment Monitoring):
Assesses temperature and humidity every second.
Display: LCD Screen  
#### (2) Focus Timer Mode:
The Neopixel stick 8 provides a visual countdown, the LCD screen shows the remaining time.  
  Check the phone's position every second, if it disappears ---> the Pixel stick flashes red + a buzzer sounds.  
  When the phone disappears more than 10s, fail ---> the LCD Screen flashes yellow and displays "Task Fail! Work harder!"  
  When the countdown ends sucessfully ---> the LCD Screen turns green, flashes for 5 seconds and displays "Success! Good Job!"

