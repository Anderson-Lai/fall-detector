#pragma once

#include <cstdint>

namespace Init {
    inline constexpr unsigned long SERIAL_BAUD_RATE = 115200;
    inline constexpr uint32_t LOOP_DELAY_MS = 10;

    void InitSerial(const unsigned long baudRate);
    void PulldownAllPins();
    bool ConnectToWifi();
}