#pragma once

#include "Crosswind/Core/Driver/Driver.h"
#include "Crosswind/Core/Hardware/Hardware.h"
#include "Crosswind/Core/Service/Service.h"

#include <list>
#include <map>
#include <string>

class Application {
  
  public:
    Application() = default;
    virtual ~Application() = default;

    virtual Hardware* hardware() = 0;

    virtual void init() = 0;
    virtual void loop() = 0;

    virtual void handleException(const std::exception& ex);
    virtual void handleUnknownException();

  public:
    void runInit();
    void runLoop();

  public:
    template <typename Drv>
    Drv* registerDriver() {
      auto driver = new Drv();
      drivers.emplace(driver->name(), driver);
      return driver;
    }

    template <typename Svc>
    Svc* registerService() {
      auto service = new Svc();
      services.emplace(service->name(), service);
      return service;
    }

    template <typename Drv>
    Drv* driver(const std::string& name) {
      auto drv = drivers.find(name);
      if (drv == drivers.end()) {
        return nullptr; // TODO: throw
      }
      return static_cast<Drv*>(drv->second);
    }

    template <typename Drv>
    Drv* driver() {
      return driver<Drv>(GET_DRIVER_NAME(Drv));
    }

    template <typename Svc>
    Svc* service(const std::string& name) {
      auto svc = services.find(name);
      if (svc == services.end()) {
        return nullptr; // TODO: throw
      }
      return static_cast<Svc*>(svc->second);
    }

    template <typename Svc>
    Svc* service() {
      return service<Svc>(GET_SERVICE_NAME(Svc));
    }

  public:
    static Application* application();

  private:
    std::map<std::string, Driver*> drivers;
    std::list<Driver*> driverLoop;

    std::map<std::string, Service*> services;
    std::list<Service*> orderedServiceLoop;

    static void terminationHandler();

};

extern Application* cw_main();
