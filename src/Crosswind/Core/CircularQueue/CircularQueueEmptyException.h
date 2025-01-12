#pragma once

#include "Crosswind/Platforms/Platform.h"

#if defined(CORE_CIRCULAR_QUEUE)

  #include <exception>

  class CircularQueueEmptyException : std::exception {
    public:
      CircularQueueEmptyException() {}
  };

#endif // CORE_CIRCULAR_QUEUE
