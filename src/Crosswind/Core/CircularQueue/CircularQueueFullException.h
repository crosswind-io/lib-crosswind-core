#pragma once

#include "Crosswind/Platforms/Platform.h"

#if defined(CORE_CIRCULAR_QUEUE)

  #include <exception>

  class CircularQueueFullException : std::exception {
    public:
      CircularQueueFullException() {}
  };

#endif // CORE_CIRCULAR_QUEUE
