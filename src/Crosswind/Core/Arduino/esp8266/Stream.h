#pragma once

#if defined(ESP8266)

#include "Print.h"

class Stream : public Print {
  public:
    Stream();
    virtual ~Stream();

    virtual int available() = 0;
    virtual int read() = 0;
    virtual int peek() = 0;
    virtual void flush() = 0;

    // sets maximum milliseconds to wait for stream data, default is 1 second
    void setTimeout(unsigned long timeout);
    unsigned long getTimeout();

    // reads data from the stream until the target string is found
    bool find(const char* target);
    bool find(uint8_t* target);

    // returns true if target string is found, false if timed out (see setTimeout)
    bool find(const char* target, size_t length);
    bool find(const uint8_t* target, size_t length);
    
    // returns true if target string is found, false if timed out
    bool find(char target);

    // same as find but search ends if the terminator string is found
    bool findUntil(const char* target, const char* terminator);
    bool findUntil(const uint8_t* target, const char* terminator);

    // same as above but search ends if the terminator string is found
    bool findUntil(const char* target, size_t targetLen, const char* terminator, size_t termLen);
    bool findUntil(const uint8_t* target, size_t targetLen, const char* terminator, size_t termLen);

    // read chars from stream into buffer
    virtual size_t readBytes(char* buffer, size_t length);
    virtual size_t readBytes(uint8_t* buffer, size_t length);

    // same as readBytes with terminator character
    size_t readBytesUntil(char terminator, char* buffer, size_t length);
    size_t readBytesUntil(char terminator, uint8_t* buffer, size_t length);

    // returns the first valid (long) integer value from the current position.
    long parseInt();
    // float version of parseInt
    float parseFloat();

  protected:
    int timedRead();     // private method to read stream with timeout
    int timedPeek();     // private method to peek stream with timeout
    int peekNextDigit(); // returns the next numeric digit in the stream or -1 if timeout

    long parseInt(char skipChar);
    float parseFloat(char skipChar);

    struct MultiTarget {
      const char* str;  // string you're searching for
      size_t len;       // length of string you're searching for
      size_t index;     // index used by the search routine.
    };

    // This allows you to search for an arbitrary number of strings.
    // Returns index of the target that is found first or -1 if timeout occurs.
    int findMulti(struct MultiTarget* targets, int tCount);

  protected:
    unsigned long _timeout = 1000;   // number of milliseconds to wait for the next char before aborting timed read
    unsigned long _startMillis = 0;  // used for timeout measurement
};

#endif // ESP8266
