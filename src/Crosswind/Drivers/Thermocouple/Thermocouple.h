#pragma once

#include "Crosswind/Core/Defs/Polarity.h"
#include "Crosswind/Core/Driver/Driver.h"

#include "TemperatureUnit.h"

class Thermocouple : public Driver {

  public:
    Thermocouple() = default;
    virtual ~Thermocouple() = default;

    virtual std::string name() = 0;

    virtual void init() = 0;
    virtual void loop() = 0;

    virtual int alertCount() = 0;
    virtual int sensorCount() = 0;

    virtual void enableSensor(int sensor, bool enabled = true) = 0;
    virtual void disableSensor(int sensor) = 0;
    virtual bool isSensorEnabled(int sensor) = 0;

    virtual double readSensor(int sensor) = 0;

    virtual void setADCResolution(int sensor, uint8_t bits) = 0;
    virtual uint8_t getADCResolution(int sensor) = 0;

    virtual void setTemperatureUnit(int sensor, TemperatureUnit unit) = 0;
    virtual TemperatureUnit getTemperatureUnit(int sensor) = 0;

    virtual void enableAlert(int alert, uint8_t polarity, uint8_t mode, double temperature) = 0;
    virtual void disableAlert(int alert) = 0;

};
