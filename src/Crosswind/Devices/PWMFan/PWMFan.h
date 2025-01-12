#pragma once

#include "Crosswind/Platforms/Platform.h"

#if defined(DEVICE_PWM_FAN)

  #include <cstdint>
  #include <limits>

  class PWMFan {

    public:
      static constexpr uint16_t MAX_RPM = std::numeric_limits<uint16_t>::max();

    public:
      PWMFan(int pwm_pin, uint16_t max_rpm);
      virtual ~PWMFan() = default;

      void turnOff();

      uint16_t getMaxRPM();
      uint16_t getRPM();
      void setRPM(uint16_t rpm = MAX_RPM);

      double getSpeed();
      void setSpeed(double speed = 100.0);

    private:
      void setPWM(uint8_t pwm);

    protected:
      int pwmPin = -1;
      uint16_t maxRpm = 0;
      uint8_t currentPwm = 0;

  };

#endif // DEVICE_PWM_FAN
