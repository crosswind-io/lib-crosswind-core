#include "NVMemory.h"

#if defined(SERVICE_NV_MEMORY)

#include "nvs_flash.h"
#include "nvs.h"

const std::string NVMemory::SERVICE_NAME = "NVMemory";

NVMemory::~NVMemory() {
  nvs_flash_deinit();
}

void NVMemory::init() {
  assert(nvs_flash_init() == ESP_OK);
}

void NVMemory::loop() {
}

void NVMemory::erase() {
  nvs_flash_erase();
}

#else
  #pragma message("Feature [Service/NVMemory]: DISABLED")
#endif // SERVICE_NV_MEMORY
