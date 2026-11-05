#include <Arduino.h>

#include "init.hpp"

void Init::InitSerial(int baudRate) {
    Serial.begin(baudRate);
    Serial.println("Starting...");
}

void Init::PulldownAllPins() {
    const uint8_t pins[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 20, 21 };
    for (uint8_t i = 0; i < sizeof(pins) / sizeof(uint8_t); ++i) {
        pinMode(pins[i], INPUT_PULLDOWN);
    }
}