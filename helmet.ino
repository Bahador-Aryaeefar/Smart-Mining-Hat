#include <WiFi.h>
#include <WebServer.h>
#include <DHT.h>
#include <Adafruit_BMP085.h>
#define DHTPIN 4
#define DHTTYPE DHT22
#define RED_PIN 18
#define GREEN_PIN 19

DHT dht(DHTPIN, DHTTYPE);
Adafruit_BMP085 bmp;

const char* ssid = "my_hotspot";
const char* password = "my_password";
const IPAddress local_IP(192, 168, 0, 1);
const IPAddress gateway_IP(192, 168, 0, 1);
const IPAddress subnet_mask(255, 255, 255, 0);
float h = -1;
float t1 = -1;
float t2 = -1;
double p = -1;
double a = -1;
double g = -1;

WebServer server(80);

void handleRoot() {
  server.send(200, "text/plain", "Hello from ESP32!");
  Serial.println("sent root");
}

void handleSensors() {
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.sendHeader("Access-Control-Allow-Methods", "GET, POST");
  server.sendHeader("Access-Control-Allow-Headers", "Content-Type");
  String json = "{\"humidity_th22\": " + String(h)
                + ", \"temperature_th22\": " + String(t1)
                + ", \"altitude_bmp180\": " + String(a)
                + ", \"pressure_bmp180\": " + String(p)
                + ", \"temperature_bmp180\": " + String(t2)
                + ", \"gas_mq9b\": " + String(g)
                + "}";
  server.send(200, "application/json", json);
  Serial.println("sent sensors");
}

void setup() {
  Serial.begin(115200);
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  WiFi.softAPConfig(local_IP, gateway_IP, subnet_mask);
  WiFi.softAP(ssid, password);

  server.on("/", handleRoot);
  server.on("/sensors", handleSensors);
  while (1) {
    if (bmp.begin()) break;
    Serial.println("failed");
    delay(2000);
  }
  server.begin();

  dht.begin();
}

void loop() {
  h = dht.readHumidity();
  t1 = dht.readTemperature();
  p = bmp.readPressure() / 100.0F;
  a = bmp.readAltitude(101325);
  t2 = bmp.readTemperature();

  int sensorValue = analogRead(36);
  float voltage = sensorValue * (5 / 4095.0);
  g = voltage / 5 * 100;

  if (g < 20) {
    digitalWrite(GREEN_PIN, HIGH);
    digitalWrite(RED_PIN, LOW);
  } else {
    digitalWrite(GREEN_PIN, LOW);
    digitalWrite(RED_PIN, HIGH);
  }
  // Serial.println("Gas Level: "  + String(sensorValue) + " - Voltage: "  + String(voltage) + " - Percent: "  + String(g));
  // Serial.println("Humidity: " + String(h));
  // Serial.println("Temperature_dht22: " + String(t1));
  // Serial.println("Temperature_bmp180: " + String(t2));
  // Serial.println("Pressure : " + String(p));
  // Serial.println("Altitude : " + String(a));
  server.handleClient();
  delay(200);
}