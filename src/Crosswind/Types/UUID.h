#pragma once

#include <cstdint>
#include <string>

class UUID {
  public:
    UUID();
    UUID(const uint8_t* id);
    UUID(const char* id);
    UUID(const std::string& id);
    virtual ~UUID() = default;

    bool operator==(const UUID& other) const;
    bool operator==(const uint8_t* other) const;
    bool operator==(const char* other) const;
    bool operator==(const std::string& other) const;

    bool operator!=(const UUID& other) const;
    bool operator!=(const uint8_t* other) const;
    bool operator!=(const char* other) const;
    bool operator!=(const std::string& other) const;

    uint8_t operator[](int index) const;
    uint8_t& operator[](int index);

    UUID& operator=(const uint8_t* id);
    UUID& operator=(const char* id);
    UUID& operator=(const std::string& id);

    operator uint8_t*() { return uuid; }
    operator const uint8_t*() const { return uuid; }

    std::string toString() const;

  public:
    static const size_t UUID_BYTE_LENGTH = 16;

  private:
    static const size_t UUID_STRING_LENGTH = ((UUID_BYTE_LENGTH * 2) + 4);

  private:
    uint8_t uuid[UUID_BYTE_LENGTH];
};

extern const UUID INVALID_UUID;
