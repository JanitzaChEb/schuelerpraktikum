#include <Arduino.h>

// Wir nehmen an, die LED ist an GPIO25 angeschlossen
int ledPin = 25;  // Pin-Nummer für die LED

void setup() {
  // Pin als Ausgang einstellen
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // LED einschalten
  digitalWrite(ledPin, HIGH);
}
