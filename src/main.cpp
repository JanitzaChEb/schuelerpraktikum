#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Display
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Pins
#define BUTTON_PIN 33
#define OLED_SDA 21
#define OLED_SCL 22

// Spieler (Quadrat)
int px = 0;            // Position x
int py = 27;           // Position y
const int pSize = 10;  // Breite/Höhe
const int pSpeed = 2;  // Schritt pro Tastendruck

// Objekt (z. B. "Münze")
int ox = 80;           // Position x
int oy = 30;           // Position y
const int oW = 8;      // Breite
const int oH = 8;      // Höhe

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  Serial.begin(9600);
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("Display-Init fehlgeschlagen!");
    for(;;);
  }
  display.clearDisplay();
  display.display();
}

void loop() {
  // --- Bewegung nach rechts (mit rechter Randbegrenzung) ---
  if (digitalRead(BUTTON_PIN) == LOW) {
    int neuerX = px + pSpeed;
    if (neuerX + pSize <= SCREEN_WIDTH) {
      px = neuerX;                 // nur bewegen, wenn im Bild
    } else {
      px = SCREEN_WIDTH - pSize;   // am Rand stehen bleiben
    }
    delay(40); // kleine Entprellpause
  }

  // --- Kollision prüfen: AABB (Axis-Aligned Bounding Box) ---
  bool getrennt =
    (px + pSize <= ox) ||      // Spieler rechts vor Objekt links
    (ox + oW <= px) ||         // Objekt rechts vor Spieler links
    (py + pSize <= oy) ||      // Spieler unter Objekt
    (oy + oH <= py);           // Objekt unter Spieler

  bool kollidiert = !getrennt;

  // --- Zeichnen ---
  display.clearDisplay();

  // Objekt
  display.fillRect(ox, oy, oW, oH, SSD1306_WHITE);

  // Spieler
  display.fillRect(px, py, pSize, pSize, SSD1306_WHITE);

  // Meldung bei Kollision
  if (kollidiert) {
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(2, 2);
    display.println("Treffer!");
  }

  display.display();
}
