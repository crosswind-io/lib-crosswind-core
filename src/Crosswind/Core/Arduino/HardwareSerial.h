#if defined(ESP32)
  #include <HardwareSerial.h>
#elif defined(ESP8266)
  #include "Crosswind/Core/Arduino/esp8266/HardwareSerial.h"
#endif
