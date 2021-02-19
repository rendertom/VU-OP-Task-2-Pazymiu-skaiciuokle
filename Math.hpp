#include <algorithm>  // std::sort
#include <vector>

using std::sort;
using std::vector;

namespace Math {

double findMean(vector<int> &array) {
  if (array.empty()) {
    return 0;
  }

  const int arraySize = array.size();
  int sum = 0;
  for (int i = 0; i < arraySize; i++) {
    sum += array[i];
  }

  return (double)sum / arraySize;
}

double findMedian(vector<int> &array) {
  if (array.empty()) {
    return 0;
  }

  sort(array.begin(), array.end());

  const int arraySize = array.size();
  const bool isOddNumber = arraySize % 2 != 0;

  if (isOddNumber) {
    return (double)array[arraySize / 2];
  }

  return (double)(array[(arraySize - 1) / 2] + array[arraySize / 2]) / 2.0;
}

}  // namespace Math