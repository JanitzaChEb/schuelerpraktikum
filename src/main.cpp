#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Display-Größe
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

// Pins
#define OLED_SDA 21
#define OLED_SCL 22
#define BUTTON_PIN 33
#define LIGHT_PIN 32

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Variablen
int page = 0;                  // aktuelle Seite (0 = Willkommen, 1 = Lichtsensor)
int lastButtonState = HIGH;    // vorheriger Buttonzustand
int currentButtonState = HIGH; // aktueller Zustand

void showWelcomePage() {
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(10, 25);
  display.println("Hallo!");
  display.display();
}

void showLightPage() {
  int sensorWert = analogRead(LIGHT_PIN);
  int helligkeit = map(sensorWert, 0, 4095, 0, 100);
  if (helligkeit < 0) helligkeit = 0;
  if (helligkeit > 100) helligkeit = 100;

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 10);
  display.println("Lichtsensor:");
  display.setTextSize(2);
  display.setCursor(10, 30);
  display.print(helligkeit);
  display.println("%");
  display.display();
}

void setup() {
  Serial.begin(9600);

  pinMode(BUTTON_PIN, INPUT_PULLUP);

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("Fehler beim Initialisieren des Displays!");
    for(;;);
  }

  display.clearDisplay();
  showWelcomePage();
}

void loop() {
  currentButtonState = digitalRead(BUTTON_PIN);

  // Wenn der Button gerade gedrückt wurde (von HIGH -> LOW)
  if (currentButtonState == LOW && lastButtonState == HIGH) {
    page++;           // zur nächsten Seite wechseln
    if (page > 1) {   // nur zwei Seiten → zurück zu 0
      page = 0;
    }

    // Anzeige je nach Seite aktualisieren
    if (page == 0) {
      showWelcomePage();
    } else if (page == 1) {
      showLightPage();
    }

    delay(200); // kleine Pause gegen Prellen
  }

  lastButtonState = currentButtonState;

  // Wenn wir auf der Lichtsensor-Seite sind, regelmäßig aktualisieren
  if (page == 1) {
    showLightPage();
    delay(500);
  }
}
