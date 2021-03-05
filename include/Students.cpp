#include "Students.hpp"

void addFormattedStudentToBuffer(Student::Student *student, const string &resultType, stringstream &buffer) {
  struct Table::Width width;

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

void addFormattedHeaderToBuffer(stringstream &buffer, const string &resultType) {
  struct Table::Width width;
  struct Table::Names names;

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

void addHeaderToBuffer(stringstream &buffer, int numGrades) {
  const struct Table::Names names;
  const struct Table::Width width;

  const int gradeWidth = names.homework.size() + Utils::getNumberOfDigits(numGrades) + 1;
  buffer << left
         << setw(width.firstName) << names.firstName
         << setw(width.lastName) << names.lastName;

  for (int i = 1; i <= numGrades; i++) {
    buffer << setw(gradeWidth) << names.homework + std::to_string(i);
  }

  buffer << names.exam << "\n";
}

void addStudentToBuffer(Student::Student &student, stringstream &buffer) {
  const struct Table::Width width;

  buffer << setw(width.firstName) << student.firstName
         << setw(width.lastName) << student.lastName;

  for (int i = 0, il = student.grades.size(); i < il; i++) {
    buffer << setw(5) << student.grades[i];
  }

  buffer << student.examGrade << "\n";
}

void addRandomStudentsToBuffer(stringstream &buffer, int numStudents, int numGrades) {
  const struct Table::Names names;
  const struct Table::Width width;

  for (int i = 1; i <= numStudents; i++) {
    buffer << setw(width.firstName) << names.firstName + std::to_string(i)
           << setw(width.lastName) << names.lastName + std::to_string(i);

    for (int j = 1; j <= numGrades; j++) {
      buffer << setw(5) << RND::getIntegerInRange(GRADE_MIN, GRADE_MAX);
    }

    buffer << RND::getIntegerInRange(GRADE_MIN, GRADE_MAX) << "\n";
  }
}

void Students::generateRecords(int numStudents) {
  Timer timer;
  const int numGrades = 10;
  std::stringstream buffer;

  cout << "Buffering students...";
  timer.reset();
  addHeaderToBuffer(buffer, numGrades);
  addRandomStudentsToBuffer(buffer, numStudents, numGrades);
  cout << timer.elapsed() << endl;

  const string filePath = string(DATA_FOLDER) + "Random " + std::to_string(numStudents) + ".txt";
  cout << "Saving buffer...";
  timer.reset();
  File::saveBuffer(filePath, buffer);
  cout << timer.elapsed() << endl;
}

void Students::printFormatted(vector<Student::Student> &students, const string &resultType) {
  stringstream buffer;
  addFormattedHeaderToBuffer(buffer, resultType);

  cout << "Sorting students by name..." << endl;
  sortByNameAscending(students);

  cout << "Buffering students..." << endl;
  for (int i = 0, il = students.size(); i < il; i++) {
    addFormattedStudentToBuffer(&students[i], resultType, buffer);
  }

  bool shouldSaveFile = Console::confirm("Print to (y)file or (n)console:");

  if (shouldSaveFile) {
    string filePath = string(DATA_FOLDER) + "Formatted.txt";
    cout << "Saving file..." << endl;
    File::saveBuffer(filePath, buffer);
    cout << "File saved" << endl;
  } else {
    cout << buffer.str() << endl;
  }
}

void Students::save(vector<Student::Student> &students, const string &filePath) {
  stringstream buffer;
  const int numGrades = students[0].grades.size();

  Timer timer;
  cout << "Buffering students...";
  timer.reset();
  addHeaderToBuffer(buffer, numGrades);
  for (int i = 0, il = students.size(); i < il; i++) {
    addStudentToBuffer(students[i], buffer);
  }
  cout << timer.elapsed() << endl;

  timer.reset();
  cout << "Writing buffer to file...";
  File::saveBuffer(filePath, buffer);
  cout << timer.elapsed() << endl;
}

void Students::sortByFinalGradeDescending(vector<Student::Student> &students) {
  sort(students.begin(), students.end(),
       [](const Student::Student &a, const Student::Student &b) {
         return a.finalGrade > b.finalGrade;
       });
}

void Students::sortByNameAscending(vector<Student::Student> &students) {
  sort(students.begin(), students.end(),
       [](const Student::Student &a, const Student::Student &b) {
         return a.lastName != b.lastName
                    ? a.lastName < b.lastName
                    : a.firstName < b.firstName;
       });
}