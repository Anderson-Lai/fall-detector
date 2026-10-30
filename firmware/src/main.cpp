#include <Arduino.h>
#include "header.hpp"

#define ACCEL_X A5
#define ACCEL_Y A4
#define ACCEL_Z A3

void setup() {
  pinMode(ACCEL_X, INPUT);
  pinMode(ACCEL_Y, INPUT);
  pinMode(ACCEL_Z, INPUT);
  Serial.begin(9600);
}

void loop() {
  int x = analogRead(ACCEL_X);
  int y = analogRead(ACCEL_Y);
  int z = analogRead(ACCEL_Z);

  Serial.print("X: ");
  Serial.print(x);
  Serial.print(" Y: ");
  Serial.print(y);
  Serial.print(" Z: ");
  Serial.println(z);

  delay(500);
}
