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

// Spielfigur
float x = 20;        // x-Position (fix)
float y = 20;        // Startposition y
float vy = 0;        // vertikale Geschwindigkeit
const float g = 0.4; // "Gravitation" (je größer, desto schneller fällt die Figur)
const float jump = -5.0; // Geschwindigkeit beim Sprung (negativ = nach oben)
const int size = 10;     // Größe der Figur

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
  // --- Eingabe ---
  if (digitalRead(BUTTON_PIN) == LOW) {
    vy = jump; // "Sprung" = Anfangsgeschwindigkeit nach oben
  }

  // --- Physik: Bewegung unter Schwerkraft ---
  vy = vy + g;   // Beschleunigung nach unten
  y = y + vy;    // neue Position

  // --- Begrenzung: nicht aus dem Display fallen ---
  if (y + size >= SCREEN_HEIGHT) {
    y = SCREEN_HEIGHT - size;
    vy = 0; // auf dem Boden stoppen
  }
  if (y < 0) {
    y = 0;
    vy = 0; // nicht über den oberen Rand
  }

  // --- Zeichnen ---
  display.clearDisplay();
  display.fillRect((int)x, (int)y, size, size, SSD1306_WHITE);
  display.display();

  delay(30); // Frame-Rate (ca. 30 ms = ~33 FPS)
}
