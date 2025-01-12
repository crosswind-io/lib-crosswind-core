#if defined(ESP8266)

#include "HardwareSerial.h"

#include "esp_err.h"

HardwareSerial::HardwareSerial(int uart_nr) : uart_port(uart_nr) {
  uart_lock = xSemaphoreCreateMutex();
}

HardwareSerial::~HardwareSerial() {
}

void HardwareSerial::begin(unsigned long baud) {
  begin(baud, SERIAL_8N1);
}

void HardwareSerial::begin(unsigned long baud, unsigned long config) {
  begin(baud, static_cast<SerialConfig>((int)config));
}

void HardwareSerial::begin(unsigned long baud, SerialConfig config) {
  uart_config_t uart_config = {
    .baud_rate           = static_cast<int>(baud),
    .data_bits           = static_cast<uart_word_length_t>(UART_Decode_Word(config)),
    .parity              = static_cast<uart_parity_t>(UART_Decode_Parity(config)),
    .stop_bits           = static_cast<uart_stop_bits_t>(UART_Decode_Stop(config)),
    .flow_ctrl           = UART_HW_FLOWCTRL_DISABLE,
    .rx_flow_ctrl_thresh = 0x00
  };

  ESP_ERROR_CHECK(uart_param_config(static_cast<uart_port_t>(uart_port), &uart_config));
  ESP_ERROR_CHECK(uart_driver_install(static_cast<uart_port_t>(uart_port), UART_BUFFER_SIZE, UART_BUFFER_SIZE, 0, nullptr, 0));
}

size_t HardwareSerial::write(uint8_t c) {
  return uartWrite(c);
}

size_t HardwareSerial::write(const uint8_t* buffer, size_t size) {
  return uartWriteBuf(buffer, size);
}

size_t HardwareSerial::read(uint8_t* buffer, size_t size) {
  size_t avail = available();
  if (size < avail) {
      avail = size;
  }

  size_t count = 0;
  while (count < avail) {
      *buffer++ = uartRead();
      count++;
  }
  return count;
}

int HardwareSerial::available() {
  return uartAvailable();
}

int HardwareSerial::read() {
  if (available()) {
    return uartRead();
  }
  return -1;
}

int HardwareSerial::peek() {
  if (available()) {
    return uartPeek();
  }
  return -1;
}

void HardwareSerial::flush() {
  uartFlush();
}

size_t HardwareSerial::uartWrite(uint8_t c) {
  size_t bytes_written = 0;

  UART_MUTEX_LOCK();
  bytes_written = uart_write_bytes(static_cast<uart_port_t>(uart_port), (const char *)&c, 1);
  UART_MUTEX_UNLOCK();

  return bytes_written;
}

size_t HardwareSerial::uartWriteBuf(const uint8_t* data, size_t len) {
  size_t bytes_written = 0;

  UART_MUTEX_LOCK();
  bytes_written = uart_write_bytes(static_cast<uart_port_t>(uart_port), (const char *)data, len);
  UART_MUTEX_UNLOCK();

  return bytes_written;
}

size_t HardwareSerial::uartAvailable() {
  size_t available = 0;

  UART_MUTEX_LOCK();
  ESP_ERROR_CHECK(uart_get_buffered_data_len(static_cast<uart_port_t>(uart_port), &available));
  if (uart_has_peek) {
    available++;
  }
  UART_MUTEX_UNLOCK();

  return available;
}

uint8_t HardwareSerial::uartPeek() {
  uint8_t c = 0;

  UART_MUTEX_LOCK();
  if (uart_has_peek) {
    c = uart_peek_byte;
  } else {
    int len = uart_read_bytes(static_cast<uart_port_t>(uart_port), &c, 1, 20 / portTICK_RATE_MS);
    if (len == 0) {
      c  = 0;
    } else {
      uart_has_peek = true;
      uart_peek_byte = c;
    }
  }
  UART_MUTEX_UNLOCK();

  return c;
}

uint8_t HardwareSerial::uartRead() {
  uint8_t c = 0;

  UART_MUTEX_LOCK();
  if (uart_has_peek) {
    uart_has_peek = false;
    c = uart_has_peek;
  } else {
    int len = uart_read_bytes(static_cast<uart_port_t>(uart_port), &c, 1, 20 / portTICK_RATE_MS);
    if (len == 0) {
      c  = 0;
    }
  }
  UART_MUTEX_UNLOCK();

  return c;
}

void HardwareSerial::uartFlush() {
  uartFlushTxOnly(true);
}

void HardwareSerial::uartFlushTxOnly(bool txOnly) {
  UART_MUTEX_LOCK();
  ESP_ERROR_CHECK(uart_wait_tx_done(static_cast<uart_port_t>(uart_port), portMAX_DELAY));
  if (!txOnly) {
    ESP_ERROR_CHECK(uart_flush_input(static_cast<uart_port_t>(uart_port)));
  }
  UART_MUTEX_UNLOCK();
}

#if !defined(NO_GLOBAL_INSTANCES) && !defined(NO_GLOBAL_SERIAL)
  HardwareSerial Serial(UART0);
#endif

#endif // ESP8266
