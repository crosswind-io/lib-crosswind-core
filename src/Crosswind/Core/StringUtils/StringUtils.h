#pragma once

#include <string>
#include <vector>

namespace StringUtils {

  std::string joinToString(const std::vector<std::string>& vec, const char *const delim = ",");

}
