#pragma once

#include "Crosswind/Platforms/Platform.h"

#if defined(CORE_THREAD)

  #include <exception>

  class ThreadStartFailedException : std::exception {
    public:
      ThreadStartFailedException(int err) : error(err) {}

      int error = 0;
  };

#endif // CORE_THREAD
