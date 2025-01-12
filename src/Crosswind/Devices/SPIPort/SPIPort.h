#pragma once

#include "Crosswind/Platforms/Platform.h"

#if defined(DEVICE_SPI_PORT)

  #include "Crosswind/Core/Arduino/Arduino.h"
  #include "Crosswind/Core/Arduino/SPI.h"

  class SPIPort : public SPIClass {

    public:
      SPIPort(uint8_t bus_num);
      virtual ~SPIPort();

      void begin(
        int8_t sck = -1,
        int8_t miso = -1,
        int8_t mosi = -1,
        uint32_t freq = 1000000,
        int8_t ss = -1,
        uint8_t order = MSBFIRST,
        uint8_t mode = SPI_MODE0
      );

      void beginTransaction(int cs);
      void endTransaction(int cs);

      size_t writeThenRead(uint8_t* writeBuffer, size_t writeLength, uint8_t* readBuffer, size_t readLength, uint8_t sendValue = 0xFF);

    private:
      SPISettings* settings = nullptr;

  };

#endif // DEVICE_SPI_PORT
