#include <Arduino.h>

#include "accelerometer.hpp"
#include "accelerometer_constants.hpp"

#include "init.hpp"

void setup() {
  Init::InitSerial(Init::SERIAL_BAUD_RATE);
  Init::PulldownAllPins();
}

void loop() {
  Accelerometer accel(InitAccelerometerConstants::PIN_X, InitAccelerometerConstants::PIN_Y, 
    InitAccelerometerConstants::PIN_Z, InitAccelerometerConstants::PIN_GSELECT, 
    InitAccelerometerConstants::MODE, InitAccelerometerConstants::IS_DEBUG);

  auto accelerations = accel.GetAccelerations();
  double magnitude = accel.GetAcclerationMagnitude();
  for (const auto& acceleration : accelerations) {
    Serial.print(acceleration);
    Serial.print(", ");
  }

  Serial.print("Magnitude: ");
  Serial.println(magnitude);

  delay(Init::LOOP_DELAY_MS);
}