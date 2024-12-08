#include <Arduino.h>
#include <WiFi.h>
#include <MQTT.h>

// WiFi credentials
const char *ssid = "SSID";
const char *password = "PASSWORD";

// MQTT credentials
const char *mqtt_server = "";
const char *mqtt_client_id = "ESP32Client";
const int mqtt_port = 1883;
const char *mqtt_user = "";
const char *mqtt_password = "";

WiFiClient net;
MQTTClient client;
unsigned long timems = 0;

void setup()
{
  Serial.begin(115200);
  pinMode(4, INPUT);
  timems = millis();

  WiFi.begin(ssid, password);

  Serial.print("checking wifi...");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(1000);
  }

  client.begin(mqtt_server, mqtt_port, net);

  Serial.print("\nconnecting...");
  while (!client.connect(mqtt_client_id, mqtt_user, mqtt_password)) {
    Serial.print(".");
    delay(1000);
  }

  Serial.println("\nconnected!");
}

void loop()
{
  int val = analogRead(4);
  if (val != 0 && (millis() - timems) > 500)
  {
    unsigned long delta = millis() - timems;

    float timeh = (float)delta / 1000.0 / 3600.0;

    float wattage = 1.0 / timeh;

    Serial.printf("Wattage: %.6f W\n", wattage);

    client.publish("esp32/wattage", String(wattage).c_str());

    timems = millis();
  }
  delay(1);
}
