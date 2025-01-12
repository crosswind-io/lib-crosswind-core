#pragma once

#include "PDO.h"

#include "Crosswind/Core/Driver/Driver.h"

#include <vector>

class USBPDSink : public Driver {

  public:
    USBPDSink() = default;
    virtual ~USBPDSink() = default;

    virtual std::string name() = 0;

    virtual void init() = 0;
    virtual void loop() = 0;

    virtual void reset() = 0;

    virtual bool isAttached() = 0;

    virtual bool supportsVoltage(uint8_t voltage) = 0;
    virtual std::vector<PDO> getSupportedPDOs() = 0;
    
    virtual void requestPDO(PDO pdo) = 0;
    virtual PDO getActivePDO() = 0;

};
