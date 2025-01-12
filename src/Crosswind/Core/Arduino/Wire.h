#if defined(ESP32)
  #include <Wire.h>
#elif defined(ESP8266)
  #include "Crosswind/Core/Arduino/esp8266/Wire.h"
#endif
