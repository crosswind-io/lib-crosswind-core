#pragma once

#include <cstdint>

typedef uint8_t TemperatureUnitType;
enum class TemperatureUnit : TemperatureUnitType {
  CELSIUS = 0,
  FAHRENHEIT,
};
