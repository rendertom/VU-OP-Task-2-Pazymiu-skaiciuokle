#include "String.hpp"

bool String::hasSuffix(const std::string &str, const std::string &suffix) {
  unsigned long stringSize = str.size();
  unsigned long suffixSize = suffix.size();

  return stringSize >= suffixSize &&
         str.compare(stringSize - suffixSize, suffixSize, suffix) == 0;
}
