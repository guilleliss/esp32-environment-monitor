#pragma once

bool initDisplay();

void clearDisplay();

void displayValues();

void startSplash();

void invertDisplayTimes(int times);

void displayWifiConnecting(int dots, const char *status);

void displayWifiConnected(const char *ip);

void displayWiFiInfo();