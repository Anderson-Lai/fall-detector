#pragma once

#include <cstdint>

namespace Init {
    inline constexpr unsigned long SERIAL_BAUD_RATE = 115200;
    inline constexpr uint32_t LOOP_DELAY_MS = 10;

    void InitSerial(const unsigned long baudRate);
    void PulldownAllPins();

    inline constexpr uint32_t WIFI_CONNECT_RETRY_TIMEOUT_MS = 750;
    inline constexpr uint32_t WIFI_CONNECT_MAX_RETRIES = 100;
    bool ConnectToWifi();
}