#include <Arduino.h>

#include "globals.hpp"
#include "init.hpp"

void setup() {
  Init::InitSerial(Init::SERIAL_BAUD_RATE);
  Init::PulldownAllPins();
  Init::ConnectToWifi();
}

void loop() {
  Globals::fall.SampleAcceleration();
  if (Globals::fall.IsFallDetected()) {
    Serial.println("Fall detected!");
    Globals::fall.ResetAccelerationHistory();

    delay(1'000); // delay for 1 second to prevent bouncing
  }

  delay(Init::LOOP_DELAY_MS);
}