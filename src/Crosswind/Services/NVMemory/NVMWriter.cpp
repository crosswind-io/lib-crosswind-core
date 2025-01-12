#include "NVMWriter.h"

#if defined(SERVICE_NV_MEMORY)

const std::string NVMWriter::SERVICE_NAME = "NVMWriter";

NVMWriter::~NVMWriter() {
  if (nvm != nullptr) {
    delete nvm;
  }
  nvm = nullptr;
}

void NVMWriter::init() {
  
}

void NVMWriter::init(const char* nvmns, bool writable) {
  // attach the NV memory namespace
  nvm = new NVMNamespace(nvmns, writable);
}

void NVMWriter::init(const std::string& nvmns, bool writable) {
  init(nvmns.c_str(), writable);
}

void NVMWriter::init(NVMNamespace* nvmns) {
  // attach the NV memory namespace
  nvm = nvmns;
}

void NVMWriter::loop() {
}

void NVMWriter::enableWrite() {
  if (!nvm->isWritable()) {
    nvm->enableWrite();
  }
}

void NVMWriter::disableWrite() {
  if (nvm->isWritable()) {
    nvm->disableWrite();
  }
}

void NVMWriter::write(std::function<void(void)> writer) {
  enableWrite();
  writer();
  disableWrite();
}

#endif // SERVICE_NV_MEMORY
