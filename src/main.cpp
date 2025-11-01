#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <DHT.h>

// ==== WLAN-Zugangsdaten ====
// Variante A: direkt hier (Platzhalter):
// const char* WIFI_SSID = "DEIN_SSID";
// const char* WIFI_PASSWORD = "DEIN_PASSWORT";

// Variante B: ausgelagert (empfohlen):
#include "wifi_credentials.h"   // enthält: const char* WIFI_SSID; const char* WIFI_PASSWORD;

// ==== DHT11 an GPIO27 ====
#define DHTPIN 27
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// ==== Webserver (Port 80) ====
WebServer server(80);

void handleRoot() {
  String page = "ESP32 Webserver\n";
  page += "Endpoints:\n";
  page += "  /temperature  -> Temperatur in °C\n";
  page += "  /humidity     -> Luftfeuchte in %\n";
  server.send(200, "text/plain", page);
}

void handleTemperature() {
  float t = dht.readTemperature();  // °C
  server.send(200, "text/plain", String(t));
}

void handleHumidity() {
  float h = dht.readHumidity();     // %
  server.send(200, "text/plain", String(h));
}

void setup() {
  Serial.begin(9600);
  dht.begin();

  // --- WLAN verbinden ---
  Serial.print("Verbinde mit WLAN: "); Serial.println(WIFI_SSID);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("WLAN verbunden!");
  Serial.print("IP-Adresse: "); Serial.println(WiFi.localIP());

  // --- Endpoints registrieren ---
  server.on("/", handleRoot);
  server.on("/temperature", handleTemperature);
  server.on("/humidity", handleHumidity);

  // Server starten
  server.begin();
  Serial.println("HTTP-Server gestartet.");
}

void loop() {
  // eingehende Anfragen bearbeiten
  server.handleClient();
}
