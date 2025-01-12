#include "NVMNamespace.h"

#if defined(SERVICE_NV_MEMORY)

#include "NVMEraseException.h"
#include "NVMReadException.h"
#include "NVMWriteException.h"

NVMNamespace::NVMNamespace(const char* name, bool writable)
  : is_writable(true), nvm_name(name)
{
  assert(nvs_open(nvm_name.c_str(), NVS_READWRITE, &nvm_handle) == ESP_OK);
  enableWrite(writable);
}

NVMNamespace::~NVMNamespace() {
  nvs_close(nvm_handle);
  nvm_handle = 0;
}

void NVMNamespace::erase() {
  auto result = nvs_erase_all(nvm_handle);
  if (result != ESP_OK) {
    handleEraseFailure(result);
  }
}

bool NVMNamespace::isWritable() {
  return is_writable;
}

void NVMNamespace::enableWrite(bool writable) {
  if (writable != is_writable) {
    if (nvm_handle != 0) {
      nvs_close(nvm_handle);
      nvm_handle = 0;
    }
    
    is_writable = writable;
    assert(nvs_open(nvm_name.c_str(), (is_writable ? NVS_READWRITE : NVS_READONLY), &nvm_handle) == ESP_OK);
  }
}

void NVMNamespace::disableWrite() {
  enableWrite(false);
}

int8_t NVMNamespace::get(const char* key, int8_t& value) {
  auto result = nvs_get_i8(nvm_handle, key, &value);
  if (result != ESP_OK) {
    handleGetFailure(result);
  }
  return value;
}

void NVMNamespace::set(const char* key, int8_t value) {
  auto result = nvs_set_i8(nvm_handle, key, value);
  if (result != ESP_OK) {
    handleSetFailure(result);
  }
}

uint8_t NVMNamespace::get(const char* key, uint8_t& value) {
  auto result = nvs_get_u8(nvm_handle, key, &value);
  if (result != ESP_OK) {
    handleGetFailure(result);
  }
  return value;
}

void NVMNamespace::set(const char* key, uint8_t value) {
  auto result = nvs_set_u8(nvm_handle, key, value);
  if (result != ESP_OK) {
    handleSetFailure(result);
  }
}

int16_t NVMNamespace::get(const char* key, int16_t& value) {
  auto result = nvs_get_i16(nvm_handle, key, &value);
  if (result != ESP_OK) {
    handleGetFailure(result);
  }
  return value;
}

void NVMNamespace::set(const char* key, int16_t value) {
  auto result = nvs_set_i16(nvm_handle, key, value);
  if (result != ESP_OK) {
    handleSetFailure(result);
  }
}

uint16_t NVMNamespace::get(const char* key, uint16_t& value) {
  auto result = nvs_get_u16(nvm_handle, key, &value);
  if (result != ESP_OK) {
    handleGetFailure(result);
  }
  return value;
}

void NVMNamespace::set(const char* key, uint16_t value) {
  auto result = nvs_set_u16(nvm_handle, key, value);
  if (result != ESP_OK) {
    handleSetFailure(result);
  }
}

int32_t NVMNamespace::get(const char* key, int32_t& value) {
  auto result = nvs_get_i32(nvm_handle, key, &value);
  if (result != ESP_OK) {
    handleGetFailure(result);
  }
  return value;
}

void NVMNamespace::set(const char* key, int32_t value) {
  auto result = nvs_set_i32(nvm_handle, key, value);
  if (result != ESP_OK) {
    handleSetFailure(result);
  }
}

uint32_t NVMNamespace::get(const char* key, uint32_t& value) {
  auto result = nvs_get_u32(nvm_handle, key, &value);
  if (result != ESP_OK) {
    handleGetFailure(result);
  }
  return value;
}

void NVMNamespace::set(const char* key, uint32_t value) {
  auto result = nvs_set_u32(nvm_handle, key, value);
  if (result != ESP_OK) {
    handleSetFailure(result);
  }
}

int64_t NVMNamespace::get(const char* key, int64_t& value) {
  auto result = nvs_get_i64(nvm_handle, key, &value);
  if (result != ESP_OK) {
    handleGetFailure(result);
  }
  return value;
}

void NVMNamespace::set(const char* key, int64_t value) {
  auto result = nvs_set_i64(nvm_handle, key, value);
  if (result != ESP_OK) {
    handleSetFailure(result);
  }
}

