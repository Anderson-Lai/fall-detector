#pragma once

#include <array>

#include "accelerometer.hpp"

class Fall {
private:
    const Accelerometer m_accelerometer;
    std::array<double, 5> m_accelerationHistory;
    const uint32_t m_debounceLength;
public:
    Fall(const Accelerometer& accelerometer, const uint32_t debounceLengthMS);
public:
    void SampleAcceleration();

    static constexpr double FALL_THRESHOLD = 75.0; // m/s^2
    bool IsFallDetected() const;

    void ResetAccelerationHistory();
    void Debounce() const;
private:
    void InsertAcceleration(const double acceleration);
};