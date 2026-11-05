#pragma once

#include <Arduino.h>

#include "accelerometer.hpp"

namespace InitAccelerometerConstants {
    static constexpr uint8_t PIN_X = A0;
    static constexpr uint8_t PIN_Y = A1;
    static constexpr uint8_t PIN_Z = A3;
    static constexpr uint8_t PIN_GSELECT = A5;
    static constexpr AccelerometerMode MODE = AccelerometerMode::HIGH_ACCEL;
    static constexpr bool IS_DEBUG = false;
}