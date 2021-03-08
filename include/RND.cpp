#include "RND.hpp"

std::random_device rd;
std::mt19937 mt(rd());

int RND::getIntegerInRange(int min, int max) {
  std::uniform_int_distribution<int> uid(min, max);

  return uid(mt);
}
