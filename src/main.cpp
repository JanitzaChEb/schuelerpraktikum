#include <Arduino.h>

// LED an GPIO25
const int ledPin = 25;

// Button an GPIO33 (ein Bein an Pin, das andere an GND)
const int buttonPin = 33;

// Zustandsvariablen
int lastState = HIGH;       // vorheriger Zustand des Buttons
int currentState = HIGH;    // aktueller Zustand
bool ledAn = false;         // merkt sich, ob LED gerade leuchtet

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);

  // Serielle Verbindung starten (Baudrate 9600)
  Serial.begin(9600);
  Serial.println("Programm gestartet!");
}

void loop() {
  // aktuellen Buttonzustand lesen
  currentState = digitalRead(buttonPin);

  // Wenn sich der Zustand geändert hat
  if (currentState != lastState) {
    // Wenn Button gedrückt wurde (LOW)
    if (currentState == LOW) {
      ledAn = !ledAn; // LED-Zustand umschalten
      digitalWrite(ledPin, ledAn ? HIGH : LOW);

      // Zustände im seriellen Monitor ausgeben
      Serial.print("Button gedrückt → LED ist jetzt: ");
      Serial.println(ledAn ? "AN" : "AUS");
    }

    // kleine Pause zur Entprellung
    delay(50);
  }

  // Debug-Ausgabe (optional): Zustände immer anzeigen
  Serial.print("currentState: ");
  Serial.print(currentState);
  Serial.print(" | lastState: ");
  Serial.println(lastState);

  // Zustand für nächsten Durchlauf merken
  lastState = currentState;
}
