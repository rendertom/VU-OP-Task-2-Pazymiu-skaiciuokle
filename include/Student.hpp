#pragma once

#include <deque>
#include <iostream>
#include <list>
#include <string>
#include <vector>

#include "Definitions.hpp"
#include "Math.hpp"

using std::deque;
using std::list;
using std::string;
using std::vector;

namespace Student {

  struct Student {
#if ARRAY_TYPE == TYPE_DEQUE
    deque<int> grades;
#elif ARRAY_TYPE == TYPE_LIST
    list<int> grades;
#elif ARRAY_TYPE == TYPE_VECTOR
    vector<int> grades;
#endif

    string firstName;
    string lastName;
    int examGrade;
    double meanGrade;
    double finalGrade;
    double medianGrade;
  };

  double findFinalGrade(double, double);
  bool isLoser(Student &);
  void processStudent(Student *, const string &);
}