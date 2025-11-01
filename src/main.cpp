#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>

// -------- Display (SSD1306, 128x64) --------
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
// I²C-Pins am ESP32: SDA=21, SCL=22
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// -------- DHT11 --------
#define DHTPIN 27       // Daten-Pin des DHT11
#define DHTTYPE DHT11   // Sensortyp
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);

  // Display starten
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("Display-Init fehlgeschlagen!");
    for(;;);
  }
  display.clearDisplay();
  display.display();

  // DHT starten
  dht.begin();
}

void loop() {
  // Messwerte lesen
  float hum = dht.readHumidity();        // in Prozent
  float temp = dht.readTemperature();    // in °C (Celsius)

  // Prüfen, ob das Lesen geklappt hat
  if (isnan(hum) || isnan(temp)) {
    Serial.println("Fehler beim Lesen vom DHT11!");
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.println("DHT11-Fehler :(");
    display.display();
    delay(2000);
    return;
  }

  // Ausgabe im Serial Monitor (optional)
  Serial.print("Temp: ");
  Serial.print(temp);
  Serial.print(" °C  |  Feuchte: ");
  Serial.print(hum);
  Serial.println(" %");

  // Anzeige auf dem Display
  display.clearDisplay();

  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("Klima (DHT11):");

  display.setTextSize(2);
  display.setCursor(0, 22);
  display.print("T: ");
  display.print(temp, 1);   // eine Nachkommastelle
  display.println(" C");

  display.setCursor(0, 46);
  display.print("H: ");
  display.print(hum, 0);    // ganzzahlig reicht beim DHT11
  display.println(" %");

  display.display();

  delay(2000);  // DHT11: sinnvolles Messintervall ~2s
}
