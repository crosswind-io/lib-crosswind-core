#pragma once

#include "Crosswind/Platforms/Platform.h"

#if defined(SERVICE_NV_MEMORY)

  #include "Crosswind/Core/Service/Service.h"

  #include <string>

  class NVMemory : public Service {

    public:
      static constexpr const char* SERVICE_NAME = "NVMemory";

    public:
      NVMemory() = default;
      virtual ~NVMemory();

      virtual std::string name() {
        return SERVICE_NAME;
      }

      virtual void init();
      virtual void loop();

    public:
      void erase();

  };

#endif // SERVICE_NV_MEMORY
