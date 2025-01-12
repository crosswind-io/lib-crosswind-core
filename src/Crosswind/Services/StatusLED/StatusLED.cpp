#include "StatusLED.h"

#if defined(SERVICE_STATUS_LED)

#include "Crosswind/Core/Arduino/Arduino.h"

#include <stdexcept>

const std::string StatusLED::SERVICE_NAME = "StatusLED";

void StatusLED::init() {
  throw std::invalid_argument("Missing 'led_pin' argument.");
}

void StatusLED::init(int led_pin) {
  ledPin = led_pin;
  pinMode(ledPin, OUTPUT);
}

void StatusLED::loop() {
  bool next_cycle = false;
  bool reset_cycle = false;

  switch (blinkMode) {
    
    case StatusLEDBlinkMode::OFF: {
      digitalWrite(ledPin, LOW);
    } break;

    case StatusLEDBlinkMode::SOLID_ON: {
      digitalWrite(ledPin, HIGH);
    } break;

    case StatusLEDBlinkMode::BLINK: {
      if ((counter % 2) == 0) {
        if (stopWatch.elapsed() >= 500) {
          digitalWrite(ledPin, HIGH);
          next_cycle = true;
        }
      } else {
        if (stopWatch.elapsed() >= 500) {
          digitalWrite(ledPin, LOW);
          reset_cycle = true;
        }
      }
    } break;

    case StatusLEDBlinkMode::LONG_BLINK: {
      if ((counter % 2) == 0) {
        if (stopWatch.elapsed() >= 1000) {
          digitalWrite(ledPin, HIGH);
          next_cycle = true;
        }
      } else {
        if (stopWatch.elapsed() >= 1000) {
          digitalWrite(ledPin, LOW);
          reset_cycle = true;
        }
      }
    } break;

    case StatusLEDBlinkMode::FAST_BLINK: {
      if ((counter % 2) == 0) {
        if (stopWatch.elapsed() >= 250) {
          digitalWrite(ledPin, HIGH);
          next_cycle = true;
        }
      } else {
        if (stopWatch.elapsed() >= 250) {
          digitalWrite(ledPin, LOW);
          reset_cycle = true;
        }
      }
    } break;

    case StatusLEDBlinkMode::STROBE: {
      if ((counter % 2) == 0) {
        if (stopWatch.elapsed() >= 100) {
          digitalWrite(ledPin, HIGH);
          next_cycle = true;
        }
      } else {
        if (stopWatch.elapsed() >= 100) {
          digitalWrite(ledPin, LOW);
          reset_cycle = true;
        }
      }
    } break;

    case StatusLEDBlinkMode::HEARTBEAT: {
      if ((counter % 2) == 0) {
        if (counter == 4) {
          if (stopWatch.elapsed() >= (1000 - 100)) {
            reset_cycle = true;
          }
        } else {
          if (stopWatch.elapsed() >= 100) {
            digitalWrite(ledPin, HIGH);
            next_cycle = true;
          }
        }
      } else {
        if (stopWatch.elapsed() >= 100) {
          digitalWrite(ledPin, LOW);
          next_cycle = true;
        }
      }
    } break;

  }

  if (next_cycle || reset_cycle) {
    if (next_cycle) {
      counter++;
    }
    if (reset_cycle) {
      counter = 0;
    }
    stopWatch.reset();
  }
}

void StatusLED::setBlinkMode(StatusLEDBlinkMode blink_mode) {
  blinkMode = blink_mode;
  stopWatch.reset();
  counter = 0;
}

#else
  #pragma message("Feature [Service/StatusLED]: DISABLED")
#endif // SERVICE_STATUS_LED
