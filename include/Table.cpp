#include "Table.hpp"

void Table::addStudentToBuffer(Student::Student *student, const string &resultType, stringstream &buffer) {
  struct Width width;

  buffer << left
         << setw(width.firstName) << student->firstName
         << setw(width.lastName) << student->lastName
         << fixed << setprecision(2);

  if (resultType == RESULT_TYPE_MEAN) {
    buffer << setw(width.mean) << student->finalGrade;
  } else if (resultType == RESULT_TYPE_MEDIAN) {
    buffer << setw(width.median) << student->medianGrade;
  } else if (resultType == RESULT_TYPE_BOTH) {
    buffer << setw(width.mean) << student->finalGrade;
    buffer << setw(width.median) << student->medianGrade;
  }

  buffer << "\n";
}

void Table::addHeaderToBuffer(stringstream &buffer, const string &resultType) {
  struct Width width;
  struct Names names;

  buffer << left
         << setw(width.firstName) << names.firstName
         << setw(width.lastName) << names.lastName;

  int tableWidth = width.firstName + width.lastName;

  if (resultType == RESULT_TYPE_MEAN) {
    buffer << setw(width.mean) << names.mean;
    tableWidth += width.mean;
  } else if (resultType == RESULT_TYPE_MEDIAN) {
    buffer << setw(width.median) << names.median;
    tableWidth += width.median;
  } else if (resultType == RESULT_TYPE_BOTH) {
    buffer << setw(width.mean) << names.mean;
    tableWidth += width.mean;
    buffer << setw(width.median) << names.median;
    tableWidth += width.median;
  }

  buffer << "\n";
  buffer << string(tableWidth, '-') << "\n";
}

void Table::print(vector<Student::Student> &students, const string &resultType) {
  cout << "start 1" << endl;
  stringstream buffer;
  addHeaderToBuffer(buffer, resultType);

  cout << "Sorting students..." << endl;
  sort(students.begin(), students.end(),
       [](const Student::Student &a, const Student::Student &b) {
         return a.lastName != b.lastName
                    ? a.lastName < b.lastName
                    : a.firstName < b.firstName;
       });

  cout << "Buffering students..." << endl;
  for (int i = 0, il = students.size(); i < il; i++) {
    addStudentToBuffer(&students[i], resultType, buffer);
  }

  bool shouldSaveFile = Console::confirm("Print to (y)file or (n)console:");

  if (shouldSaveFile) {
    cout << "Saving file..." << endl;
    File::saveBuffer("-- result --.txt", buffer);
    cout << "File saved" << endl;
  } else {
    cout << buffer.str() << endl;
  }
}
