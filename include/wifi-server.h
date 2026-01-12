#pragma once
#include <IPAddress.h>
#include <WiFi.h>

// Global IP address accessible from other files
extern IPAddress wifiIPAddress;

void handleData();

void initServer();

void initWiFi();

const char *wifiStatusToString(wl_status_t status);

void handleClient();