#include "Student.hpp"

double Student::findFinalGrade(double meanGrade, double examGrade) {
  return 0.4 * meanGrade + 0.6 * examGrade;
}

void Student::processStudent(Student *student, const string &resultType) {
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

void Student::processStudents(vector<Student> &students, const string &resultType) {
  for (int i = 0, il = students.size(); i < il; i++) {
    processStudent(&students[i], resultType);
  }
}
