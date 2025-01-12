#pragma once

#include "Crosswind/Platforms/Platform.h"

#if defined(SERVICE_NV_MEMORY)

  #include <exception>

  class NVMEraseException : std::exception {
    public:
      NVMEraseException(const char* message) : message(message) {}

      virtual char const* what() const noexcept {
        return message;
      }

    private:
      const char* message = nullptr;
  };

#endif // SERVICE_NV_MEMORY
