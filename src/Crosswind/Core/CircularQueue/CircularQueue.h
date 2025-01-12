#pragma once

#include "Crosswind/Platforms/Platform.h"

#if defined(CORE_CIRCULAR_QUEUE)

  #include "CircularQueueEmptyException.h"
  #include "CircularQueueFullException.h"

  #include <stddef.h>

  template <typename T, size_t Capacity>
  class CircularQueue {
    public:
      CircularQueue() {
        _capacity = Capacity;
        _front = _rear = -1;
        _queue = new T[_capacity];
      }

      ~CircularQueue() {
        delete[] _queue;
        _queue = nullptr;
        _capacity = 0;
        _front = _rear = -1;
      }

      void enqueue(T& _value) {
        if (full()) {
          throw CircularQueueFullException();
        } else if (_front == -1) {
          _front = _rear = 0;
          _queue[_rear] = _value;
        } else if (_rear == _capacity - 1 && _front != 0) {
          _rear = 0;
          _queue[_rear] = _value;
        } else {
          _rear++;
          _queue[_rear] = _value;
        }
      }

      T* enqueue() {
        if (full()) {
          throw CircularQueueFullException();
        } else if (_front == -1) {
          _front = _rear = 0;
          return &_queue[_rear];
        } else if (_rear == _capacity - 1 && _front != 0) {
          _rear = 0;
          return &_queue[_rear];
        } else {
          _rear++;
          return &_queue[_rear];
        }
      }

      T& dequeue() {
        if (empty()) {
          throw CircularQueueEmptyException();
        }
    
        T* item = &_queue[_front];
        if (_front == _rear) {
          _front = -1;
          _rear = -1;
        } else if (_front == _capacity - 1) {
          _front = 0;
        } else {
          _front++;
        }
    
        return *item;
      }

      T& front() {
        if (empty()) {
          throw CircularQueueEmptyException();
        }

        T* item = &_queue[_front];
        return *item;
      }

      size_t size() {
        if (_front == -1) {
          return 0;
        } else if (_rear >= _front) {
          return ((_rear - _front) + 1);
        } else {
          return ((_capacity - _front) + (_rear + 1));
        }
      }

      size_t capacity() {
        return _capacity;
      }

      bool full() {
        return ((_front == 0 && _rear == _capacity - 1) || (_rear == (_front - 1)%(_capacity - 1)));
      }

      bool empty() {
        return (_front == -1);
      }

    private:
      T* _queue = nullptr;
      int _capacity = 0;
      int _front = -1;
      int _rear = -1;
  };

#endif // CORE_CIRCULAR_QUEUE
