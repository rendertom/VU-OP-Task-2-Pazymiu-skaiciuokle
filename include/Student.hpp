#pragma once

#include <iostream>
#include <list>
#include <string>
#include <vector>

#include "Definitions.hpp"
#include "Math.hpp"

using std::list;
using std::string;
using std::vector;

namespace Student {

  struct Student {
#ifdef ARRAY_TYPE_LIST
    list<int> grades;
#endif

#ifdef ARRAY_TYPE_VECTOR
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