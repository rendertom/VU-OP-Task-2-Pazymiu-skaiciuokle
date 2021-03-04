#include "Students.hpp"

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

  buffer << names.egzam << "\n";
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

void Students::filter(vector<Student::Student> &students,
                      vector<Student::Student> &filtered,
                      bool (*callback)(Student::Student &)) {
  vector<Student::Student>::iterator it = students.begin();
  while (it != students.end()) {
    if (callback(*it)) {
      filtered.push_back(*it);
      it = students.erase(it);
    } else {
      it++;
    }
  }
}

void Students::save(vector<Student::Student> &students, const string &filePath) {
  stringstream buffer;
  const int numGrades = students[0].grades.size();

  addHeaderToBuffer(buffer, numGrades);

  cout << "Buffering records..." << endl;
  for (int i = 0, il = students.size(); i < il; i++) {
    addStudentToBuffer(students[i], buffer);
  }

  cout << "Saving file..." << endl;
  File::saveBuffer(filePath, buffer);
  cout << "done" << endl;
}
