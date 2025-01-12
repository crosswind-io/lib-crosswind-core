#include "UUID.h"

#include <assert.h>
#include <stdio.h>
#include <string.h>

#include <cstdio>

const UUID INVALID_UUID;

UUID::UUID() {
  memset(uuid, 0x00, UUID_BYTE_LENGTH);
}

UUID::UUID(const uint8_t* id) {
  *this = id;
}

UUID::UUID(const char* id) {
  *this = id;
}

UUID::UUID(const std::string& id) {
  *this = id;
}

bool UUID::operator==(const UUID& other) const {
  return (memcmp(uuid, other.uuid, UUID_BYTE_LENGTH) == 0);
}

bool UUID::operator==(const uint8_t* other) const {
  return (memcmp(uuid, other, UUID_BYTE_LENGTH) == 0);
}

bool UUID::operator==(const char* other) const {
  UUID other_uuid(other);
  return *this == other_uuid;
}

bool UUID::operator==(const std::string& other) const {
  return operator==(other.c_str());
}

bool UUID::operator!=(const UUID& other) const {
  return !operator==(other);
}

bool UUID::operator!=(const uint8_t* other) const {
  return !operator==(other);
}

bool UUID::operator!=(const char* other) const {
  return !operator==(other);
}

bool UUID::operator!=(const std::string& other) const {
  return !operator==(other);
}

uint8_t UUID::operator[](int index) const {
  assert(index < UUID_BYTE_LENGTH);
  return uuid[index];
}

uint8_t& UUID::operator[](int index) {
  assert(index < UUID_BYTE_LENGTH);
  return uuid[index];
}

UUID& UUID::operator=(const uint8_t* id) {
  if (id) {
    memcpy(uuid, id, UUID_BYTE_LENGTH);
  }
  return *this;
}

UUID& UUID::operator=(const char* id) {
  if (id) {
    std::sscanf(id, "%02hhx%02hhx%02hhx%02hhx-%02hhx%02hhx-%02hhx%02hhx-%02hhx%02hhx-%02hhx%02hhx%02hhx%02hhx%02hhx%02hhx",
                &uuid[0], &uuid[1], &uuid[2],  &uuid[3],  &uuid[4],  &uuid[5],  &uuid[6],  &uuid[7],
                &uuid[8], &uuid[9], &uuid[10], &uuid[11], &uuid[12], &uuid[13], &uuid[14], &uuid[15]);
  }
  return *this;
}

UUID& UUID::operator=(const std::string& id) {
  return operator=(id.c_str());
}

std::string UUID::toString() const {
  char uuid_string[UUID_STRING_LENGTH + 1];
  snprintf(uuid_string, UUID_STRING_LENGTH + 1, "%02x%02x%02x%02x-%02x%02x-%02x%02x-%02x%02x-%02x%02x%02x%02x%02x%02x", 
           uuid[0], uuid[1], uuid[2],  uuid[3],  uuid[4],  uuid[5],  uuid[6],  uuid[7],
           uuid[8], uuid[9], uuid[10], uuid[11], uuid[12], uuid[13], uuid[14], uuid[15]);
  return std::string(uuid_string);
}
