#include <Arduino.h>

#include "globals.hpp"
#include "init.hpp"

void setup() {
  Init::Setup();
}

static void AlertCleanUp() {
  digitalWrite(Globals::BUZZER_PIN, LOW);
  Globals::state = Globals::State::IDLE;
  Globals::alertTriggerTimeMS = UINT64_MAX;
  Globals::alertSendTimeMS = UINT64_MAX;
}

void loop() {
  // handle double press of button
  bool manualAlertTriggered = false;
  if (Globals::button.IsDoublePressed()) {
    switch (Globals::state) {
      case Globals::State::IDLE:
        Serial.println();
        Serial.println("Button double-pressed. Switching to QUEUED_MESSAGE state.");
        Serial.println();

        Globals::state = Globals::State::QUEUED_MESSAGE;
        manualAlertTriggered = true;
        break;
      case Globals::State::QUEUED_MESSAGE:        
      case Globals::State::MESSAGE_PENDING:
        Serial.println();
        Serial.println("Button double-pressed. Switching to IDLE state.");
        Serial.println();

        AlertCleanUp();
        break;
    }
  }

  // send alert if timeout has been reached
  if (Globals::state == Globals::State::MESSAGE_PENDING && millis() >= Globals::alertSendTimeMS) {
    Serial.println("Alert timeout reached. Sending alert to API...");
    Serial.println();

    // tell user they can no longer cancel the alert
    digitalWrite(Globals::BUZZER_PIN, LOW);

    bool alertSent = false;
    for (uint8_t i = 0; i < Globals::RETRY_ATTEMPTS; ++i) {
      if (Globals::api.SendAlert("SOS")) {
        Serial.println("Alert sent successfully!");

        alertSent = true;
        break;
      } else {
        Serial.print("Failed to send alert. Attempt ");
        Serial.print(i + 1);
        Serial.print(" of ");
        Serial.println(Globals::RETRY_ATTEMPTS);

        delay(Globals::RETRY_TIMEOUT_MS);
      }
    }

    if (!alertSent) {
      Serial.println("All attempts to send alert failed.");
      Init::ChimeBuzzer(500);
    }

    AlertCleanUp();

    Serial.println();
    Serial.println("Global state reset to IDLE. Waiting for next event...");
    Serial.println();
  }

  // detect for falls
#ifdef DEBUG_BUILD_ACCELEROMETER
  Serial.println("Accelerations: ");
  const auto accelerations = Globals::accelerometer.GetAccelerations();
  Serial.print("X: ");
  Serial.print(accelerations[0]);
  Serial.print(" | Y: ");
  Serial.print(accelerations[1]);
  Serial.print(" | Z: ");
  Serial.println(accelerations[2]);

  Serial.print("Acceleration magnitude: ");
  Serial.println(Globals::accelerometer.GetAcclerationMagnitude());
#endif
  Globals::fall.SampleAcceleration();

  // second check will perform debouncing for us
  // handles if fall is detected
  if (Globals::fall.IsFallDetected() && Globals::state == Globals::State::IDLE) {
    Serial.println("Fall detected!");
    Globals::state = Globals::State::QUEUED_MESSAGE;
  }

  // handles if a message is queued
  if (Globals::state == Globals::State::QUEUED_MESSAGE) {
    Serial.println("Global state is QUEUED_MESSAGE. Activating buzzer and setting alert timeout...");
    digitalWrite(Globals::BUZZER_PIN, HIGH);

    const uint32_t alertTimeoutMS = manualAlertTriggered ? 
      Globals::MANUAL_ALERT_TIMEOUT_MS : Globals::AUTOMATIC_ALERT_TIMEOUT_MS; 

    Globals::alertTriggerTimeMS = millis();
    Globals::alertSendTimeMS = Globals::alertTriggerTimeMS + alertTimeoutMS;

    Globals::state = Globals::State::MESSAGE_PENDING;
  }

  delay(Init::LOOP_DELAY_MS);
}