#pragma once

#include "Crosswind/Platforms/Platform.h"

#if defined(CORE_THREAD)

  #include <pthread.h>
  #include <atomic>

  #include "esp_pthread.h"

  class Thread {

    public:
      Thread(
        size_t stack_size = DEFAULT_STACK_SIZE,
        size_t prio = DEFAULT_PRIORITY,
        int core = DEFAULT_CORE
      );
      virtual ~Thread();

      void start();
      void terminate();

      bool isRunning();

    protected:
      virtual void run() = 0;

    public:
      static const size_t DEFAULT_STACK_SIZE = 4096;
      static const size_t DEFAULT_PRIORITY = CONFIG_PTHREAD_TASK_PRIO_DEFAULT;
      static const int DEFAULT_CORE = 0x7FFFFFFF;

    private:
      static void* ThreadRunner(void* data);

    private:
      size_t stackSize = DEFAULT_STACK_SIZE;
      size_t priority = DEFAULT_PRIORITY;
      int pinToCore = DEFAULT_CORE;
      pthread_t threadHandle;
      volatile std::atomic<bool> isThreadRunning;

  };

#endif // CORE_THREAD
