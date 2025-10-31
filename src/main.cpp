#include <Arduino.h>

// LED ist an GPIO25 angeschlossen
int ledPin = 25;

void setup() {
  // Pin als Ausgang festlegen
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // LED einschalten
  digitalWrite(ledPin, HIGH);
  delay(500);  // warte 500 Millisekunden (0,5 Sekunden)

  // LED ausschalten
  digitalWrite(ledPin, LOW);
  delay(500);  // wieder 0,5 Sekunden warten
}
