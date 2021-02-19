// Adopted from https://repl.it/@AleksandrIgumen/AtsKlase#RandInt.hpp

#include <random>

namespace RND {

  std::random_device rd;
  std::mt19937 mt(rd());

  int getIntegerInRange(int min, int max) {
    std::uniform_int_distribution<int> uid(min, max);

    return uid(mt);
  }
}