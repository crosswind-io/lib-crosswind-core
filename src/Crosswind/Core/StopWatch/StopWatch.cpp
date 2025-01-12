#include "StopWatch.h"

#if defined(CORE_STOP_WATCH)

#include "Crosswind/Core/Arduino/Arduino.h"

#include <limits>

StopWatch::StopWatch(StopWatchResolution resolution)
  : timeResolution(resolution) {
}

StopWatch::~StopWatch() {
}

void StopWatch::start() {
  startTime = now();
  state = StopWatchState::RUNNING;
}

void StopWatch::stop() {
  stopTime = now();
  state = StopWatchState::STOPPED;
}

void StopWatch::reset() {
  state = StopWatchState::RUNNING;
  stopTime = startTime = now();
}

bool StopWatch::isRunning() {
  return (state == StopWatchState::RUNNING);
}

uint32_t StopWatch::elapsed() {
  uint32_t elapsed_time = 0;

  switch (state) {
    
    case StopWatchState::STOPPED: {
      elapsed_time = StopWatch::timeDiffWithRollover(startTime, stopTime);
    } break;

    case StopWatchState::RUNNING: {
      elapsed_time = StopWatch::timeDiffWithRollover(startTime, now());
    } break;

  }

  return elapsed_time;
}

uint32_t StopWatch::now() {
  uint32_t now_time = 0;

  switch (timeResolution) {

    case StopWatchResolution::MILLIS: {
      now_time = StopWatch::nowMillis();
    } break;

    case StopWatchResolution::MICROS: {
      now_time = StopWatch::nowMicros();
    } break;

  }

  return now_time;
}

uint32_t StopWatch::nowMillis() {
  return millis();
}

uint32_t StopWatch::nowMicros() {
  return micros();
}

uint32_t StopWatch::timeDiffWithRollover(uint32_t start, uint32_t end) {
  if (end < start) {
    // rollover occurred
    return (std::numeric_limits<uint32_t>::max() - start) + end;
  } else {
    return end - start;
  }
}

#else
  #pragma message("Feature [Core/StopWatch]: DISABLED")
#endif // CORE_STOP_WATCH
