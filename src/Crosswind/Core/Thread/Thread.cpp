#include "Thread.h"

#if defined(CORE_THREAD)

#include "ThreadStartFailedException.h"

Thread::Thread(size_t stack_size, size_t prio, int core)
  : stackSize(stack_size), priority(prio), pinToCore(core) {
}

Thread::~Thread() {
  terminate();
}

void Thread::start() {
  pthread_attr_t attr;
  pthread_attr_init(&attr);
  pthread_attr_setstacksize(&attr, stackSize);
  
  auto err = pthread_create(&threadHandle, &attr, Thread::ThreadRunner, static_cast<void*>(this));
  if (err < 0) {
    throw ThreadStartFailedException(err);
  }
}

void Thread::terminate() {
  if (isRunning()) {
    pthread_cancel(threadHandle);
    pthread_join(threadHandle, NULL);
    isThreadRunning = false;
  }
}

bool Thread::isRunning() {
  return isThreadRunning;
}

void* Thread::ThreadRunner(void* data) {
  Thread* thread = static_cast<Thread*>(data);

  {
    auto config = esp_pthread_get_default_config();
    config.prio = thread->priority;
    config.pin_to_core = thread->pinToCore;
    esp_pthread_set_cfg(&config);
  }

  thread->isThreadRunning = true;
  thread->run();
  thread->isThreadRunning = false;
}

#else
  #pragma message("Feature [Core/Thread]: DISABLED")
#endif // CORE_THREAD
