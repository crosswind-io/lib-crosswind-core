#pragma once

#if defined(ESP8266)

#include "Stream.h"
#include "driver/i2c.h"

#include <cstdint>
#include <queue>

enum I2c {
  I2C0 = 0,
  I2C1,
  I2C_MAX
};

class TwoWire : public Stream {
  public:
    TwoWire(uint8_t bus_num);
    virtual ~TwoWire();

    bool setPins(int sda, int scl);
    
    bool begin(int sda = -1, int scl = -1, uint32_t frequency = 0, bool enableAckCheck = true);

    virtual size_t write(uint8_t ch);
    virtual size_t write(const uint8_t* buffer, size_t size);

    void beginTransmission(uint16_t address);
    void beginTransmission(uint8_t address);
    void beginTransmission(int address);

    int32_t endTransmission(bool sendStop = true);

    uint8_t requestFrom(uint16_t address, uint8_t size, bool sendStop = true);
    uint8_t requestFrom(uint8_t address, uint8_t size, bool sendStop = true);
    uint8_t requestFrom(int address, int size, bool sendStop = true);

    virtual int available();
    virtual int read();
    virtual int peek();
    virtual void flush();

  private:
    static const uint8_t I2C0_DEFAULT_SDA = 4;
    static const uint8_t I2C0_DEFAULT_SCL = 5;

    /* IMPLEMENTATION:
    static const uint32_t DEFAULT_TIMEOUT_MS = 1000;
    */
    static const uint32_t DEFAULT_TIMEOUT_MS = 5000;

  private:
    uint8_t i2cBus = I2C0;
    int sdaPin = -1;
    int sclPin = -1;
    bool ackCheck = true;

    bool i2cInitialized = false;

    i2c_cmd_handle_t txCmd = nullptr;
    i2c_cmd_handle_t rxCmd = nullptr;

    std::queue<uint8_t> rxBuffer;
};

#if !defined(NO_GLOBAL_INSTANCES) && !defined(NO_GLOBAL_TWO_WIRE)
  extern TwoWire Wire;
#endif

#endif // ESP8266
