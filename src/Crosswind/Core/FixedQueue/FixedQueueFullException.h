#pragma once

#include "Crosswind/Platforms/Platform.h"

#if defined(CORE_FIXED_QUEUE)

  #include <exception>

  class FixedQueueFullException : std::exception {
    public:
      FixedQueueFullException() {}
  };

#endif // CORE_FIXED_QUEUE
