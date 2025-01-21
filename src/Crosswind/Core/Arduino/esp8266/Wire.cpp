#if defined(ESP8266)

#include "Wire.h"

TwoWire::TwoWire(uint8_t bus_num) : i2cBus(bus_num) {
}

TwoWire::~TwoWire() {
}

bool TwoWire::setPins(int sda, int scl) {
  if (i2cInitialized) {
    return false;
  }

  sdaPin = sda;
  sclPin = scl;
  return true;
}
    
bool TwoWire::begin(int sda, int scl, uint32_t frequency, bool enableAckCheck) {
  if (sda < 0) {
    if (i2cBus == I2C0) {
      if (sdaPin == -1) {
          sdaPin = I2C0_DEFAULT_SDA;
      }
    } else {
      if (sdaPin == -1) {
        return false;
      }
    }
  } else {
    sdaPin = sda;
  }

  if (scl < 0) {
    if (i2cBus == I2C0) {
      if (sclPin == -1) {
          sclPin = I2C0_DEFAULT_SCL;
      }
    } else {
      if (sclPin == -1) {
        return false;
      }
    }
  } else {
    sclPin = scl;
  }

  i2c_config_t i2c_config = {
    .mode = I2C_MODE_MASTER,
    .sda_io_num = static_cast<gpio_num_t>(sdaPin),
    .sda_pullup_en = GPIO_PULLUP_ENABLE,
    .scl_io_num = static_cast<gpio_num_t>(sclPin),
    .scl_pullup_en = GPIO_PULLUP_ENABLE,
    .clk_stretch_tick = 300 // TODO: 300 ticks, Clock stretch is about 210us, you can make changes according to the actual situation ???
  };

  ackCheck = enableAckCheck;

  // TODO: frequency?

  ESP_ERROR_CHECK(i2c_driver_install(static_cast<i2c_port_t>(i2cBus), i2c_config.mode));
  ESP_ERROR_CHECK(i2c_param_config(static_cast<i2c_port_t>(i2cBus), &i2c_config));

  return true;
}

size_t TwoWire::write(uint8_t ch) {
  if (txCmd != nullptr) {
    ESP_ERROR_CHECK(i2c_master_write_byte(txCmd, ch, ackCheck));
    return 1;
  } else {
    return 0;
  }
}

size_t TwoWire::write(const uint8_t* buffer, size_t size) {
  if (txCmd != nullptr) {
    ESP_ERROR_CHECK(i2c_master_write(txCmd, const_cast<uint8_t*>(buffer), size, ackCheck));
    return size;
  } else {
    return 0;
  }
}

void TwoWire::beginTransmission(uint16_t address) {
  beginTransmission(static_cast<uint8_t>(address));
}

void TwoWire::beginTransmission(uint8_t address) {
  if (txCmd == nullptr) {
    txCmd = i2c_cmd_link_create();
    ESP_ERROR_CHECK(i2c_master_start(txCmd));
    ESP_ERROR_CHECK(i2c_master_write_byte(txCmd, (address << 1) | I2C_MASTER_WRITE, ackCheck));
  }
}

void TwoWire::beginTransmission(int address) {
  beginTransmission(static_cast<uint8_t>(address));
}

int32_t TwoWire::endTransmission(bool sendStop) {
  if (txCmd != nullptr) {
    if (sendStop) {
      ESP_ERROR_CHECK(i2c_master_stop(txCmd));
    }

    auto result = i2c_master_cmd_begin(static_cast<i2c_port_t>(i2cBus), txCmd, DEFAULT_TIMEOUT_MS / portTICK_RATE_MS);
    i2c_cmd_link_delete(txCmd);
    txCmd = nullptr;

    ESP_ERROR_CHECK(result);
    return result;
  } else {
    return ESP_ERR_INVALID_STATE;
  }
}

uint8_t TwoWire::requestFrom(uint16_t address, uint8_t size, bool sendStop) {
  return requestFrom(static_cast<uint8_t>(address), size, sendStop);
}

uint8_t TwoWire::requestFrom(uint8_t address, uint8_t size, bool sendStop) {
  if (rxCmd == nullptr) {
    rxCmd = i2c_cmd_link_create();
    ESP_ERROR_CHECK(i2c_master_start(rxCmd));
    ESP_ERROR_CHECK(i2c_master_write_byte(rxCmd, (address << 1) | I2C_MASTER_READ, ackCheck));

    uint8_t data[size];
    ESP_ERROR_CHECK(i2c_master_read(rxCmd, data, size, I2C_MASTER_LAST_NACK));
    if (sendStop) {
      ESP_ERROR_CHECK(i2c_master_stop(rxCmd));
    }

    auto result = i2c_master_cmd_begin(static_cast<i2c_port_t>(i2cBus), rxCmd, DEFAULT_TIMEOUT_MS / portTICK_RATE_MS);
    i2c_cmd_link_delete(rxCmd);
    rxCmd = nullptr;

    ESP_ERROR_CHECK(result);
    if (result == ESP_OK) {
      for (auto x = 0; x < size; x++) {
        rxBuffer.push(data[x]);
      }
      return size;
    } else {
      return 0;
    }
  } else {
    return 0;
  }
}

uint8_t TwoWire::requestFrom(int address, int size, bool sendStop) {
  return requestFrom(static_cast<uint8_t>(address), static_cast<uint8_t>(size), sendStop);
}

int TwoWire::available() {
  return rxBuffer.size();
}

int TwoWire::read() {
  int value = -1;
  if (rxBuffer.size() > 0) {
    value = rxBuffer.front();
    rxBuffer.pop();
  }
  return value;
}

int TwoWire::peek() {
  int value = -1;
  if (rxBuffer.size() > 0) {
    value = rxBuffer.front();
  }
  return value;
}

void TwoWire::flush() {
  while (rxBuffer.size() > 0) {
    rxBuffer.pop();
  }
}

#if !defined(NO_GLOBAL_INSTANCES) && !defined(NO_GLOBAL_TWO_WIRE)
  TwoWire Wire(I2C0);
#endif

#endif // ESP8266
