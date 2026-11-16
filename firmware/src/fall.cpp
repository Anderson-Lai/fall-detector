#include <Arduino.h>

#include <algorithm>
#include <cmath>

#include "fall.hpp"

Fall::Fall(const Accelerometer &accelerometer, const uint32_t debounceLengthMS)
    : m_accelerometer(accelerometer), m_debounceLength(debounceLengthMS)
{
    m_accelerationHistory.fill(0.0);
}

void Fall::SampleAcceleration() {
    double acceleration = m_accelerometer.GetAcclerationMagnitude();
    InsertAcceleration(acceleration);
}

bool Fall::IsFallDetected() const {
    return std::ranges::any_of(m_accelerationHistory, [this](const double acceleration) {
        return std::abs(acceleration - m_accelerationHistory.front()) > FALL_THRESHOLD;
    });
}

void Fall::ResetAccelerationHistory() {
    m_accelerationHistory.fill(0.0);
}

void Fall::Debounce() {
    delay(m_debounceLength);
}

void Fall::InsertAcceleration(const double acceleration) {
    for (std::size_t i = 0; i < m_accelerationHistory.size() - 1; ++i) {
        m_accelerationHistory[i] = m_accelerationHistory[i + 1];
    }
    m_accelerationHistory.back() = acceleration;
}

