#pragma once

#include "Crosswind/Platforms/Platform.h"

#if defined(SERVICE_NV_MEMORY)

  #include "NVMemory.h"
  #include "NVMNamespace.h"

  #include <functional>
  #include <string>

  class NVMWriter {

    public:
      NVMWriter() = default;
      virtual ~NVMWriter();

      virtual void init();
      virtual void init(const char* nvmns, bool writable = false);
      virtual void init(const std::string& nvmns, bool writable = false);
      virtual void init(NVMNamespace* nvmns);

      void enableWrite();
      void disableWrite();

    protected:
      bool write(std::function<bool(NVMNamespace*)> writer);

    protected:
      NVMNamespace* nvm = nullptr;

  };

#endif // SERVICE_NV_MEMORY
