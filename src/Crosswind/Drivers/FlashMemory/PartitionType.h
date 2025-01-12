#pragma once

#include <cstdint>

typedef uint32_t PartitionTypeType;
enum class PartitionType : PartitionTypeType {
  UNKNOWN = 0,
  FACTORY_APPLICATION,
  OTA_APPLICATION,
  OTA_SELECTION,
  PHY_DATA,
  NVS_DATA,
  COREDUMP,
  NVS_KEYS,
  HTTPD_DATA,
  FAT_FILESYSTEM,
  SPIFFS_FILESYSTEM,
  OTHER
};
