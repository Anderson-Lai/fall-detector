#pragma once

#include "accelerometer.hpp"
#include "fall.hpp"

namespace Globals {
    namespace InitAccelerometerConstants {
        inline constexpr uint8_t PIN_X = A0;
        inline constexpr uint8_t PIN_Y = A1;
        inline constexpr uint8_t PIN_Z = A3;
        inline constexpr uint8_t PIN_GSELECT = A5;
        inline constexpr AccelerometerMode MODE = AccelerometerMode::HIGH_ACCEL;
        inline constexpr bool IS_DEBUG = false;
    }
    
    inline const Accelerometer accelerometer(InitAccelerometerConstants::PIN_X, InitAccelerometerConstants::PIN_Y, 
        InitAccelerometerConstants::PIN_Z, InitAccelerometerConstants::PIN_GSELECT, 
        InitAccelerometerConstants::MODE, InitAccelerometerConstants::IS_DEBUG);
    inline Fall fall(accelerometer);
}