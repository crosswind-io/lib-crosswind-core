#include "NVMWriter.h"

#if defined(SERVICE_NV_MEMORY)

NVMWriter::~NVMWriter() {
  if (nvm != nullptr) {
    delete nvm;
  }
  nvm = nullptr;
}

void NVMWriter::init() {
  // TODO: throw exception
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

bool NVMWriter::write(std::function<bool(NVMNamespace*)> writer) {
  bool result = false;

  enableWrite();
  result = writer(nvm);
  disableWrite();

  return result;
}

#endif // SERVICE_NV_MEMORY
