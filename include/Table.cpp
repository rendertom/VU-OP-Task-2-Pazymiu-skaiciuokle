#include "Table.hpp"

void Table::printResult(Student::Student *student, const string &resultType) {
  struct Width width;
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

void Table::printResults(vector<Student::Student> &students, const string &resultType) {
  struct Width width;
  struct Names names;

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

  for (int i = 0, il = students.size(); i < il; i++) {
    printResult(&students[i], resultType);
  }
}
