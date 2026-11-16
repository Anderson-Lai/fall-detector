#include <Arduino.h>

#include "globals.hpp"
#include "init.hpp"

void setup() {
  Init::InitSerial(Init::SERIAL_BAUD_RATE);
  Init::PulldownAllPins();
  if (!Init::ConnectToWifi()) {
    Serial.println("Failed to connect to Wi-Fi. Continuing without Wi-Fi.");
  }
}

void loop() {
  Globals::fall.SampleAcceleration();
  if (Globals::fall.IsFallDetected()) {
    Serial.println("Fall detected!");

    Globals::fall.ResetAccelerationHistory();
    Globals::fall.Debounce();
  }

  delay(Init::LOOP_DELAY_MS);
}