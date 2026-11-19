#include <Arduino.h>

#include "globals.hpp"
#include "init.hpp"

void setup() {
  Init::InitSerial(Init::SERIAL_BAUD_RATE);

  if (!Init::ConnectToWifi()) {
    Serial.println("Failed to connect to Wi-Fi. Continuing without Wi-Fi.");
  }

  // needed for TLS
  Serial.println();
  if (!Init::SynchronizeTime()) {
    Serial.println("Failed to synchronize time. Continuing without time synchronization.");
  }

  pinMode(Globals::BUZZER_PIN, OUTPUT);

  Serial.println();
  Serial.println("Setup complete.");
  Serial.println();
}

void loop() {
  Globals::fall.SampleAcceleration();
  if (Globals::fall.IsFallDetected()) {
    Serial.println("Fall detected!");

     digitalWrite(Globals::BUZZER_PIN, HIGH);

    Serial.println("Sending fall alert to API...");

    if (Globals::api.SendAlert("SOS")) {
      Serial.println("Fall alert sent successfully!");
    } else {
      Serial.println("Failed to send fall alert.");
    }

    digitalWrite(Globals::BUZZER_PIN, LOW);

    Serial.println();
    Serial.println("Debouncing...");

    Globals::fall.ResetAccelerationHistory();
    Globals::fall.Debounce();

    Serial.println("Resuming fall detection...");
    Serial.println();
  }

  delay(Init::LOOP_DELAY_MS);
}