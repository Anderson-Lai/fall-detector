#pragma once

#include "accelerometer.hpp"
#include "fall.hpp"
#include "credentials.hpp"
#include "api.hpp"

namespace Globals {
    namespace InitAccelerometerConstants {
        inline constexpr uint8_t PIN_X = A0;
        inline constexpr uint8_t PIN_Y = A1;
        inline constexpr uint8_t PIN_Z = A3;
        inline constexpr uint8_t PIN_GSELECT = 8;
        inline constexpr AccelerometerMode MODE = AccelerometerMode::HIGH_ACCEL;
        inline constexpr bool IS_DEBUG = false;
    }
    inline const Accelerometer accelerometer(InitAccelerometerConstants::PIN_X, InitAccelerometerConstants::PIN_Y, 
        InitAccelerometerConstants::PIN_Z, InitAccelerometerConstants::PIN_GSELECT, 
        InitAccelerometerConstants::MODE, InitAccelerometerConstants::IS_DEBUG);
    
    namespace InitFallConstants {
        inline constexpr uint32_t DEBOUNCE_LENGTH_MS = 1'000;
    }
    inline Fall fall(accelerometer, InitFallConstants::DEBOUNCE_LENGTH_MS);

    inline Api api(APICredentials::API_URL, APICredentials::CERTIFICATE, 
        APICredentials::API_KEY, APICredentials::DEVICE_ID);
}