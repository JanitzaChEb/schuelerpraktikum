#include <Arduino.h>

// LEDs
const int led1 = 25;     // erste LED an GPIO25
const int led2 = 26;     // zweite LED an GPIO26

// Button
const int buttonPin = 33;  // Button an GPIO33 (zweites Bein an GND)

void setup() {
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);

  // interner Pull-Up-Widerstand aktiviert:
  // → HIGH wenn nicht gedrückt, LOW wenn gedrückt
  pinMode(buttonPin, INPUT_PULLUP);
}

void loop() {
  // Buttonzustand lesen
  int buttonState = digitalRead(buttonPin);

  if (buttonState == LOW) {
    // gedrückt → LEDs an
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
  } else {
    // nicht gedrückt → LEDs aus
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
  }
}
