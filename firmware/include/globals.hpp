#pragma once

#include "accelerometer.hpp"
#include "fall.hpp"
#include "credentials.hpp"
#include "button.hpp"
#include "api.hpp"

namespace Globals {
    inline constexpr uint8_t BUZZER_PIN = 21;

    enum class State {
        IDLE,
        QUEUED_MESSAGE,
        MESSAGE_PENDING
    };
    inline State state = State::IDLE;

    namespace InitButtonConstants {
        inline constexpr uint8_t PIN = 6;
        inline constexpr uint32_t DEBOUNCE_LENGTH_MS = 200;
        inline constexpr uint32_t DOUBLE_PRESS_LENGTH_MS = 500;
    }
    inline Button button(InitButtonConstants::PIN, InitButtonConstants::DEBOUNCE_LENGTH_MS,
        InitButtonConstants::DOUBLE_PRESS_LENGTH_MS);

    inline uint64_t alertTriggerTimeMS = UINT64_MAX;
    inline uint64_t alertSendTimeMS = UINT64_MAX;

    inline constexpr uint8_t RETRY_ATTEMPTS = 5;
    inline constexpr uint32_t RETRY_TIMEOUT_MS = 1'000;

    inline constexpr uint64_t MANUAL_ALERT_TIMEOUT_MS = 10'000;
    inline constexpr uint64_t AUTOMATIC_ALERT_TIMEOUT_MS = 20'000;

    namespace InitAccelerometerConstants {
        inline constexpr uint8_t PIN_X = A0;
        inline constexpr uint8_t PIN_Y = A1;
        inline constexpr uint8_t PIN_Z = A3;
        inline constexpr uint8_t PIN_GSELECT = 20;
        inline constexpr AccelerometerMode MODE = AccelerometerMode::HIGH_ACCEL;
    }
    inline const Accelerometer accelerometer(InitAccelerometerConstants::PIN_X, InitAccelerometerConstants::PIN_Y, 
        InitAccelerometerConstants::PIN_Z, InitAccelerometerConstants::PIN_GSELECT, 
        InitAccelerometerConstants::MODE);
    
    namespace InitFallConstants {
        inline constexpr uint32_t DEBOUNCE_LENGTH_MS = 1'000;
    }
    inline Fall fall(accelerometer, InitFallConstants::DEBOUNCE_LENGTH_MS);

    inline Api api(APICredentials::API_URL, APICredentials::CERTIFICATE, 
        APICredentials::API_KEY, APICredentials::DEVICE_ID);
}