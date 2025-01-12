#pragma once

#include "Crosswind/Platforms/Platform.h"

#if defined(CORE_STOP_WATCH)

  #include <stdint.h>

  typedef uint8_t StopWatchResolutionType;
  enum class StopWatchResolution : StopWatchResolutionType {
    MILLIS = 0,
    MICROS
  };

  typedef uint8_t StopWatchStateType;
  enum class StopWatchState : StopWatchStateType {
    STOPPED = 0,
    RUNNING
  };

  class StopWatch final {

    public:
      StopWatch(StopWatchResolution resolution = StopWatchResolution::MILLIS);
      ~StopWatch();

      void start();
      void stop();
      void reset();

      bool isRunning();
      uint32_t elapsed();
      uint32_t now();

      static uint32_t nowMillis();
      static uint32_t nowMicros();
      static uint32_t timeDiffWithRollover(uint32_t start, uint32_t end);

    private:
      StopWatchResolution timeResolution = StopWatchResolution::MILLIS;

      StopWatchState state = StopWatchState::STOPPED;
      uint32_t startTime = 0;
      uint32_t stopTime = 0;

  };

#endif // CORE_STOP_WATCH
