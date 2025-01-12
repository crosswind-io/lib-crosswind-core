#pragma once

#include "Crosswind/Platforms/Platform.h"

#if defined(DEVICE_I2C_PORT)

  #include "Crosswind/Core/Arduino/Wire.h"

  #if defined (__USE_CUSTOM_TWOWIRE__)
    #include "Crosswind/Core/Thread/Thread.h"
    #include "driver/i2c.h"
  #endif

  #if defined (__USE_CUSTOM_TWOWIRE__)
    typedef void(*OnRequestCallback)(void);
    typedef void(*OnReceiveCallback)(uint8_t*, int);
  #endif

  class I2CPort : public TwoWire
  #if defined (__USE_CUSTOM_TWOWIRE__)
    , public Thread
  #endif
  {

    public:
      I2CPort(uint8_t bus_num, uint16_t timeOutMillis = 50);
      virtual ~I2CPort();

      #if defined (__USE_CUSTOM_TWOWIRE__)
        void setTimeOut(uint16_t timeOutMillis);
        uint16_t getTimeOut();

        bool begin(int sda = -1, int scl = -1, uint32_t frequency = 0);
        bool begin(uint8_t address, int sda = -1, int scl = -1);

        bool end();

        void beginTransmission(uint16_t address);
        void beginTransmission(uint8_t address);
        void beginTransmission(int address);

        uint8_t endTransmission(bool sendStop);
        uint8_t endTransmission();

        size_t write(uint8_t data);
        size_t write(const uint8_t* data, size_t quantity);

        int read();

        uint8_t requestFrom(uint16_t address, uint8_t size, bool sendStop);
        uint8_t requestFrom(uint16_t address, uint8_t size, uint8_t sendStop);
        uint8_t requestFrom(uint16_t address, uint8_t size);
        uint8_t requestFrom(uint8_t address, uint8_t size, uint8_t sendStop);
        uint8_t requestFrom(uint8_t address, uint8_t size);
        uint8_t requestFrom(int address, int size, int sendStop);
        uint8_t requestFrom(int address, int size);

        void onReceive(OnReceiveCallback callback);
        void onRequest(OnRequestCallback callback);
      #endif

    protected:
      #if defined (__USE_CUSTOM_TWOWIRE__)
        virtual void run();
      #endif

    protected:
      #if defined (__USE_CUSTOM_TWOWIRE__)
        i2c_port_t port = I2C_NUM_MAX;
        uint32_t timeout = 50;
        uint16_t device_address = 0;

        OnReceiveCallback on_receive = nullptr;
        OnRequestCallback on_request = nullptr;
      #endif

  };

#endif // DEVICE_I2C_PORT
