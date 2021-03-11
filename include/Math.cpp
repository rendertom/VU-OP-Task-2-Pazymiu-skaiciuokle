#include "Math.hpp"

template <class A>
double Math::findMean(A &array) {
  if (array.empty()) {
    return 0;
  }

  return std::accumulate(array.begin(), array.end(), 0.0) / array.size();
}

template <class A>
double Math::findMedian(A &array) {
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

double Math::findMedian(list<int> &array) {
  if (array.empty()) {
    return 0;
  }

  array.sort();

  const int arraySize = array.size();
  const bool isOddNumber = arraySize % 2 != 0;

  if (isOddNumber) {
    list<int>::iterator middle = array.begin();
    std::advance(middle, arraySize / 2);
    return *middle;
  } else {
    list<int>::iterator right = array.begin();
    std::advance(right, arraySize / 2);

    list<int>::iterator left = array.begin();
    std::advance(left, (arraySize - 1) / 2);
    return (*left + *right) / 2.0;
  }
}

// No need to call this MATH_happyLinter() function,
// it's just to avoid link error. Method #1
// https://www.codeproject.com/Articles/48575/How-to-define-a-template-class-in-a-h-file-and-imp
__unused void MATH_happyLinter() {
  deque<int> dequeArray;
  Math::findMean(dequeArray);
  Math::findMedian(dequeArray);

  list<int> listArray;
  Math::findMean(listArray);
  Math::findMedian(listArray);

  vector<int> vectorArray;
  Math::findMean(vectorArray);
  Math::findMedian(vectorArray);
}