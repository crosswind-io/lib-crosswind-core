#pragma once

#include <cstdint>
#include <string>

class MACAddress {
  public:
    MACAddress();
    MACAddress(uint8_t first_octet, uint8_t second_octet, uint8_t third_octet, uint8_t fourth_octet, uint8_t fifth_octet, uint8_t sixth_octet);
    MACAddress(const uint8_t* address);
    MACAddress(const char* address);
    MACAddress(const std::string& address);
    virtual ~MACAddress() = default;

    bool operator==(const MACAddress& other) const;
    bool operator==(const uint8_t* other) const;
    bool operator==(const char* other) const;
    bool operator==(const std::string& other) const;

    bool operator!=(const MACAddress& other) const;
    bool operator!=(const uint8_t* other) const; 
    bool operator!=(const char* other) const;
    bool operator!=(const std::string& other) const;

    uint8_t operator[](int index) const;
    uint8_t& operator[](int index);

    MACAddress& operator=(const uint8_t* address);
    MACAddress& operator=(const char* address);
    MACAddress& operator=(const std::string& address);

    operator uint8_t*() { return mac_address; }
    operator const uint8_t*() const { return mac_address; }

    std::string toString() const;

  private:
    static const size_t MAC_ADDRESS_BYTE_LENGTH = 6;
    static const size_t MAC_ADDRESS_STRING_LENGTH = ((MAC_ADDRESS_BYTE_LENGTH * 2) + (MAC_ADDRESS_BYTE_LENGTH - 1));

  private:
    uint8_t mac_address[MAC_ADDRESS_BYTE_LENGTH];
};

extern const MACAddress INVALID_MAC_ADDRESS;
