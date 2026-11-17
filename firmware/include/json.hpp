#pragma once

#include <Arduino.h>

#include "request_types.hpp"

namespace JSON {
    String SerializeAlert(const Alert& alert);
}