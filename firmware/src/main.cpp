#include <Arduino.h>
#include "init.hpp"
#include "accelerometer.hpp"

#define ACCEL_X A0
#define ACCEL_Y A1
#define ACCEL_Z A3
#define ACCEL_GSELECT A5
#define ACCEL_MODE AccelerometerMode::HIGH_ACCEL
#define ACCEL_IS_DEBUG false

#define SERIAL_BAUD_RATE 115200
#define LOOP_DELAY_MS 10

void setup() {
  Init::InitSerial(SERIAL_BAUD_RATE);
  Init::PulldownAllPins();
}

void loop() {
  Accelerometer accel(ACCEL_X, ACCEL_Y, ACCEL_Z, 
    ACCEL_GSELECT, ACCEL_MODE, ACCEL_IS_DEBUG);

  auto accelerations = accel.GetAccelerations();
  double magnitude = accel.GetAcclerationMagnitude();
  for (const auto& acceleration : accelerations) {
    Serial.print(acceleration);
    Serial.print(", ");
  }

  Serial.print("Magnitude: ");
  Serial.println(magnitude);

  delay(LOOP_DELAY_MS);
}