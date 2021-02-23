#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "Definitions.hpp"
#include "Math.hpp"

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
  void processStudent(Student *, const string &);
  void processStudents(vector<Student> &, const string &);
}