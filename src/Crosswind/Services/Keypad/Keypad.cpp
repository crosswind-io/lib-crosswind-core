#include "Keypad.h"

#if defined(SERVICE_KEYPAD)

#include "Crosswind/Core/Application/Application.h"
#include "Crosswind/Core/Arduino/Arduino.h"
#include "Crosswind/Core/StopWatch/StopWatch.h"
#include "KeypadEvents.h"

#include <stdexcept>

const std::string Keypad::SERVICE_NAME = "Keypad";

Keypad::~Keypad() {
  // TODO
}

void Keypad::init() {
  throw std::invalid_argument("Missing 'key_map' argument.");
}

void Keypad::init(const std::map<KeyCode, int>& key_map) {
  auto eventBroker = Application::application()->service<EventBroker>();
  eventTopic = eventBroker->registerTopic(SERVICE_NAME);
  eventBroker->registerEvent<KeyStateChangedEventData>();
  eventBroker->registerEvent<KeyPressedEventData>();

  totalKeys = key_map.size();
  keys = new KeyMapEntry[totalKeys];
  keyInfo = new KeyInfo[totalKeys];
  isrKeyStates = new KeyState[totalKeys];

  uint32_t now = millis();

  size_t idx = 0;
  for (const auto& kv : key_map) {
    if (idx < totalKeys) {
      keys[idx].key = kv.first;
      keys[idx].gpio = kv.second;

      pinMode(keys[idx].gpio, INPUT_PULLDOWN);

      keyInfo[idx].state = isrKeyStates[idx] = ((digitalRead(this->keys[idx].gpio) == HIGH) ? KeyState::PRESSED : KeyState::RELEASED);
      keyInfo[idx].timestamp = now;

      attachInterrupt(digitalPinToInterrupt(keys[idx].gpio), Keypad::KeypadISR, CHANGE);

      idx++;
    }
  }
}

void Keypad::loop() {
  uint32_t now = millis();

  for (size_t idx = 0; idx < totalKeys; idx++) {
    if (isrKeyStates[idx] != keyInfo[idx].state) {
      auto eventBroker = Application::application()->service<EventBroker>();

      eventBroker->publish(eventTopic, [&](void* ptr){ new (ptr) KeyStateChangedEventData(keys[idx].key, isrKeyStates[idx], now); });
      keyInfo[idx].state = isrKeyStates[idx];

      if (keyInfo[idx].state == KeyState::RELEASED) {
        auto duration = StopWatch::timeDiffWithRollover(keyInfo[idx].timestamp, now);
        if (duration >= EXTRA_LONG_DURATION_MS) {
          eventBroker->publish(eventTopic, [&](void* ptr){ new (ptr) KeyPressedEventData(keys[idx].key, KeyPressType::EXTRA_LONG_PRESS); });
        } else if (duration >= LONG_DURATION_MS) {
          eventBroker->publish(eventTopic, [&](void* ptr){ new (ptr) KeyPressedEventData(keys[idx].key, KeyPressType::LONG_PRESS); });
        } else {
          eventBroker->publish(eventTopic, [&](void* ptr){ new (ptr) KeyPressedEventData(keys[idx].key, KeyPressType::NORMAL); });
        }
      }

      keyInfo[idx].timestamp = now;
    }
  }
}

void Keypad::KeypadISR() {
  auto keypad = Application::application()->service<Keypad>();
  for (size_t idx = 0; idx < keypad->totalKeys; idx++) {
    keypad->isrKeyStates[idx] = ((digitalRead(keypad->keys[idx].gpio) == HIGH) ? KeyState::PRESSED : KeyState::RELEASED);
  }
}

#else
  #pragma message("Feature [Service/Keypad]: DISABLED")
#endif // SERVICE_KEYPAD
