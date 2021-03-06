#include "Student.hpp"

double Student::findFinalGrade(double meanGrade, double examGrade) {
  return 0.4 * meanGrade + 0.6 * examGrade;
}

bool Student::isLoser(Student &student) {
  return student.finalGrade < 5;
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
