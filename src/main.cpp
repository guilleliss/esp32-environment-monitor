#include <Arduino.h>
#include <WiFi.h>
#include <Wire.h>

#include "display.h"
#include "sensor.h"
#include "wifi-server.h"

#define BUTTON_PIN 7

void readAndDisplay();
void readButton();

unsigned long lastRead = 0;
const unsigned long READ_INTERVAL = 2000; // ms

void readAndDisplay()
{
  unsigned long now = millis();
  if (now - lastRead >= READ_INTERVAL)
  {
    lastRead = now;
    readSensor();
    displayValues();
  }
}

void readButton()
{
  static bool lastButtonState = HIGH;
  bool currentButtonState = digitalRead(BUTTON_PIN);

  if (currentButtonState == LOW)
  {
    displayWiFiInfo();
    delay(1000); // Debounce delay
  }
  // if (lastButtonState == HIGH && currentButtonState == LOW)
  // {
  //   // Button pressed
  //   Serial.println("Button pressed!");
  // }

  // lastButtonState = currentButtonState;
}

void setup()
{
  Serial.begin(115200);
  pinMode(BUTTON_PIN, INPUT_PULLUP); // Configure button with pull-up resistor
  delay(2000);

  Wire.begin(4, 5);

  Serial.println("ESP32-C3 booted");
  Serial.println(F("BME280 and Display test"));

  bool statusBME, statusDisplay;

  statusBME = initSensor();
  statusDisplay = initDisplay();

  if (!statusBME || !statusDisplay)
  {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    while (1)
      ;
  }

  initWiFi();
  initServer();

  // startSplash();
  // invertDisplayTimes(2);
}

void loop()
{
  handleClient();
  bool currentButtonState = digitalRead(BUTTON_PIN);

  if (currentButtonState == LOW)
  {
    displayWiFiInfo();
  }
  else
  {

    readAndDisplay();
  }
  // readButton();
}