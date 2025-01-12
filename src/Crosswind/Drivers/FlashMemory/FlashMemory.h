#pragma once

#include "Crosswind/Core/Driver/Driver.h"

#include "Partition.h"

#include <string>

class FlashMemory : public Driver {

  public:
    FlashMemory() = default;
    virtual ~FlashMemory() = default;

    virtual std::string name() = 0;

    virtual void init() = 0;
    virtual void loop() = 0;

    virtual size_t getTotalPartitions() = 0;
    
    virtual Partition* getPartition(size_t index) = 0;
    virtual Partition* getPartition(const std::string& name) = 0;

};
