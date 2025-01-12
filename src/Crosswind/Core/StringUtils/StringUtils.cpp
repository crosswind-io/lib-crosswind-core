#include "StringUtils.h"

namespace StringUtils {

  std::string joinToString(const std::vector<std::string>& vec, const char *const delim) {
    std::string result;

    for (size_t i = 0; i < vec.size(); ++i) {
      result += vec[i];
      if (i != vec.size() - 1) {
        result += delim;
      }
    }

    return result;
  }

}
