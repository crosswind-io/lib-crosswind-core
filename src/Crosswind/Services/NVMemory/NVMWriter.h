#pragma once

#include "Crosswind/Platforms/Platform.h"

#if defined(SERVICE_NV_MEMORY)

  #include "Crosswind/Core/Service/Service.h"

  #include "NVMemory.h"
  #include "NVMNamespace.h"

  #include <functional>
  #include <string>

  // TODO: make a service that depends on NVMemory ??? <<< not sure what I meant here
  // TODO: but, this should probably not be a service... the pattern is inheritance!
  class NVMWriter : public Service {

    public:
      static const std::string SERVICE_NAME;

    public:
      NVMWriter() = default;
      virtual ~NVMWriter();

      virtual std::string name() {
        return SERVICE_NAME;
      }

      virtual void init();
      virtual void init(const char* nvmns, bool writable = false);
      virtual void init(const std::string& nvmns, bool writable = false);
      virtual void init(NVMNamespace* nvmns);
      virtual void loop();

      virtual std::set<std::string> dependsOn() {
        return std::set<std::string>({ NVMemory::SERVICE_NAME });
      }

    public:
      void enableWrite();
      void disableWrite();

      void write(std::function<void(void)> writer);

    protected:
      NVMNamespace* nvm = nullptr;

  };

#endif // SERVICE_NV_MEMORY
