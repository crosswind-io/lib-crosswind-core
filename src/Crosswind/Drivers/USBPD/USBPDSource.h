#pragma once

#include "Crosswind/Core/Driver/Driver.h"

class USBPDSource : public Driver {

  public:
    USBPDSource() = default;
    virtual ~USBPDSource() = default;

    virtual std::string name() = 0;

    virtual void init() = 0;
    virtual void loop() = 0;

};
