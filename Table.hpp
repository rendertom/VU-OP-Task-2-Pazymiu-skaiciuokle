#include <algorithm>  // std::sort
#include <iomanip>    // std::fixed, left,setprecision, setw
#include <iostream>

#include "Definitions.hpp"
#include "Student.hpp"

using std::cout;
using std::endl;
using std::fixed;
using std::left;
using std::setprecision;
using std::setw;
using std::sort;

struct Names {
  string firstName = "Vardas";
  string lastName = "Pavarde";
  string mean = "Galutinis Vid.";
  string median = "Galutinis Med.";
} names;

struct Width {
  int firstName = 6 + 6;
  int lastName = 7 + 9;
  int mean = 14 + 1;
  int median = 14 + 1;
} width;

namespace Table {

  void printResult(Student::Student *student, const string &resultType) {
    cout << left
         << setw(width.firstName) << student->firstName
         << setw(width.lastName) << student->lastName
         << fixed << setprecision(2);

    if (resultType == RESULT_TYPE_MEAN) {
      cout << setw(width.mean) << student->finalGrade;
    } else if (resultType == RESULT_TYPE_MEDIAN) {
      cout << setw(width.median) << student->medianGrade;
    } else if (resultType == RESULT_TYPE_BOTH) {
      cout << setw(width.mean) << student->finalGrade;
      cout << setw(width.median) << student->medianGrade;
    }

    cout << endl;
  }

  void printResults(vector<Student::Student> &students, const string &resultType) {
    cout << left
         << setw(width.firstName) << names.firstName
         << setw(width.lastName) << names.lastName;

    int tableWidth = width.firstName + width.lastName;

    if (resultType == RESULT_TYPE_MEAN) {
      cout << setw(width.mean) << names.mean;
      tableWidth += width.mean;
    } else if (resultType == RESULT_TYPE_MEDIAN) {
      cout << setw(width.median) << names.median;
      tableWidth += width.median;
    } else if (resultType == RESULT_TYPE_BOTH) {
      cout << setw(width.mean) << names.mean;
      tableWidth += width.mean;
      cout << setw(width.median) << names.median;
      tableWidth += width.median;
    }
    cout << endl;
    cout << string(tableWidth, '-') << endl;

    sort(students.begin(), students.end(),
         [](const Student::Student &a, const Student::Student &b) {
           return a.lastName != b.lastName
                      ? a.lastName < b.lastName
                      : a.firstName < b.firstName;
         });

    for (int i = 0; i < students.size(); i++) {
      printResult(&students[i], resultType);
    }
  }
}