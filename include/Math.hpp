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
  double findMean(vector<int> &);
  double findMedian(vector<int> &);
}