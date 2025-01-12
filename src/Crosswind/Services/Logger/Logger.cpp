#include "Logger.h"

#if defined (SERVICE_LOGGER)

#include <cassert>

const std::string Logger::SERVICE_NAME = "Logger";

void Logger::init() {
  init(&Serial, LogLevel::INFO);
}

void Logger::init(HardwareSerial* serial_port, LogLevel level) {
  assert(serial_port != nullptr);

  serialPort = serial_port;
  logLevel = level;
}

void Logger::loop() {
}

void Logger::suspend() {
  enabled = false;
}

void Logger::resume() {
  enabled = true;
}

#else
  #pragma message("Feature [Service/Logger]: DISABLED")
#endif // SERVICE_LOGGER
