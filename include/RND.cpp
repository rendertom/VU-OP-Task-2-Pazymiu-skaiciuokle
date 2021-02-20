#include "RND.hpp"

int RND::getIntegerInRange(int min, int max) {
  std::random_device rd;
  std::mt19937 mt(rd());
  std::uniform_int_distribution<int> uid(min, max);

  return uid(mt);
}
