/***************************************************************************************************************************
 * Project:     Crosswind Framework
 * Author:      Kory Herzinger
 * 
 * File:        StatusLED.h
 * Description: Declare the StatusLED class.
 * Date:        01/21/2022
 **************************************************************************************************************************/

#pragma once

#include "Crosswind/Platforms/Platform.h"

#if defined(SERVICE_STATUS_LED)

  #include "Crosswind/Core/Service/Service.h"
  #include "Crosswind/Core/StopWatch/StopWatch.h"

  #include <stdint.h>
  #include <string>

  typedef uint8_t StatusLEDBlinkModeType;
  enum class StatusLEDBlinkMode : StatusLEDBlinkModeType {
    OFF = 0,
    SOLID_ON,
    BLINK,
    LONG_BLINK,
    FAST_BLINK,
    STROBE,
    HEARTBEAT
  };

  class StatusLED final : public Service {

    public:
      static const std::string SERVICE_NAME;

    public:
      StatusLED() = default;
      virtual ~StatusLED() = default;

      virtual std::string name() {
        return SERVICE_NAME;
      }

      virtual void init();
      virtual void init(int led_pin);
      virtual void loop();

    public:
      void setBlinkMode(StatusLEDBlinkMode blink_mode);

    private:
      int ledPin = 0;
      StatusLEDBlinkMode blinkMode = StatusLEDBlinkMode::OFF;
      StopWatch stopWatch;
      uint8_t counter = 0;

  };

#endif // SERVICE_STATUS_LED
