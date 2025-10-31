#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Displaygröße (Standard für 0.96" SSD1306)
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

// I²C-Pins am ESP32
#define OLED_SDA 21
#define OLED_SCL 22

// Displayobjekt anlegen
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  // Serielle Schnittstelle zum Debuggen
  Serial.begin(9600);

  // Display initialisieren
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("Fehler beim Initialisieren des Displays!");
    for(;;); // stoppt das Programm, falls kein Display gefunden
  }

  // Bildschirm löschen
  display.clearDisplay();

  // Text-Einstellungen
  display.setTextSize(2);             // Schriftgröße
  display.setTextColor(SSD1306_WHITE);// Farbe (nur Weiß beim OLED)
  display.setCursor(10, 25);          // Position (x, y)

  // Text ausgeben
  display.println("Hallo!");
  display.display();                  // Anzeige aktualisieren
}

void loop() {
  // Hier passiert nichts weiter
}
