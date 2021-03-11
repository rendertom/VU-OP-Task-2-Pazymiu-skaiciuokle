#pragma once

#include <algorithm>  // std::sort
#include <list>
#include <numeric>  // std::accumulate
#include <vector>

using std::list;
using std::vector;

namespace Math {
  double findMean(list<int> &);
  double findMean(vector<int> &);
  double findMedian(list<int> &);
  double findMedian(vector<int> &);
}