uint64_t NVMNamespace::get(const char* key, uint64_t& value) {
  auto result = nvs_get_u64(nvm_handle, key, &value);
  if (result != ESP_OK) {
    handleGetFailure(result);
  }
  return value;
}

void NVMNamespace::set(const char* key, uint64_t value) {
  auto result = nvs_set_u64(nvm_handle, key, value);
  if (result != ESP_OK) {
    handleSetFailure(result);
  }
}

std::string NVMNamespace::get(const char* key) {
  size_t length = 0;
  auto result = nvs_get_str(nvm_handle, key, nullptr, &length);
  if (result == ESP_OK) {
    std::string value(length, ' ');
    result = nvs_get_str(nvm_handle, key, (char*)value.c_str(), &length);
    if (result != ESP_OK) {
      handleGetFailure(result);
    }
    return value;
  } else {
    handleGetFailure(result);
  }
}

void NVMNamespace::set(const char* key, const char* value) {
  auto result = nvs_set_str(nvm_handle, key, value);
  if (result != ESP_OK) {
    handleSetFailure(result);
  }
}

size_t NVMNamespace::getBlobSize(const char* key) {
  size_t blob_length = 0;
  auto result = nvs_get_blob(nvm_handle, key, nullptr, &blob_length);
  if (result != ESP_OK) {
    blob_length = 0;
  }
  return blob_length;
}

void* NVMNamespace::get(const char* key, void* value, size_t length) {
  size_t blob_length = getBlobSize(key);
  if (length <= blob_length) {
    blob_length = length;
    auto result = nvs_get_blob(nvm_handle, key, value, &blob_length);
    if (result != ESP_OK) {
      handleGetFailure(result);
    }
    return value;
  } else {
    throw NVMReadException("NVM value larger than destination");

    return value;
  }
}

void NVMNamespace::set(const char* key, const void* value, size_t length) {
  auto result = nvs_set_blob(nvm_handle, key, value, length);
  if (result != ESP_OK) {
    handleSetFailure(result);
  }
}

void NVMNamespace::handleEraseFailure(esp_err_t err) {
  switch(err) {
    case ESP_ERR_NVS_INVALID_HANDLE: throw NVMEraseException("NVM namespace handle not open"); break;
    case ESP_ERR_NVS_READ_ONLY: throw NVMEraseException("NVM namespace is read-only"); break;
    default: throw NVMWriteException("Unknown NVM erase error"); break;
  }
}

void NVMNamespace::handleGetFailure(esp_err_t err) {
  switch(err) {
    case ESP_ERR_NVS_NOT_FOUND: throw NVMReadException("NVM key doesn't exist in namespace"); break;
    case ESP_ERR_NVS_INVALID_HANDLE: throw NVMReadException("NVM namespace handle not open"); break;
    case ESP_ERR_NVS_INVALID_NAME: throw NVMReadException("NVM key doesn't satisfy constraints"); break;
    case ESP_ERR_NVS_INVALID_LENGTH: throw NVMReadException("NVM value larger than destination"); break;
    default: throw NVMReadException("Unknown NVM read error"); break;
  }
}

void NVMNamespace::handleSetFailure(esp_err_t err) {
  switch(err) {
    case ESP_ERR_NVS_NOT_FOUND: throw NVMWriteException("NVM key doesn't exist in namespace"); break;
    case ESP_ERR_NVS_READ_ONLY: throw NVMWriteException("NVM namespace is read-only"); break;
    case ESP_ERR_NVS_NOT_ENOUGH_SPACE: throw NVMWriteException("Not enough space"); break;
    case ESP_ERR_NVS_REMOVE_FAILED: throw NVMWriteException("NVM flash write operation failed"); break;
    case ESP_ERR_NVS_VALUE_TOO_LONG: throw NVMWriteException("The value is too large for NVM"); break;
    case ESP_ERR_NVS_INVALID_HANDLE: throw NVMWriteException("NVM namespace handle not open"); break;
    case ESP_ERR_NVS_INVALID_NAME: throw NVMWriteException("NVM key doesn't satisfy constraints"); break;
    default: throw NVMWriteException("Unknown NVM write error"); break;
  }
}

#endif // SERVICE_NV_MEMORY
