#include <WiFi.h>
#include <PubSubClient.h>
#include <time.h>

// ✅ 1. WiFi credentials
const char* ssid = "Wokwi-GUEST";
const char* password = "";

// ✅ 2. MQTT broker config (ganti IP sesuai Node-RED broker kamu)
const char* mqtt_server = "test.mosquitto.org";
const int mqtt_port = 1883;
const char* mqtt_topic = "gps/data";

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  Serial.begin(115200);

  // ✅ 3. Connect WiFi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected!");

  // ✅ 4. Sync NTP time
  configTime(0, 0, "pool.ntp.org", "time.nist.gov");
  while (time(nullptr) < 100000) {
    delay(500);
    Serial.print("*");
  }
  Serial.println("\nTime synced.");

  // ✅ 5. Connect MQTT
  client.setServer(mqtt_server, mqtt_port);
  while (!client.connected()) {
    Serial.print("Connecting to MQTT...");
    if (client.connect("ESP32Client")) {
      Serial.println("connected.");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      delay(2000);
    }
  }
}

void loop() {
  if (!client.connected()) {
    while (!client.connect("ESP32Client")) {
      Serial.print("Reconnecting MQTT...");
      delay(1000);
    }
    Serial.println("MQTT reconnected.");
  }

  // ✅ 6. Dummy GPS + battery + timestamp
  float lat = 12.9716 + (random(-100, 100) / 10000.0);
  float lon = 77.5946 + (random(-100, 100) / 10000.0);
  int battery = random(40, 101);

  // ✅ 7. Time
  time_t now = time(nullptr);
  struct tm* timeinfo = localtime(&now);
  char timeStr[30];
  strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", timeinfo);

  // ✅ 8. JSON payload
  String payload = "{";
  payload += "\"lat\":" + String(lat, 6) + ",";
  payload += "\"lon\":" + String(lon, 6) + ",";
  payload += "\"battery\":" + String(battery) + ",";
  payload += "\"timestamp\":\"" + String(timeStr) + "\"";
  payload += "}";

  // ✅ 9. Publish ke MQTT
  client.publish(mqtt_topic, payload.c_str());
  Serial.println("Published: " + payload);

  delay(10000); 
}
