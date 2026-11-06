#pragma once

#include <Arduino.h>

#include "accelerometer.hpp"

namespace InitAccelerometerConstants {
    inline constexpr uint8_t PIN_X = A0;
    inline constexpr uint8_t PIN_Y = A1;
    inline constexpr uint8_t PIN_Z = A3;
    inline constexpr uint8_t PIN_GSELECT = A5;
    inline constexpr AccelerometerMode MODE = AccelerometerMode::HIGH_ACCEL;
    inline constexpr bool IS_DEBUG = false;
}