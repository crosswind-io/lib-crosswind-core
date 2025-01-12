#include "Version.h"

#include <stdio.h>
#include <stdint.h>

#include <cstdio>

#define VERSION_TO_INTEGER(major, minor, build) (static_cast<uint32_t>(major) * 1000000) + (static_cast<uint32_t>(minor) * 1000) + (static_cast<uint32_t>(build) * 1)

Version::Version(uint16_t major, uint16_t minor, uint16_t build)
  : major(major), minor(minor), build(build)
{
}

Version::Version(const Version& version) {
  *this = version;
}

Version::Version(const std::string& version) {
  *this = version;
}

Version::Version(const char* version) {
  *this = version;
}

bool Version::operator==(const Version& other) const {
  return ((major == other.major) && (minor == other.minor) && (build == other.build));
}

bool Version::operator==(const char* other) const {
  Version other_version(other);
  return *this == other_version;
}

bool Version::operator==(const std::string& other) const {
  return operator==(other.c_str());
}

bool Version::operator!=(const Version& other) const {
  return !operator==(other);
}

bool Version::operator!=(const char* other) const {
  return !operator==(other);
}

bool Version::operator!=(const std::string& other) const {
  return !operator==(other);
}

bool Version::operator<(const Version& other) const {
  auto v_this = VERSION_TO_INTEGER(major, minor, build);
  auto v_other = VERSION_TO_INTEGER(other.major, other.minor, other.build);
  return (v_this < v_other);
}

bool Version::operator<(const char* other) const {
  Version other_version(other);
  return *this < other_version;
}

bool Version::operator<(const std::string& other) const {
  return operator<(other.c_str());
}

bool Version::operator<=(const Version& other) const {
  auto v_this = VERSION_TO_INTEGER(major, minor, build);
  auto v_other = VERSION_TO_INTEGER(other.major, other.minor, other.build);
  return (v_this <= v_other);
}

bool Version::operator<=(const char* other) const {
  Version other_version(other);
  return *this <= other_version;
}

bool Version::operator<=(const std::string& other) const {
  return operator<=(other.c_str());
}

bool Version::operator>(const Version& other) const {
  auto v_this = VERSION_TO_INTEGER(major, minor, build);
  auto v_other = VERSION_TO_INTEGER(other.major, other.minor, other.build);
  return (v_this > v_other);
}

bool Version::operator>(const char* other) const {
  Version other_version(other);
  return *this > other_version;
}

bool Version::operator>(const std::string& other) const {
  return operator>(other.c_str());
}

bool Version::operator>=(const Version& other) const {
  auto v_this = VERSION_TO_INTEGER(major, minor, build);
  auto v_other = VERSION_TO_INTEGER(other.major, other.minor, other.build);
  return (v_this >= v_other);
}

bool Version::operator>=(const char* other) const {
  Version other_version(other);
  return *this >= other_version;
}

bool Version::operator>=(const std::string& other) const {
  return operator>=(other.c_str());
}

Version& Version::operator=(const Version& other) {
  major = other.major;
  minor = other.minor;
  build = other.build;

  return *this;
}

Version& Version::operator=(const char* other) {
  if (other) {
    //std::sscanf(other, "%hhu.%hhu.%hu", &major, &minor, &build);
    uint16_t tmp_major, tmp_minor;
    std::sscanf(other, "%hu.%hu.%hu", &tmp_major, &tmp_minor, &build);
    major = (uint8_t)tmp_major;
    minor = (uint8_t)tmp_minor;
  }
  
  return *this;
}

Version& Version::operator=(const std::string& other) {
  return operator=(other.c_str());
}

std::string Version::toString() const {
  char version_string[VERSION_STRING_LENGTH + 1];
  //snprintf(version_string, VERSION_STRING_LENGTH + 1, "%hhu.%hhu.%hu", major, minor, build);
  uint16_t tmp_major = major;
  uint16_t tmp_minor = minor;
  snprintf(version_string, VERSION_STRING_LENGTH + 1, "%hu.%hu.%hu", tmp_major, tmp_minor, build);
  return std::string(version_string);
}
