#pragma once

#include "Crosswind/Platforms/Platform.h"

#if defined(SERVICE_KEYPAD)

  #include <stdint.h>

  typedef uint8_t KeyStateType;
  enum class KeyState : KeyStateType
  { 
    RELEASED = 0,
    PRESSED
  };

#endif // SERVICE_KEYPAD
