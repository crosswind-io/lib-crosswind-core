#include "I2CPort.h"

#if defined(DEVICE_I2C_PORT)

#if defined (__USE_CUSTOM_TWOWIRE__)

I2CPort::I2CPort(uint8_t bus_num, uint16_t timeOutMillis) : TwoWire(bus_num), port(static_cast<i2c_port_t>(bus_num)), timeout(timeOutMillis) {
  i2c_set_timeout(port, pdMS_TO_TICKS(timeout));
}

#else 

I2CPort::I2CPort(uint8_t bus_num, uint16_t timeOutMillis) : TwoWire(bus_num) {
}

#endif

I2CPort::~I2CPort() {
  #if defined(__USE_CUSTOM_TWOWIRE__)
    i2c_driver_delete(port);
  #endif
}

#if defined (__USE_CUSTOM_TWOWIRE__)

void I2CPort::setTimeOut(uint16_t timeOutMillis) {
  timeout = timeOutMillis;
}

uint16_t I2CPort::getTimeOut() {
  return static_cast<uint16_t>(timeout & 0xFFFF);
}

bool I2CPort::begin(int sda, int scl, uint32_t frequency) {
  i2c_config_t config;
  memset(&config, 0x00, sizeof(i2c_config_t));

  config.mode = I2C_MODE_MASTER;
  config.sda_io_num = static_cast<gpio_num_t>(sda);
  config.sda_pullup_en = GPIO_PULLUP_DISABLE;
  config.scl_io_num = static_cast<gpio_num_t>(scl);
  config.scl_pullup_en = GPIO_PULLUP_DISABLE;
  config.master.clk_speed = frequency;
  config.clk_flags = I2C_SCLK_SRC_FLAG_FOR_NOMAL;

  esp_err_t err = i2c_param_config(port, &config);
  if (err == ESP_OK) {
    err = i2c_driver_install(port, config.mode, 0, 0, 0);
  }

  return (err == ESP_OK);
}

bool I2CPort::begin(uint8_t address, int sda, int scl) {
  i2c_config_t config;
  memset(&config, 0x00, sizeof(i2c_config_t));

  config.mode = I2C_MODE_SLAVE;
  config.sda_io_num = static_cast<gpio_num_t>(sda);
  config.sda_pullup_en = GPIO_PULLUP_DISABLE;
  config.scl_io_num = static_cast<gpio_num_t>(scl);
  config.scl_pullup_en = GPIO_PULLUP_DISABLE;
  config.slave.addr_10bit_en = 0;
  config.slave.slave_addr = address;

  esp_err_t err = i2c_param_config(port, &config);
  if (err == ESP_OK) {
    err = i2c_driver_install(port, config.mode, I2C_BUFFER_LENGTH, I2C_BUFFER_LENGTH, 0);
  }
  if (err == ESP_OK) {
    start();
  }

  return (err == ESP_OK);
}

bool I2CPort::end() {
  esp_err_t err = i2c_driver_delete(port);
  return (err == ESP_OK);
}

void I2CPort::beginTransmission(uint16_t address) {
  device_address = address;
  txLength = 0;
}

void I2CPort::beginTransmission(uint8_t address) {
  beginTransmission(static_cast<uint16_t>(address));
}

void I2CPort::beginTransmission(int address) {
  beginTransmission(static_cast<uint16_t>(address));
}

uint8_t I2CPort::endTransmission(bool sendStop) {
  i2c_cmd_handle_t cmd = i2c_cmd_link_create();
  i2c_master_start(cmd);

  // write the device address
  i2c_master_write_byte(cmd, (device_address << 1) | I2C_MASTER_WRITE, true);

  // write the buffer out to the device
  i2c_master_write(cmd, txBuffer, txLength, true);

  // write the stop bit
  if (sendStop) {
    i2c_master_stop(cmd);
  }

  // transmit the command
  esp_err_t err = i2c_master_cmd_begin(port, cmd, pdMS_TO_TICKS(timeout));
  i2c_cmd_link_delete(cmd);

  return (err == 0) ? I2C_ERROR_OK : I2C_ERROR_DEV;
}

uint8_t I2CPort::endTransmission() {
  return endTransmission(true);
}

size_t I2CPort::write(uint8_t data) {
  return write(&data, 1);
}

size_t I2CPort::write(const uint8_t* data, size_t quantity) {
  if (txLength + quantity > I2C_BUFFER_LENGTH) {
    quantity = I2C_BUFFER_LENGTH - txLength;
  }
  
  if (quantity > 0) {
    memcpy(&txBuffer[txLength], data, quantity);
    txLength += quantity;
  }

  return quantity;
}

int I2CPort::read() {
  int byte = static_cast<int>(rxBuffer[rxIndex]);
  rxIndex++;

  return (byte & 0xFF);
}

uint8_t I2CPort::requestFrom(uint16_t address, uint8_t size, bool sendStop) {
  rxLength = 0;
  rxIndex = 0;
  if (size > I2C_BUFFER_LENGTH) {
    return 0;
  }

  i2c_cmd_handle_t cmd = i2c_cmd_link_create();
  i2c_master_start(cmd);

  // write the device address
  i2c_master_write_byte(cmd, (device_address << 1) | I2C_MASTER_READ, true);

  // read the data from the device to the buffer
  i2c_master_read(cmd, rxBuffer, size, I2C_MASTER_LAST_NACK);

  if (sendStop) {
    i2c_master_stop(cmd);
  }

  esp_err_t err = i2c_master_cmd_begin(port, cmd, pdMS_TO_TICKS(timeout));
  i2c_cmd_link_delete(cmd);

  if (err == 0) {
    rxLength = size;
  }

  return rxLength;
}

uint8_t I2CPort::requestFrom(uint16_t address, uint8_t size, uint8_t sendStop) {
  return requestFrom(address, static_cast<size_t>(size), static_cast<bool>(sendStop));
}

uint8_t I2CPort::requestFrom(uint16_t address, uint8_t size) {
  return requestFrom(address, static_cast<size_t>(size), true);
}

uint8_t I2CPort::requestFrom(uint8_t address, uint8_t size, uint8_t sendStop) {
  return requestFrom(static_cast<uint16_t>(address), static_cast<size_t>(size), static_cast<bool>(sendStop));
}

uint8_t I2CPort::requestFrom(uint8_t address, uint8_t size) {
  return requestFrom(static_cast<uint16_t>(address), static_cast<size_t>(size), true);
}

uint8_t I2CPort::requestFrom(int address, int size, int sendStop) {
  return static_cast<uint8_t>(requestFrom(static_cast<uint16_t>(address), static_cast<size_t>(size), static_cast<bool>(sendStop)));
}

uint8_t I2CPort::requestFrom(int address, int size) {
  return requestFrom(static_cast<uint16_t>(address), static_cast<size_t>(size), true);
}

void I2CPort::onReceive(OnReceiveCallback callback) {
  on_receive = callback;
}

void I2CPort::onRequest(OnRequestCallback callback) {
  on_request = callback;
}

void I2CPort::run() {
  /*
  rxLength = 0;
  rxIndex = 0;

  while(true) {
    auto bytes_read = i2c_slave_read_buffer(port, &rxBuffer[rxIndex], 1, 1000 / portTICK_RATE_MS);
    if (bytes_read > 0) {
      rxLength += bytes_read;
      rxIndex += bytes_read;
    }
    // TODO
  }
  */
}

#endif

#else
  #pragma message("Feature [Device/I2CPort]: DISABLED")
#endif // DEVICE_I2C_PORT
