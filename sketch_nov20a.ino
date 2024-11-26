#include <DHT.h>
#include <Wire.h>
#include "rgb_lcd.h"
#include <Adafruit_NeoPixel.h>

// define Arduino Pins
#define trigPin 4
#define echoPin 5
#define DHTPIN 3
#define DHTTYPE DHT22
#define BUZZER_PIN 6
#define NEOPIXEL_PIN 2
#define NUMPIXELS 8

// Initialize objects: LCD Screen, DHT-22, Neopixel Stick 8
rgb_lcd lcd;
DHT dht(DHTPIN, DHTTYPE);
Adafruit_NeoPixel pixels(NUMPIXELS, NEOPIXEL_PIN);

unsigned long previousMillis = 0;
unsigned long displayMillis = 0;
unsigned long closeStartMillis = 0;
unsigned long distanceTimeout = 0;
unsigned long blinkMillis = 0; // Frequency at which the LCD screen blinks during the temperature and humidity alarm
int countdown = 3600; // 60 minutes count down on the Pomodoro Clock (formal mode)
bool inPomodoro = false;
bool isBlinking = false;

// In formal mode, it is difficult to test the changes of the Pixels in 60 minutes, so I set up an 8-minute test version
// Variables of the test mode
bool testMode = false; // Test mode is turned off by default
const int testCountdown = 480;   // 8 minutes count down on the Pomodoro Clock (test mode)

// Set LCD flashing interval 300ms
const int blinkInterval = 300;


void setup() {
    lcd.begin(16, 2);
    lcd.setRGB(0, 0, 255);
    lcd.print("Initializing...");
    delay(2000);

    dht.begin();
    pixels.setBrightness(20);
    pixels.begin();

    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    pinMode(BUZZER_PIN, OUTPUT);
    Serial.begin(9600);

// true: Enables the test mode
// false: Officially test
    testMode = true;

}

void loop() {
    unsigned long currentMillis = millis();

    if (currentMillis - displayMillis >= 1000) {
        displayMillis = currentMillis;
        float distance = getDistance();
        Serial.print("Distance in cm: ");
        Serial.println(distance);

        if (!inPomodoro && distance > 10) {
            displayTempHumidity();
            closeStartMillis = 0;
        } else if (distance <= 10) {
            if (closeStartMillis == 0) {
                closeStartMillis = currentMillis;
                pixels.clear();
            }
            if (currentMillis - closeStartMillis >= 3000 && !inPomodoro) {
                startPomodoro();
            }
        } else {
            closeStartMillis = 0;
        }
    }

    if (inPomodoro) {
        pomodoroLogic();
    }
}


float getDistance() {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    long duration = pulseIn(echoPin, HIGH);
    return 34400 * duration / 2000000.0;
}

void displayTempHumidity() {
    float temperature = dht.readTemperature(false);
    float humidity = dht.readHumidity(false);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Temp: ");
    lcd.print(temperature);
    lcd.print(" C");

    lcd.setCursor(0, 1);
    lcd.print("Humidity: ");
    lcd.print(humidity);
    lcd.print("%");

    if (temperature > 30 || temperature < 0 || humidity > 60 || humidity < 25) {
        //The LCD screen flashes red
        if (millis() - blinkMillis >= blinkInterval) {
            blinkMillis = millis();
            isBlinking = !isBlinking;
            lcd.setRGB(isBlinking ? 255 : 0, 0, 0);
        }
    } else {
        lcd.setRGB(0, 0, 255);
    }
}

void startPomodoro() {
    inPomodoro = true;

    // Choose between 60 minutes or 8 minutes according to two modes
    countdown = testMode ? testCountdown : countdown; 
    //countdown = 3600; // count down on 60min

    lcd.clear();
    lcd.setRGB(0, 0, 255);
    displayPomodoro(); // Show initial status
    clearAndLightUpPixels(); 

    updatePixels();
    
    Serial.println(testMode ? "Test mode: 8 minutes" : "Normal mode: 60 minutes");

}

