#include <Arduino.h>

// Lichtsensor an GPIO32 (analoger Eingang)
const int sensorPin = 32;

void setup() {
  // Serielle Verbindung starten
  Serial.begin(9600);
  Serial.println("Lichtsensor gestartet!");
}

void loop() {
  // Analogen Wert vom Sensor lesen (0 bis 4095 beim ESP32)
  int sensorWert = analogRead(sensorPin);

  // Wert im seriellen Monitor ausgeben
  Serial.print("Helligkeitswert: ");
  Serial.println(sensorWert);

  // kleine Pause, damit man die Werte besser lesen kann
  delay(500);
}
