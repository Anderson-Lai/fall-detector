#pragma once

#include "accelerometer.hpp"
#include "accelerometer_init.hpp"
#include "fall.hpp"

namespace Globals {
    inline const Accelerometer accelerometer(InitAccelerometerConstants::PIN_X, InitAccelerometerConstants::PIN_Y, 
        InitAccelerometerConstants::PIN_Z, InitAccelerometerConstants::PIN_GSELECT, 
        InitAccelerometerConstants::MODE, InitAccelerometerConstants::IS_DEBUG);
    inline Fall fall(accelerometer);
}