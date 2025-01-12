#pragma once

#include "Crosswind/Platforms/Platform.h"

#if defined (SERVICE_LOGGER)

  #include "Crosswind/Core/Application/Application.h"
  #include "Crosswind/Core/Arduino/HardwareSerial.h"
  #include "Crosswind/Core/Service/Service.h"

  #include <stdint.h>
  #include <mutex>
  #include <string>

  typedef uint8_t LogLevelType;
  enum class LogLevel : LogLevelType
  { 
    CRITICAL = 0,
    ERROR,
    WARN,
    INFO,
    DEBUG
  };

  class Logger final : public Service {

    public:
      static const std::string SERVICE_NAME;

    public:
      Logger() = default;
      virtual ~Logger() = default;

      virtual std::string name() {
        return SERVICE_NAME;
      }

      virtual void init();
      virtual void init(HardwareSerial* serial_port, LogLevel level);
      virtual void loop();

    public:
      void suspend();
      void resume();

      template<typename... Args>
      void log(LogLevel level, const char* fmt, Args... args) { 
        if (enabled && level <= logLevel && serialPort != nullptr) {
          std::lock_guard<std::mutex> lock(serialMutex);
          serialPort->printf(fmt, args...);
        }
      }

      template<typename... Args>
      void debug(const char* fmt, Args... args) { log (LogLevel::DEBUG, fmt, args...); }

      template<typename... Args>
      void info(const char* fmt, Args... args) { log (LogLevel::INFO, fmt, args...); }

      template<typename... Args>
      void warn(const char* fmt, Args... args) { log (LogLevel::WARN, fmt, args...); }

      template<typename... Args>
      void error(const char* fmt, Args... args) { log (LogLevel::ERROR, fmt, args...); }

      template<typename... Args>
      void critical(const char* fmt, Args... args) { log (LogLevel::CRITICAL, fmt, args...); }

    private:
      HardwareSerial* serialPort = nullptr;
      LogLevel logLevel = LogLevel::INFO;
      std::mutex serialMutex;
      bool enabled = true;

  };

  #define LOGGER() Application::application()->service<Logger>(Logger::SERVICE_NAME)
  #define DEBUG(...) LOGGER()->debug(__VA_ARGS__);
  #define INFO(...) LOGGER()->info(__VA_ARGS__);
  #define WARN(...) LOGGER()->warn(__VA_ARGS__);
  #define ERROR(...) LOGGER()->error(__VA_ARGS__);
  #define CRITICAL(...) LOGGER()->critical(__VA_ARGS__);

#endif // SERVICE_LOGGER
