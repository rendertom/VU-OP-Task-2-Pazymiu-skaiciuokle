#include "Utils.hpp"

int Utils::getNumberOfDigits(int number) {
  int numDigits = 0;

  while (number > 0) {
    numDigits++;
    number /= 10;
  }

  return numDigits;
}