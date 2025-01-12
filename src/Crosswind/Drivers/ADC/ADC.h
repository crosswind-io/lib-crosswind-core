#pragma once

#include "Crosswind/Core/Driver/Driver.h"

#include <functional>

typedef std::function<int(void)> ADCRead;

class ADC : public Driver {

  public:
    ADC() = default;
    virtual ~ADC() = default;

    virtual std::string name() = 0;

    virtual void init() = 0;
    virtual void loop() = 0;

    virtual int channelCount() = 0;

    virtual void setResolution(int channel, uint8_t bits) = 0;
    virtual uint8_t getResolution(int channel) = 0;

    virtual int readChannel(int channel) = 0;

    virtual void startContinuousRead(int channel, bool start = true) = 0;
    virtual void stopContinuousRead(int channel) {
      startContinuousRead(channel, false);
    }
};
