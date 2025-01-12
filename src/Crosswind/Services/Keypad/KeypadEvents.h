#pragma once

#include "Crosswind/Platforms/Platform.h"

#if defined(SERVICE_KEYPAD)

  #include "Crosswind/Services/EventBroker/EventData.h"
  #include "KeyCode.h"
  #include "KeyState.h"

  #include <stdint.h>

  typedef uint8_t KeyPressTypeType;
  enum class KeyPressType : KeyPressTypeType
  { 
    NORMAL = 0,
    LONG_PRESS,
    EXTRA_LONG_PRESS
  };

  typedef uint8_t KeypadEventType;
  enum class KeypadEvent : KeypadEventType
  { 
    KEY_STATE_CHANGED = 0,
    KEY_PRESSED
  };

  class KeypadEventData : public EventData {

    public:
      KeypadEventData(KeypadEvent event) : event(event) {}
      virtual ~KeypadEventData() {}

    public:
      KeypadEvent event;

  };

  class KeyStateChangedEventData : public KeypadEventData {

    public:
      KeyStateChangedEventData(KeyCode key, KeyState state, uint32_t time) 
        : KeypadEventData(KeypadEvent::KEY_STATE_CHANGED), key(key), state(state), time(time) {}
      virtual ~KeyStateChangedEventData() {}

    public:
      KeyCode key = KEY_NONE;
      KeyState state;
      uint32_t time;
  };

  class KeyPressedEventData : public KeypadEventData {

    public:
      KeyPressedEventData(KeyCode key, KeyPressType type)
        : KeypadEventData(KeypadEvent::KEY_PRESSED), key(key), type(type) {}
      virtual ~KeyPressedEventData() {}

    public:
      KeyCode key = KEY_NONE;
      KeyPressType type;

  };

#endif // SERVICE_KEYPAD
