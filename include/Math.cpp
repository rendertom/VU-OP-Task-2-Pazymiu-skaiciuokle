#include "Math.hpp"

double Math::findMean(vector<int> &array) {
  if (array.empty()) {
    return 0;
  }

  return std::accumulate(array.begin(), array.end(), 0.0) / array.size();
}

double Math::findMedian(vector<int> &array) {
  if (array.empty()) {
    return 0;
  }

  std::sort(array.begin(), array.end());

  const int arraySize = array.size();
  const bool isOddNumber = arraySize % 2 != 0;

  if (isOddNumber) {
    return (double)array[arraySize / 2];
  }

  return (double)(array[(arraySize - 1) / 2] + array[arraySize / 2]) / 2.0;
}
