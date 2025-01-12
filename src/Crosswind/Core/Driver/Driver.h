#pragma once

#include <set>
#include <string>

class Driver {
  
  public:
    Driver() = default;
    virtual ~Driver() = default;

    virtual std::string name() = 0;

    virtual void init() = 0;
    virtual void loop() = 0;

};

#define GET_DRIVER_NAME(DRV) DRV::DRIVER_NAME
