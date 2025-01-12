#include "MACAddress.h"

#include <assert.h>
#include <stdio.h>
#include <string.h>

#include <cstdio>

const MACAddress INVALID_MAC_ADDRESS;

MACAddress::MACAddress() {
  memset(mac_address, 0x00, MAC_ADDRESS_BYTE_LENGTH);
}

MACAddress::MACAddress(uint8_t first_octet, uint8_t second_octet, uint8_t third_octet, uint8_t fourth_octet, uint8_t fifth_octet, uint8_t sixth_octet) {
  mac_address[0] = first_octet;
  mac_address[1] = second_octet;
  mac_address[2] = third_octet;
  mac_address[3] = fourth_octet;
  mac_address[4] = fifth_octet;
  mac_address[5] = sixth_octet;
}

MACAddress::MACAddress(const uint8_t* address) : MACAddress() {
  *this = address;
}

MACAddress::MACAddress(const char* address) : MACAddress() {
  *this = address;
}

MACAddress::MACAddress(const std::string& address) : MACAddress() {
  *this = address;
}

bool MACAddress::operator==(const MACAddress& other) const {
  return (memcmp(mac_address, other.mac_address, MAC_ADDRESS_BYTE_LENGTH) == 0);
}

bool MACAddress::operator==(const uint8_t* other) const {
  return (memcmp(mac_address, other, MAC_ADDRESS_BYTE_LENGTH) == 0);
}

bool MACAddress::operator==(const char* other) const {
  MACAddress other_addr(other);
  return *this == other_addr;
}

bool MACAddress::operator==(const std::string& other) const {
  return operator==(other.c_str());
}

bool MACAddress::operator!=(const MACAddress& other) const {
  return !operator==(other);
}

bool MACAddress::operator!=(const uint8_t* other) const {
  return !operator==(other);
}

bool MACAddress::operator!=(const char* other) const {
  return !operator==(other);
}

bool MACAddress::operator!=(const std::string& other) const {
  return !operator==(other);
}

uint8_t MACAddress::operator[](int index) const {
  assert(index < MAC_ADDRESS_BYTE_LENGTH);
  return mac_address[index];
}

uint8_t& MACAddress::operator[](int index) {
  assert(index < MAC_ADDRESS_BYTE_LENGTH);
  return mac_address[index];
}

MACAddress& MACAddress::operator=(const uint8_t* address) {
  if (address) {
    memcpy(mac_address, address, MAC_ADDRESS_BYTE_LENGTH);
  }
  return *this;
}

MACAddress& MACAddress::operator=(const char* address) {
  if (address) {
    std::sscanf(address, "%02hhx:%02hhx:%02hhx:%02hhx:%02hhx:%02hhx",
                &mac_address[0], &mac_address[1], &mac_address[2], &mac_address[3], &mac_address[4], &mac_address[5]);
  }
  return *this;
}

MACAddress& MACAddress::operator=(const std::string& address) {
  return operator=(address.c_str());
}

std::string MACAddress::toString() const {
  char mac_address_string[MAC_ADDRESS_STRING_LENGTH + 1];
  snprintf(mac_address_string, MAC_ADDRESS_STRING_LENGTH + 1, "%02x:%02x:%02x:%02x:%02x:%02x", 
           mac_address[0], mac_address[1], mac_address[2], mac_address[3], mac_address[4], mac_address[5]);
  return std::string(mac_address_string);
}