// Clear the previous state and light all Pixels
void clearAndLightUpPixels() {
    pixels.clear();
    for (int i = 0; i < NUMPIXELS; i++) {
        pixels.setPixelColor(i, 255, 255, 0);
    }
    pixels.show();
}

void stopPomodoro(bool success) {
    inPomodoro = false;
    countdown = 0;
    pixels.clear();
    pixels.show();

    lcd.clear();

    if (success) {
        // When the countdown successfully end, "Success!" will display, and the LCD screen flashes green.
        lcd.print("Success!");
        lcd.setCursor(0, 1);
        lcd.print("Perseverance prevails!");

        for (int i = 0; i < 10; i++) {
            lcd.setRGB(0, 255, 0);
            delay(250);
            lcd.setRGB(0, 0, 0);
            delay(250);
        }
    } else {
        // If the task fails, the screen flashes yellow and displays "Task Fail. Work harder!"
        lcd.print("Task Fail");
        lcd.setCursor(0, 1);
        lcd.print("Work harder!");

        for (int i = 0; i < 6; i++) {
            lcd.setRGB(255, 255, 0);
            delay(500);
            lcd.setRGB(0, 0, 0);
            delay(500);
        }
    }

    // Restore the default blue background color
    lcd.clear();
    lcd.setRGB(0, 0, 255);
    // When the blinking is complete, reset the temperature and humidity monitoring mode
    displayTempHumidity();
}


void pomodoroLogic() {
    float distance = getDistance();

    if (distance > 10) {
        if (distanceTimeout == 0) distanceTimeout = millis();
        if (millis() - distanceTimeout > 10000) {
            stopPomodoro(false);
        } else {
            emergencyAlert();
        }
    } else {
        distanceTimeout = 0;
        countdownLogic();
    }
}

void countdownLogic() {
    if (millis() - previousMillis >= 1000) {
        previousMillis = millis();
        countdown--;

        displayPomodoro();
        updatePixels();

        if (countdown <= 0) stopPomodoro(true);   // success!
    }
}

void displayPomodoro() {
    float temperature = dht.readTemperature(false);
    float humidity = dht.readHumidity(false);

    lcd.setCursor(0, 0);
    lcd.print("Temp:");
    lcd.print(temperature, 1);
    lcd.print(" Hum:");
    lcd.print(humidity, 1);
    lcd.setCursor(0, 1);
    lcd.print("Time:");
    lcd.print(countdown / 60);
    lcd.print(":");
    if (countdown % 60 < 10) lcd.print("0");
    lcd.print(countdown % 60);

// When the temperature and humidity exceed the threshold, the LCD screen blinks red
    if (temperature > 30 || temperature < 0 || humidity > 60 || humidity < 25) {
        if (millis() - blinkMillis >= blinkInterval) {
            blinkMillis = millis();
            isBlinking = !isBlinking;
            lcd.setRGB(isBlinking ? 255 : 0, 0, 0); 
        }
    } else {
        lcd.setRGB(0, 0, 255); // default blue background color
    }

}

void updatePixels() {

    int totalDuration = testMode ? testCountdown : 3600; // Select the total duration based on two modes

    // Count the number of segments that have passed 7.5 minutes
    int segmentsPassed = (3600 - countdown) / 450; // 60 min
    int segmentsPassed2 = (480 - countdown) / 60; // 8 min

    int sp = testMode ? segmentsPassed2 : segmentsPassed; 

    // Count the number of lights that should be turned on
    int lightsToKeepOn = NUMPIXELS - sp; // Subtract the number of segments that have passed from the total

    // Make sure lightsToKeepOn is never less than 0
    if (lightsToKeepOn < 0) {
        lightsToKeepOn = 0;
    }

    pixels.clear();
    for (int i = 0; i < lightsToKeepOn; i++) {
      // Light up lights that need to be kept
        pixels.setPixelColor(i, 255, 255, 0);
    }
    pixels.show();
}


void emergencyAlert() {
    pixels.clear();
    for (int i = 0; i < NUMPIXELS; i++) {
        pixels.setPixelColor(i, 255, 0, 0);
    }
    pixels.show();
    tone(BUZZER_PIN, 500);
    delay(500);
    noTone(BUZZER_PIN);
}
