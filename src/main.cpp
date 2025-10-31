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

// Spielfigur
int x = 0;           // aktuelle x-Position
int y = 27;          // y bleibt konstant (mittig)
const int size = 10; // Größe der Figur (Breite=Höhe)
const int speed = 2; // Schrittweite pro Tastendruck

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  Serial.begin(9600);
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("Fehler beim Initialisieren des Displays!");
    for (;;);
  }

  display.clearDisplay();
  display.display();
}

void loop() {
  int state = digitalRead(BUTTON_PIN);

  if (state == LOW) {
    // --- KOLLISIONS-PRUEFUNG RECHTS ---
    // neue x-Position, wenn wir uns bewegen würden
    int neuerX = x + speed;

    // Rand-Bedingungen (nur rechts nötig in dieser Aufgabe)
    bool rechter_rand_wuerde_ueberschritten =
      (neuerX + size) > SCREEN_WIDTH; // rechte Figurkante > 128?

    // Nur bewegen, wenn wir im Bild bleiben
    if (!rechter_rand_wuerde_ueberschritten) {
      x = neuerX;
    } else {
      // optional: exakt an den Rand "klemmen"
      x = SCREEN_WIDTH - size;
    }

    delay(50); // kleine Entprellpause
  }

  // Zeichnen
  display.clearDisplay();
  display.fillRect(x, y, size, size, SSD1306_WHITE);
  display.display();
}
