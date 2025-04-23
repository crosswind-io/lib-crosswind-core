#include "StringUtils.h"

#include <algorithm>

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

  bool containsOnly(const std::string& str, const std::vector<char>& allowed) {
    return std::all_of(str.begin(), str.end(), [&](char ch){
        return std::find(allowed.begin(), allowed.end(), ch) != allowed.end();
    });
  }

}
