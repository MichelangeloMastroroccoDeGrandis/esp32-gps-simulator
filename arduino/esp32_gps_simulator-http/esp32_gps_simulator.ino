#include <WiFi.h>
#include <HTTPClient.h>
#include <time.h>

const char* ssid = "Wokwi-GUEST";
const char* password = "";

const char* serverUrl = "http://192.168.18.104:1880/gpsdata";  // Ensure port 1880 is included

void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("WiFi connected.");

  configTime(0, 0, "pool.ntp.org", "time.nist.gov");
  while (time(nullptr) < 100000) {
    delay(500);
    Serial.print("*");
  }
  Serial.println("Time synced.");
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    float lat = 12.9716 + (random(-100, 100) / 10000.0);
    float lon = 77.5946 + (random(-100, 100) / 10000.0);
    int battery = random(50, 100);

    time_t now = time(nullptr);
    struct tm* timeinfo = localtime(&now);
    char timeStr[30];
    strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", timeinfo);

    String payload = "{";
    payload += "\"lat\":" + String(lat, 6) + ",";
    payload += "\"lon\":" + String(lon, 6) + ",";
    payload += "\"battery\":" + String(battery) + ",";
    payload += "\"timestamp\":\"" + String(timeStr) + "\"";
    payload += "}";

    HTTPClient http;
    http.begin(serverUrl);
    http.addHeader("Content-Type", "application/json");
    int httpCode = http.POST(payload);
    Serial.println("Sent: " + payload);
    Serial.println("HTTP Response: " + String(httpCode));
    http.end();

    delay(10000);
  }
}