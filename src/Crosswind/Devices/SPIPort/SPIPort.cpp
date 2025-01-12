#include "SPIPort.h"

#if defined(DEVICE_SPI_PORT)

SPIPort::SPIPort(uint8_t bus_num) : SPIClass(bus_num) {
  // TEMP TEMP TEMP
  Serial.printf("SPIPort::SPIPort\n");
  // TEMP TEMP TEMP
}

SPIPort::~SPIPort() {
  if (settings != nullptr) {
    delete settings;
    settings = nullptr;
  }
}

void SPIPort::begin(
  int8_t sck,
  int8_t miso,
  int8_t mosi,
  uint32_t frequency,
  int8_t ss,
  uint8_t order,
  uint8_t mode
) {
  // TEMP TEMP TEMP
  Serial.printf("SPIPort::begin\n");
  // TEMP TEMP TEMP

  SPIClass::begin(sck, miso, mosi, ss);
  setFrequency(frequency);

  settings = new SPISettings(frequency, order, mode);
}

void SPIPort::beginTransaction(int cs) {
  SPIClass::beginTransaction(*settings);
  digitalWrite(cs, LOW);
}

void SPIPort::endTransaction(int cs) {
  digitalWrite(cs, HIGH);
  SPIClass::endTransaction();
}

size_t SPIPort::writeThenRead(uint8_t* writeBuffer, size_t writeLength, uint8_t* readBuffer, size_t readLength, uint8_t sendValue) {
  #if defined(ARDUINO_ARCH_ESP32)
    if (writeLength > 0) {
      SPIClass::transferBytes(writeBuffer, nullptr, writeLength);
    }
  #else
    for (size_t x = 0; x < writeLength; x++) {
      SPIClass::transfer(writeBuffer[x]);
    }
  #endif

  for (size_t x = 0; x < readLength; x++) {
    readBuffer[x] = transfer(sendValue);
  }

  return readLength;
}

#else
  #pragma message("Feature [Device/SPIPort]: DISABLED")
#endif // DEVICE_SPI_PORT
