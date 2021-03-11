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
    string firstName;
    string lastName;
    vector<int> grades;
    int examGrade;
    double meanGrade;
    double finalGrade;
    double medianGrade;
  };

  double findFinalGrade(double, double);
  bool isLoser(Student &);
  void processStudent(Student *, const string &);
}