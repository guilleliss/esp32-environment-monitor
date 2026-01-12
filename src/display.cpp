#include <Adafruit_SSD1306.h>
#include <Wire.h>

#include "display.h"
#include "sensor.h"
#include "wifi-server.h"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire);

bool initDisplay()
{
  bool status = display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

  if (status)
  {
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.display();
  }

  return status;
}

void clearDisplay()
{
  display.setCursor(0, 0);
  display.clearDisplay();
}

void displayValues()
{
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 4);

  display.print("T: ");
  display.print(getTemperature());
  display.print(" C");

  display.setCursor(0, 16);

  display.print("H: ");
  display.print(getHumidity());
  display.print("%");

  display.setCursor(0, 28);

  display.print("Battery: ");
  display.print(getBatteryLevel());
  display.print("%");

  display.display();
}

void startSplash()
{
  display.setTextSize(2);
  for (int i = 0; i < 30; i++)
  {
    display.clearDisplay();
    display.setCursor(15, 20 + (60 - i * 2));
    display.print("Starting");
    display.display();
    delay(5);
  }
}

void invertDisplayTimes(int times)
{
  for (int i = 0; i < times * 2; i++)
  {
    display.invertDisplay(i % 2 == 0);
    display.display();
    delay(500);
  }
}

void displayWifiConnecting(int dots, const char *status)
{
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 10);
  display.print("Connecting to WiFi");
  for (int i = 0; i < dots; i++)
    display.print(".");

  display.setCursor(0, 20);
  display.setTextSize(1);
  display.print("Status: ");
  display.println(status);
  display.display();
}

void displayWifiConnected(const char *ip)
{
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 10);
  display.println("Connected!");
  display.println();
  display.print("IP: ");
  display.println(ip);
  display.display();
  delay(5000);
}

void displayWiFiInfo()
{
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("WiFi Info:");
  display.print("IP: ");
  display.println(wifiIPAddress.toString());
  display.display();
}