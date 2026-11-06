#pragma once

#include <array>

#include "accelerometer.hpp"

class Fall {
private:
    Accelerometer m_accelerometer;
    std::array<double, 5> m_accelerationHistory;
public:
    Fall(const Accelerometer& accelerometer);
public:
    void SampleAcceleration();

    static constexpr double FALL_THRESHOLD = 100.0; // m/s^2
    bool IsFallDetected() const;
    
    void ResetAccelerationHistory();
private:
    void InsertAcceleration(const double acceleration);
};