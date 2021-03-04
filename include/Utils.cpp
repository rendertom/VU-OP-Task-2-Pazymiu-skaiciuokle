#include "Utils.hpp"

int Utils::getNumberOfDigits(int &number) {
  int numDigits = 0;
  int value = number;

  while (value > 0) {
    numDigits++;
    value /= 10;
  }

  return numDigits;
}