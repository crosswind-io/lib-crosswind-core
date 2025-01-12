#pragma once

#if defined(ESP8266)

#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <time.h>

#define DEC     10
#define HEX     16
#define OCT      8
#define BIN      2

class Print
{
  public:
    Print();
    virtual ~Print();

    int getWriteError();
    void clearWriteError();

    virtual size_t write(uint8_t) = 0;
    size_t write(const char* str);

    virtual size_t write(const uint8_t* buffer, size_t size);
    size_t write(const char* buffer, size_t size);

    size_t printf(const char* format, ...) __attribute__ ((format (printf, 2, 3)));

    // add availableForWrite to make compatible with Arduino Print.h
    // default to zero, meaning "a single write may block"
    // should be overriden by subclasses with buffering
    virtual int availableForWrite();

    size_t print(const char[]);
    size_t print(char);
    size_t print(unsigned char, int = DEC);
    size_t print(int, int = DEC);
    size_t print(unsigned int, int = DEC);
    size_t print(long, int = DEC);
    size_t print(unsigned long, int = DEC);
    size_t print(long long, int = DEC);
    size_t print(unsigned long long, int = DEC);
    size_t print(double, int = 2);
    size_t print(struct tm* timeinfo, const char* format = nullptr);

    size_t println(const char[]);
    size_t println(char);
    size_t println(unsigned char, int = DEC);
    size_t println(int, int = DEC);
    size_t println(unsigned int, int = DEC);
    size_t println(long, int = DEC);
    size_t println(unsigned long, int = DEC);
    size_t println(long long, int = DEC);
    size_t println(unsigned long long, int = DEC);
    size_t println(double, int = 2);
    size_t println(struct tm* timeinfo, const char* format = nullptr);
    size_t println();

  private:
    int write_error = 0;

    size_t printNumber(unsigned long, uint8_t);
    size_t printNumber(unsigned long long, uint8_t);
    size_t printFloat(double, uint8_t);

  protected:
    void setWriteError(int err = 1);
};

#endif // ESP8266
