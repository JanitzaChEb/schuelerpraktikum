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
int x = 0;           // Startposition (x)
int y = 27;          // y bleibt konstant (mittig)
const int size = 10; // Breite/Höhe der Figur
const int speed = 2; // Schrittgröße pro Tastendruck

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

  // Wenn der Button gedrückt ist (LOW wegen INPUT_PULLUP)
  if (state == LOW) {
    x = x + speed;   // Figur bewegt sich nach rechts
    delay(50);       // kurze Pause (Entprellung)
  }

  // Display aktualisieren
  display.clearDisplay();
  display.fillRect(x, y, size, size, SSD1306_WHITE); // Figur zeichnen
  display.display();
}
