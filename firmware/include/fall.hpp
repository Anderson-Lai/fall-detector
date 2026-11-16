#pragma once

#include <array>

#include "accelerometer.hpp"

class Fall {
private:
    Accelerometer m_accelerometer;
    std::array<double, 5> m_accelerationHistory;
    uint32_t m_debounceLength = 0;
public:
    Fall(const Accelerometer& accelerometer, const uint32_t debounceLengthMS);
public:
    void SampleAcceleration();

    static constexpr double FALL_THRESHOLD = 75.0; // m/s^2
    bool IsFallDetected() const;

    void ResetAccelerationHistory();
    void Debounce();
private:
    void InsertAcceleration(const double acceleration);
};