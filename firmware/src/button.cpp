#include <Arduino.h>

#include "button.hpp"

Button::Button(const uint8_t pin, const uint32_t debounceMS, const uint32_t doublePressMS) : m_pin(pin), 
    m_debounceMS(debounceMS), m_doublePressMS(doublePressMS), m_timeAtLastPressMS(0) {
    pinMode(pin, INPUT_PULLUP);
}

bool Button::IsDoublePressed() {
    const uint32_t currentTimeMS = millis();
    if (digitalRead(m_pin) == LOW) {
        if (currentTimeMS - m_timeAtLastPressMS <= m_debounceMS) {
            return false;
        }

        if (currentTimeMS - m_timeAtLastPressMS <= m_doublePressMS) {
            m_timeAtLastPressMS = 0;
            return true;
        }

        m_timeAtLastPressMS = currentTimeMS;
    }

    return false;
}