#pragma once

#include <algorithm>  // std::sort
#include <list>
#include <numeric>  // std::accumulate
#include <vector>

using std::list;
using std::vector;

namespace Math {
  template <class A>
  double findMean(A &);

  double findMedian(list<int> &);
  double findMedian(vector<int> &);
}