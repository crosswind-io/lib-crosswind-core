#include "Application.h"

#include "Crosswind/Core/Arduino/Arduino.h"

#include <cstdlib>

static Application* app = nullptr;

Application* Application::application() {
  return app;
}

void Application::handleException(const std::exception &ex) {
  // NOTE: ignore the exception
}

void Application::handleUnknownException() {
  // NOTE: ignore the exception
}

void Application::runInit() {
  // setup the global exception handler
  std::set_terminate(Application::terminationHandler);

  // initialize the hardware
  hardware()->init();

  // initialize the application
  init();

  // generate the driver loop
  driverLoop.clear();
  for (const auto& drv : drivers) {
    driverLoop.push_back(drv.second);
  }

  // order the service loop
  orderedServiceLoop.clear();
  for (const auto& svc : services) {
    orderedServiceLoop.push_back(svc.second);
  }
  orderedServiceLoop.sort([](Service* a, Service* b) {
    auto deps = b->dependsOn();
    return (deps.find(a->name()) != deps.end());
  });
}

void Application::runLoop() {
  // run the hardware loop
  hardware()->loop();

  // run the driver loop
  for(auto drv : driverLoop) {
    drv->loop();
  }

  // run the service loop
  for(auto svc : orderedServiceLoop) {
    svc->loop();
  }

  // run the application loop
  loop();
}

void Application::terminationHandler() {
  static bool rethrow = false;

  try {
    if (!rethrow++) throw;
  } catch (const std::exception& ex) {
    app->handleException(ex);
  } catch (...) {
    app->handleUnknownException();
  }

  std::abort();
}

/***************************************************************************************************************************
 * Arduino functions
 **************************************************************************************************************************/

// Setup the device. Called once on program start.
void setup() {
  // invoke the `cw_main` entrypoint
  app = cw_main();

  // initialize the application
  app->runInit();
}

// The main loop. Called once every time through the program loop.
void loop() {
  app->runLoop();
}
