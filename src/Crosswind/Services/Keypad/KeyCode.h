#pragma once

#include "Crosswind/Platforms/Platform.h"

#if defined(SERVICE_KEYPAD)

    #include <stdint.h>

    typedef uint16_t KeyCode;
    const KeyCode KEY_NONE = 0;

#endif // SERVICE_KEYPAD
