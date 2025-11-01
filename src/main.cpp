#include <Arduino.h>
#include <WiFi.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "wifi_credentials.h"  // <--- WLAN-Daten von externer Datei einbinden

// === Display-Setup ===
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_SDA 21
#define OLED_SCL 22
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  Serial.begin(9600);
  delay(100);

  // Display starten
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("Display-Init fehlgeschlagen!");
    for(;;);
  }

  // WLAN-Verbindung starten
  Serial.print("Verbinde mit WLAN: ");
  Serial.println(WIFI_SSID);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  // Warten bis verbunden
  int versuch = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    versuch++;
    if (versuch > 40) { // nach 20 Sekunden abbrechen
      Serial.println("Verbindung fehlgeschlagen!");
      return;
    }
  }

  // Erfolgreich verbunden
  Serial.println();
  Serial.println("WLAN verbunden!");
  Serial.print("IP-Adresse: ");
  Serial.println(WiFi.localIP());

  // IP auf dem Display zeigen
  display.clearDisplay();
  display.setCursor(0, 0);
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.print("IP: ");
  display.println(WiFi.localIP());
  display.display();
}

void loop() {
}
