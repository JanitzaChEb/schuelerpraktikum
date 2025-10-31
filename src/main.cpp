#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define OLED_SDA 21
#define OLED_SCL 22

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Ein kleines Beispiel-Bitmap (8x8 Pixel Herz)
static const unsigned char PROGMEM herz_bild[] = {
  0b00000000,
  0b01100110,
  0b11111111,
  0b11111111,
  0b01111110,
  0b00111100,
  0b00011000,
  0b00000000
};

void setup() {
  Serial.begin(9600);
  
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("Fehler beim Initialisieren des Displays!");
    for(;;);
  }

  display.clearDisplay();

  // --- 1️⃣ Text ---
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Display Test");

  // --- 2️⃣ Linie ---
  display.drawLine(0, 12, 127, 12, SSD1306_WHITE);

  // --- 3️⃣ Rechtecke & Kreise ---
  display.drawRect(5, 20, 30, 20, SSD1306_WHITE);  // Rahmen
  display.fillRect(10, 25, 20, 10, SSD1306_WHITE); // gefülltes Rechteck
  display.drawCircle(70, 30, 10, SSD1306_WHITE);   // Kreisrahmen
  display.fillCircle(100, 30, 10, SSD1306_WHITE);  // gefüllter Kreis

  // --- 4️⃣ Bitmap ---
  display.drawBitmap(58, 48, herz_bild, 8, 8, SSD1306_WHITE);

  display.display();
}

void loop() {
  // Hier passiert nichts weiter
}
