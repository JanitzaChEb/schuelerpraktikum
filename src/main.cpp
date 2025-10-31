#include <Arduino.h>

// Lichtsensor an GPIO32
const int sensorPin = 32;

// Kalibrierung – hier ggf. eigene Werte einsetzen:
// Wert bei hell (ohne Hand)
const int maxWert = 2800;
// Wert bei dunkel (Hand drauf oder abgedeckt)
const int minWert = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("Lichtsensor mit Prozentanzeige gestartet!");
}

void loop() {
  // Analogen Wert vom Sensor lesen
  int sensorWert = analogRead(sensorPin);

  // Den Messwert in Prozent umrechnen (0–100 %)
  int helligkeit = map(sensorWert, minWert, maxWert, 0, 100);

  // Werte außerhalb des Bereichs begrenzen
  if (helligkeit < 0) helligkeit = 0;
  if (helligkeit > 100) helligkeit = 100;

  // Ausgabe im seriellen Monitor
  Serial.print("Sensorwert: ");
  Serial.print(sensorWert);
  Serial.print(" -> Helligkeit: ");
  Serial.print(helligkeit);
  Serial.println("%");

  delay(500);
}
