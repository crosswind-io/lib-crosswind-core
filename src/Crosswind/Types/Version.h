#pragma once

#include <cstdint>

#include <string>

class Version {
  public:
    Version() = default;
    Version(uint16_t major, uint16_t minor, uint16_t build);
    Version(const Version& version);
    Version(const char* version);
    Version(const std::string& version);
    ~Version() = default;

    bool operator==(const Version& other) const;
    bool operator==(const char* other) const;
    bool operator==(const std::string& other) const;

    bool operator!=(const Version& other) const;
    bool operator!=(const char* other) const;
    bool operator!=(const std::string& other) const;

    bool operator<(const Version& other) const;
    bool operator<(const char* other) const;
    bool operator<(const std::string& other) const;

    bool operator<=(const Version& other) const;
    bool operator<=(const char* other) const;
    bool operator<=(const std::string& other) const;

    bool operator>(const Version& other) const;
    bool operator>(const char* other) const;
    bool operator>(const std::string& other) const;

    bool operator>=(const Version& other) const;
    bool operator>=(const char* other) const;
    bool operator>=(const std::string& other) const;

    Version& operator=(const Version& other);
    Version& operator=(const char* other);
    Version& operator=(const std::string& other);

    std::string toString() const;

  private:
    static const size_t VERSION_STRING_LENGTH = (3 + 1 + 3 + 1 + 3);

  public:
    uint8_t major = 0;
    uint8_t minor = 0;
    uint16_t build = 0;
};
