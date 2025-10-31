#include <Arduino.h>

// LED1 an GPIO25, LED2 an GPIO26 angeschlossen
int led1 = 25;
int led2 = 26;

void setup() {
  // Beide Pins als Ausgänge einstellen
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
}

void loop() {
  // Erste LED an, zweite LED aus
  digitalWrite(led1, HIGH);
  digitalWrite(led2, LOW);
  delay(500);  // kurze Pause

  // Erste LED aus, zweite LED an
  digitalWrite(led1, LOW);
  digitalWrite(led2, HIGH);
  delay(500);  // gleiche Pause
}
