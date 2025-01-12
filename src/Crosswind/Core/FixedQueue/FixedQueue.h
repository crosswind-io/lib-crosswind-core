#pragma once

#include "Crosswind/Platforms/Platform.h"

#if defined(CORE_FIXED_QUEUE)

  #include "FixedQueueEmptyException.h"
  #include "FixedQueueFullException.h"

  #include <stddef.h>
  #include <string.h>

  template <typename T, size_t Capacity>
  class FixedQueue {
    public:
      FixedQueue() {
        _capacity = Capacity;
        _queue = new T[_capacity];
        _end = 0;
      }

      ~FixedQueue() {
        delete[] _queue;
        _queue = nullptr;
        _capacity = 0;
        _end = 0;
      }

      void enqueue(T& _value) {
        if (full()) {
          throw FixedQueueFullException();
        }

        _queue[_end] = _value;
        _end++;
      }

      void enqueue(T _values[], size_t _length) {
        if (full() || (_end + _length) > _capacity) {
          throw FixedQueueFullException();
        }

        memcpy(&_queue[_end], _values, _length);
        _end += _length;
      }

      T& dequeue() {
        if (empty()) {
          throw FixedQueueEmptyException();
        }

        T* item = &_queue[0];
        memcpy(_queue, &_queue[1], size() - 1);
        _end--;

        return *item;
      }

      void dequeue(size_t _count) {
        if (_count > _end) {
          _end = 0;
        } else {
          memcpy(_queue, &_queue[_count], size() - _count);
          _end -= _count;
        }
      }

      T& front() {
        if (empty()) {
          throw FixedQueueEmptyException();
        }

        T* item = &_queue[0];
        return *item;
      }

      void clear() {
        _end = 0;
      }

      const T* c_buf() {
        return _queue;
      }

      size_t size() {
        return _end;
      }

      size_t capacity() {
        return _capacity;
      }

      bool full() {
        return (_end == _capacity);
      }

      bool empty() {
        return (_end == 0);
      }

    private:
      T* _queue = nullptr;
      size_t _capacity = 0;
      size_t _end = 0;
  };

#endif // CORE_FIXED_QUEUE
