#include <Arduino.h>

// LED an GPIO25
const int ledPin = 25;

// Button an GPIO33 (ein Bein an Pin, das andere an GND)
const int buttonPin = 33;

// Variablen für den Tasterzustand
int lastState = HIGH;       // vorheriger Zustand (HIGH = nicht gedrückt)
int currentState = HIGH;    // aktueller Zustand
bool ledAn = false;         // merkt sich, ob die LED gerade an oder aus ist

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
}

void loop() {
  // aktuellen Zustand des Buttons lesen
  currentState = digitalRead(buttonPin);

  // prüfen, ob sich der Zustand geändert hat
  if (currentState != lastState) {
    // wenn der Button gerade gedrückt wurde (LOW)
    if (currentState == LOW) {
      // LED-Zustand umschalten
      ledAn = !ledAn;
      digitalWrite(ledPin, ledAn ? HIGH : LOW);
    }

    // kleine Pause zur Entprellung (Button prellt kurz beim Drücken)
    delay(50);
  }

  // aktuellen Zustand speichern, um ihn beim nächsten Durchlauf zu vergleichen
  lastState = currentState;
}
