#include <WiFi.h>
#include <HTTPClient.h>
#include <time.h>

// ✅ 1. Replace with your own WiFi credentials
const char* ssid = "Michelangelo_5G";
const char* password = "0661153026";

// ✅ 2. Replace this with your computer’s local IP address (running Node-RED)
const char* serverUrl = "http://192.168.1.38:1880/gpsdata";

void setup() {
  Serial.begin(115200);

  // ✅ 3. Connect to WiFi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected!");

  // ✅ 4. Sync time from NTP
  configTime(0, 0, "pool.ntp.org", "time.nist.gov");
  while (time(nullptr) < 100000) {
    delay(500);
    Serial.print("*");
  }
  Serial.println("\nTime synced.");
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;

    // ✅ 5. Generate dummy GPS + battery + timestamp data
    float lat = 12.9716 + (random(-100, 100) / 10000.0);
    float lon = 77.5946 + (random(-100, 100) / 10000.0);
    int battery = random(40, 101);

    // ✅ 6. Get current time
    time_t now = time(nullptr);
    struct tm* timeinfo = localtime(&now);
    char timeStr[30];
    strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", timeinfo);

    // ✅ 7. Create JSON payload
    String payload = "{";
    payload += "\"lat\":" + String(lat, 6) + ",";
    payload += "\"lon\":" + String(lon, 6) + ",";
    payload += "\"battery\":" + String(battery) + ",";
    payload += "\"timestamp\":\"" + String(timeStr) + "\"";
    payload += "}";

    // ✅ 8. Send data to Node-RED
    http.begin(serverUrl);
    http.addHeader("Content-Type", "application/json");

    int httpCode = http.POST(payload);
    Serial.println("Sent: " + payload);
    Serial.println("Response: " + String(httpCode));

    http.end();

    delay(3600000); // ✅ Wait 1 hour (3600000 ms) – for testing, you can change to 10 seconds
  } else {
    Serial.println("WiFi not connected!");
    delay(10000);
  }
}
