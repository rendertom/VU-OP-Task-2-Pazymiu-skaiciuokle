#include "Grades.hpp"

void printRandomGrades(Student::Student &student) {
  const int arraySize = student.grades.size();
  std::cout << "Generated " << arraySize << " random grades: ";
  for (const int &grade : student.grades) {
    std::cout << grade << " ";
  }
  std::cout << std::endl;
  std::cout << "Generated random exam grade: " << student.examGrade << std::endl;
}

void Grades::enterManually(bool numberOfGradesIsKnown, int numGrades, Student::Student &student) {
  if (numberOfGradesIsKnown) {
    if (numGrades > 0) {
      while (student.grades.size() != numGrades) {
        int grade = Console::promptForInt("Enter grade", GRADE_MIN, GRADE_MAX);
        student.grades.push_back(grade);
      }
    }
  } else {
    while (true) {
      int grade = Console::promptForInt(
          "Enter grade (type -1 to quit)", GRADE_MIN, GRADE_MAX, -1);
      if (grade == -1) {
        break;
      } else {
        student.grades.push_back(grade);
      }
    }
  }

  student.examGrade = Console::promptForInt("Enter exam grade", GRADE_MIN, GRADE_MAX);
}

void Grades::generateRandomly(bool numberOfGradesIsKnown, int numGrades, Student::Student &student) {
  if (numberOfGradesIsKnown) {
    for (int i = 0; i < numGrades; i++) {
      int grade = RND::getIntegerInRange(GRADE_MIN, GRADE_MAX);
      student.grades.push_back(grade);
    }
  } else {
    while (true) {
      int grade = RND::getIntegerInRange(0, GRADE_MAX);
      if (grade == 0) {
        break;
      } else {
        student.grades.push_back(grade);
      }
    }
  }
  student.examGrade = RND::getIntegerInRange(GRADE_MIN, GRADE_MAX);
  printRandomGrades(student);
}
