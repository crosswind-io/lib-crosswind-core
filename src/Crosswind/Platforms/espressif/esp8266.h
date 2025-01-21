#pragma once

#if defined(ESP8266)
  // Core features
  // #define CORE_ANALOG_WRITE             1
  // #define CORE_CIRCULAR_QUEUE           1
  // #define CORE_FIXED_QUEUE              1
  #define CORE_STOP_WATCH               1
  // #define CORE_THREAD                   1
  // #define CORE_EXCEPTIONS               1

  // Device features
  #define DEVICE_I2C_PORT               1
  // #define DEVICE_PWM_FAN                1
  // #define DEVICE_SPI_PORT               1

  // Services features
  // #define SERVICE_EVENT_BROKER          1
  // #define SERVICE_KEYPAD                1
  #define SERVICE_LOGGER                1
  // #define SERVICE_NV_MEMORY             1
  // #define SERVICE_STATUS_LED            1
#endif // ESP8266
