#include <WebServer.h>
#include <WiFi.h>

#include "display.h"
#include "sensor.h"
#include "wifi-server.h"

const char *ssid = "WagnerColoc";
const char *password = "87Power!";

WebServer server(80);

// Define the global IP address variable
IPAddress wifiIPAddress;

const char INDEX_HTML[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
  <meta charset="utf-8">
  <title>ESP32 Sensor</title>
  <meta name="viewport" content="width=device-width,initial-scale=1">
</head>
<style>
body { font-family: Helvetica; }
</style>
<body>
  <h1>Room data</h1>
  <div id="data">Loading...</div>

  <script>
    async function load() {
      const r = await fetch('/api/data');
      const d = await r.json();
      document.getElementById('data').innerHTML =
        `Temperature: ${d.temp} °C<br>
         Humidity: ${d.hum} %<br>
         Pressure: ${d.pres} hPa`;
    }
    load();
    setInterval(load, 2000);
  </script>
</body>
</html>
)rawliteral";

void handleData()
{
  String json = "{";
  json += "\"temp\":" + String(getTemperature(), 1) + ",";
  json += "\"hum\":" + String(getHumidity(), 1) + ",";
  json += "\"pres\":" + String(getPressure() / 100.0, 1);
  json += "}";

  server.send(200, "application/json", json);
}

void initServer()
{
  server.on("/", []()
            { server.send_P(200, "text/html", INDEX_HTML); });

  server.on("/api/data", handleData);

  server.begin();
}

void initWiFi()
{
  WiFi.begin(ssid, password);
  WiFi.setTxPower(WIFI_POWER_8_5dBm);

  int dots = 0;
  while (WiFi.status() != WL_CONNECTED)
  {
    displayWifiConnecting(dots, wifiStatusToString(WiFi.status()));
    dots = (dots + 1) % 4;
    delay(1000);
  }

  wifiIPAddress = WiFi.localIP();
  displayWifiConnected(wifiIPAddress.toString().c_str());
}

void handleClient()
{
  server.handleClient();
}

const char *wifiStatusToString(wl_status_t status)
{
  switch (status)
  {
  case WL_NO_SHIELD:
    return "NO_SHIELD";
  case WL_IDLE_STATUS:
    return "IDLE";
  case WL_NO_SSID_AVAIL:
    return "NO_SSID";
  case WL_SCAN_COMPLETED:
    return "SCAN_DONE";
  case WL_CONNECTED:
    return "CONNECTED";
  case WL_CONNECT_FAILED:
    return "CONNECT_FAILED";
  case WL_CONNECTION_LOST:
    return "CONNECTION_LOST";
  case WL_DISCONNECTED:
    return "DISCONNECTED";
  default:
    return "UNKNOWN";
  }
}