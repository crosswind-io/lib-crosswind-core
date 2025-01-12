#pragma once

#include "Crosswind/Platforms/Platform.h"

#if defined(CORE_FIXED_QUEUE)

  #include <exception>

  class FixedQueueEmptyException : std::exception {
    public:
      FixedQueueEmptyException() {}
  };

#endif // CORE_FIXED_QUEUE
