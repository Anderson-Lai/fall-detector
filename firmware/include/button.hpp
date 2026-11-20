#pragma once

#include <cstdint>

class Button {
private:
    const uint8_t m_pin;
    const uint32_t m_debounceMS;
    const uint32_t m_doublePressMS;
    uint32_t m_timeAtLastPressMS;
public:
    Button(const uint8_t pin, const uint32_t debounceMS, const uint32_t doublePressMS);
    bool IsDoublePressed();
};