#pragma once

#if defined(ESP8266)

#include "Stream.h"

#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include "driver/uart.h"

#define UART_WORD_SHIFT             4
#define UART_PARITY_SHIFT           2
#define UART_STOP_SHIFT             0

#define UART_COMPONENT_MASK         0x03 // 0b00000011

#define UART_Encode(w,p,s)          ((w << UART_WORD_SHIFT) | (p << UART_PARITY_SHIFT) | (s << UART_STOP_SHIFT))
#define UART_Decode_Word(c)         ((c >> UART_WORD_SHIFT) & UART_COMPONENT_MASK)
#define UART_Decode_Parity(c)       ((c >> UART_PARITY_SHIFT) & UART_COMPONENT_MASK)
#define UART_Decode_Stop(c)         ((c >> UART_STOP_SHIFT) & UART_COMPONENT_MASK)

enum SerialConfig {
  SERIAL_5N1 = UART_Encode(UART_DATA_5_BITS, UART_PARITY_DISABLE, UART_STOP_BITS_1),
  SERIAL_6N1 = UART_Encode(UART_DATA_6_BITS, UART_PARITY_DISABLE, UART_STOP_BITS_1),
  SERIAL_7N1 = UART_Encode(UART_DATA_7_BITS, UART_PARITY_DISABLE, UART_STOP_BITS_1),
  SERIAL_8N1 = UART_Encode(UART_DATA_8_BITS, UART_PARITY_DISABLE, UART_STOP_BITS_1),
  SERIAL_5N2 = UART_Encode(UART_DATA_5_BITS, UART_PARITY_DISABLE, UART_STOP_BITS_2),
  SERIAL_6N2 = UART_Encode(UART_DATA_6_BITS, UART_PARITY_DISABLE, UART_STOP_BITS_2),
  SERIAL_7N2 = UART_Encode(UART_DATA_7_BITS, UART_PARITY_DISABLE, UART_STOP_BITS_2),
  SERIAL_8N2 = UART_Encode(UART_DATA_8_BITS, UART_PARITY_DISABLE, UART_STOP_BITS_2),
  SERIAL_5E1 = UART_Encode(UART_DATA_5_BITS, UART_PARITY_EVEN,    UART_STOP_BITS_1),
  SERIAL_6E1 = UART_Encode(UART_DATA_6_BITS, UART_PARITY_EVEN,    UART_STOP_BITS_1),
  SERIAL_7E1 = UART_Encode(UART_DATA_7_BITS, UART_PARITY_EVEN,    UART_STOP_BITS_1),
  SERIAL_8E1 = UART_Encode(UART_DATA_8_BITS, UART_PARITY_EVEN,    UART_STOP_BITS_1),
  SERIAL_5E2 = UART_Encode(UART_DATA_5_BITS, UART_PARITY_EVEN,    UART_STOP_BITS_2),
  SERIAL_6E2 = UART_Encode(UART_DATA_6_BITS, UART_PARITY_EVEN,    UART_STOP_BITS_2),
  SERIAL_7E2 = UART_Encode(UART_DATA_7_BITS, UART_PARITY_EVEN,    UART_STOP_BITS_2),
  SERIAL_8E2 = UART_Encode(UART_DATA_8_BITS, UART_PARITY_EVEN,    UART_STOP_BITS_2),
  SERIAL_5O1 = UART_Encode(UART_DATA_5_BITS, UART_PARITY_ODD,     UART_STOP_BITS_1),
  SERIAL_6O1 = UART_Encode(UART_DATA_6_BITS, UART_PARITY_ODD,     UART_STOP_BITS_1),
  SERIAL_7O1 = UART_Encode(UART_DATA_7_BITS, UART_PARITY_ODD,     UART_STOP_BITS_1),
  SERIAL_8O1 = UART_Encode(UART_DATA_8_BITS, UART_PARITY_ODD,     UART_STOP_BITS_1),
  SERIAL_5O2 = UART_Encode(UART_DATA_5_BITS, UART_PARITY_ODD,     UART_STOP_BITS_2),
  SERIAL_6O2 = UART_Encode(UART_DATA_6_BITS, UART_PARITY_ODD,     UART_STOP_BITS_2),
  SERIAL_7O2 = UART_Encode(UART_DATA_7_BITS, UART_PARITY_ODD,     UART_STOP_BITS_2),
  SERIAL_8O2 = UART_Encode(UART_DATA_8_BITS, UART_PARITY_ODD,     UART_STOP_BITS_2),
};

enum Uart {
  UART0 = 0,
  UART1,
  UART_MAX
};

class HardwareSerial : public Stream
{
  public:
    HardwareSerial(int uart_nr);
    virtual ~HardwareSerial();

    void begin(unsigned long baud);
    void begin(unsigned long baud, unsigned long config);
    void begin(unsigned long baud, SerialConfig config);

    virtual size_t write(uint8_t ch);
    virtual size_t write(const uint8_t* buffer, size_t size);

    size_t read(uint8_t* buffer, size_t size);
    inline size_t read(char* buffer, size_t size) {
      return read((uint8_t*)buffer, size);
    }

    virtual int available();
    virtual int read();
    virtual int peek();
    virtual void flush();

  private:
    static const int UART_BUFFER_SIZE = 1024;

  private:
    int uart_port = -1;
    xSemaphoreHandle uart_lock;

    bool uart_has_peek = false;
    uint8_t uart_peek_byte = 0x00;

  private:
    inline void UART_MUTEX_LOCK() {
      do {
      } while (xSemaphoreTake(uart_lock, portMAX_DELAY) != pdPASS);
    }
    inline void UART_MUTEX_UNLOCK() {
      xSemaphoreGive(uart_lock);
    }

    size_t uartWrite(uint8_t c);
    size_t uartWriteBuf(const uint8_t* data, size_t len);
    size_t uartAvailable();
    uint8_t uartPeek();
    uint8_t uartRead();
    void uartFlush();
    void uartFlushTxOnly(bool txOnly);
};

#if !defined(NO_GLOBAL_INSTANCES) && !defined(NO_GLOBAL_SERIAL)
  extern HardwareSerial Serial;
#endif

#endif // ESP8266
