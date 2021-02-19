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

double findFinalGrade(double meanGrade, double examGrade) {
  return 0.4 * meanGrade + 0.6 * examGrade;
}

void processStudent(Student *student, const string &resultType) {
  if (resultType == RESULT_TYPE_MEAN) {
    student->meanGrade = Math::findMean(student->grades);
    student->finalGrade = findFinalGrade(student->meanGrade, student->examGrade);
  } else if (resultType == RESULT_TYPE_MEDIAN) {
    student->medianGrade = Math::findMedian(student->grades);
  } else if (resultType == RESULT_TYPE_BOTH) {
    student->meanGrade = Math::findMean(student->grades);
    student->finalGrade = findFinalGrade(student->meanGrade, student->examGrade);
    student->medianGrade = Math::findMedian(student->grades);
  }
}

void processStudents(vector<Student> &students, const string &resultType) {
  for (int i = 0; i < students.size(); i++) {
    processStudent(&students[i], resultType);
  }
}

}  // namespace Student