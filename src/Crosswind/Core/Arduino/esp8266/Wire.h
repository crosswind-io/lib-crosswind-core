#pragma once

#if defined(ESP8266)

#include <cstdint>

class TwoWire {
  public:
    TwoWire(uint8_t bus_num);
    virtual ~TwoWire();
};

#endif // ESP8266
