#pragma once

#include "Crosswind/Platforms/Platform.h"

#if defined(SERVICE_EVENT_BROKER)

  class EventData {

    public:
      EventData() = default;
      virtual ~EventData() = default;
      
  };

#endif // SERVICE_EVENT_BROKER
