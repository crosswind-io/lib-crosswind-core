#pragma once

#include "Crosswind/Platforms/Platform.h"

#if defined(CORE_ANALOG_WRITE)

  #include <cstdint>

  int analogWriteChannel(uint8_t pin);

  void analogWriteFrequency(double frequency);
  void analogWriteFrequency(uint8_t pin, double frequency);

  void analogWriteResolution(uint8_t resolution);
  void analogWriteResolution(uint8_t pin, uint8_t resolution);

  void analogWrite(uint8_t pin, uint32_t value, uint32_t valueMax = 255);

#endif // CORE_ANALOG_WRITE
