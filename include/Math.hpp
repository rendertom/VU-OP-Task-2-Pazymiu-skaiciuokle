#pragma once

#include <algorithm>  // std::sort
#include <deque>
#include <list>
#include <numeric>  // std::accumulate
#include <vector>

using std::deque;
using std::list;
using std::vector;

namespace Math {
  template <class A>
  double findMean(A &);

  template <class A>
  double findMedian(A &);
  double findMedian(list<int> &);
}