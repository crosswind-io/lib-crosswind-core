#if defined(ESP32)
  #include <SPI.h>
#elif defined(ESP8266)
  #include "Crosswind/Core/Arduino/esp8266/SPI.h"
#endif
