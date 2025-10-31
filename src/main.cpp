#include <Arduino.h>

// LEDs an GPIO25 und GPIO26
int led1 = 25;
int led2 = 26;

// Blinkgeschwindigkeiten (in Millisekunden)
int interval1 = 500;   // LED1 wechselt alle 0,5 Sekunden
int interval2 = 300;   // LED2 wechselt alle 0,3 Sekunden

// Variablen, um zu speichern, wann zuletzt geschaltet wurde
unsigned long letzteZeit1 = 0;
unsigned long letzteZeit2 = 0;

// Zustände der LEDs (an/aus)
bool led1An = false;
bool led2An = false;

void setup() {
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
}

void loop() {
  // aktuelle Zeit merken
  unsigned long jetzt = millis();

  // --- LED1 prüfen ---
  if (jetzt - letzteZeit1 >= interval1) {
    // Zustand umschalten
    led1An = !led1An;
    digitalWrite(led1, led1An ? HIGH : LOW);
    // Zeit merken
    letzteZeit1 = jetzt;
  }

  // --- LED2 prüfen ---
  if (jetzt - letzteZeit2 >= interval2) {
    led2An = !led2An;
    digitalWrite(led2, led2An ? HIGH : LOW);
    letzteZeit2 = jetzt;
  }
}
