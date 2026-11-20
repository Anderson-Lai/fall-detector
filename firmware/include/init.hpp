#pragma once

#include <cstdint>

namespace Init {
    void Setup();

    inline constexpr unsigned long SERIAL_BAUD_RATE = 115200;
    inline constexpr uint32_t LOOP_DELAY_MS = 10;

    void InitSerial(const unsigned long baudRate);
    void ChimeBuzzer(const uint32_t durationMS);

    inline constexpr uint32_t WIFI_CONNECT_RETRY_TIMEOUT_MS = 750;
    inline constexpr uint32_t WIFI_CONNECT_MAX_RETRIES = 100;
    bool ConnectToWifi();

    inline constexpr uint32_t TIME_SYNC_RETRY_TIMEOUT_MS = 750;
    inline constexpr uint32_t TIME_SYNC_MAX_RETRIES = 100;
    bool SynchronizeTime();
}