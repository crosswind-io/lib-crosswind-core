#pragma once

#include "Crosswind/Platforms/Platform.h"

#if defined(SERVICE_EVENT_BROKER)

  #include <exception>

  class EventBrokerQueueFullException : std::exception {
    public:
      EventBrokerQueueFullException() {}
  };

#endif // SERVICE_EVENT_BROKER
