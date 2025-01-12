#pragma once

#include "Crosswind/Core/Defs/Polarity.h"
#include "Crosswind/Core/Driver/Driver.h"

#include <functional>

typedef std::function<void(uint8_t, int)> PinInterruptHandler;
typedef std::function<void(uint8_t, uint8_t)> BankInterruptHandler;

class GPIO : public Driver {

  public:
    GPIO() = default;
    virtual ~GPIO() = default;

    virtual std::string name() = 0;

    virtual void init() = 0;
    virtual void loop() = 0;

    virtual int bankCount() = 0;
    virtual int pinCount() = 0;

    virtual bool supportsPullUp(uint8_t pin) = 0;
    virtual bool supportsPullDown(uint8_t pin) = 0;
    virtual bool supportsInterruptOnChange(uint8_t pin) = 0;
    virtual bool supportsInversePolarity(uint8_t pin) = 0;

    virtual void pinMode(uint8_t pin, uint8_t mode) = 0;
    virtual void digitalWrite(uint8_t pin, uint8_t value) = 0;
    virtual int digitalRead(uint8_t pin) = 0;
    virtual void invertPolarity(uint8_t pin, bool invert) = 0;
    virtual void attachPinInterrupt(uint8_t pin, PinInterruptHandler handler) = 0;

    virtual uint8_t bankRead(uint8_t bank) = 0;
    virtual void bankWrite(uint8_t bank, uint8_t value) = 0;
    virtual void attachBankInterrupt(uint8_t bank, BankInterruptHandler handler) = 0;
};
