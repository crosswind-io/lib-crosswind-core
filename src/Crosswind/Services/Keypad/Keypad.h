/***************************************************************************************************************************
 * Project:     Crosswind Framework
 * Author:      Kory Herzinger
 * 
 * File:        Keypad.h
 * Description: Declare the Keypad class.
 * Date:        08/27/2024
 **************************************************************************************************************************/

#pragma once

#include "Crosswind/Platforms/Platform.h"

#if defined(SERVICE_KEYPAD)

  #include "Crosswind/Core/Service/Service.h"
  #include "Crosswind/Services/EventBroker/EventBroker.h"
  #include "Crosswind/Services/EventBroker/EventTopic.h"
  #include "KeyCode.h"
  #include "KeyState.h"

  #include <map>
  #include <set>
  #include <string>

  class Keypad final : public Service {

    public:
      static const std::string SERVICE_NAME;

    public:
      Keypad() = default;
      virtual ~Keypad();

      virtual std::string name() {
        return SERVICE_NAME;
      }

      virtual std::set<std::string> dependsOn() {
        return {
          GET_SERVICE_NAME(EventBroker)
        };
      }

      virtual void init();
      virtual void init(const std::map<KeyCode, int>& key_map);
      virtual void loop();

    private:
      static const uint32_t LONG_DURATION_MS = 2000;
      static const uint32_t EXTRA_LONG_DURATION_MS = 5000;

    private:
      struct KeyMapEntry {
        KeyCode key;
        int gpio;
      };

      struct KeyInfo {
        KeyState state;
        uint32_t timestamp;
      };

    private:
      static void KeypadISR();

    private:
      EventTopic eventTopic = TOPIC_NONE;

      KeyMapEntry* keys = nullptr;
      size_t totalKeys = 0;

      KeyInfo* keyInfo = nullptr;
      volatile KeyState* isrKeyStates = nullptr;

  };

#endif // SERVICE_KEYPAD
