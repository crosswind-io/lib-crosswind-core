#pragma once

#include "Crosswind/Platforms/Platform.h"

#if defined(SERVICE_EVENT_BROKER)

    #include <stdint.h>

    typedef uint8_t EventTopic;

    const EventTopic TOPIC_NONE = 0;

#endif // SERVICE_EVENT_BROKER
