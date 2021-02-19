#include <iostream>
#include <sstream>  // std::stringstream
#include <string>
#include <vector>

#include "Console.hpp"
#include "Definitions.hpp"
#include "File.hpp"
#include "RND.hpp"  // getIntegerInRange
#include "Student.hpp"
#include "Table.hpp"
#include "Timer.hpp"

#define GRADE_MIN 1
#define GRADE_MAX 10

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::stringstream;
using std::vector;

int getNumberOfGrades() {
  cout << "Enter number of grades: ";
  int numGrades;
  cin >> numGrades;
  Console::clearLine();

  while (numGrades < 0) {
    cout << "Value cannot be negative. Please enter new value: ";
    cin >> numGrades;
    Console::clearLine();
  }

  return numGrades;
}

string getResultType() {
  int promptResult = Console::promptForInt("Choose what to calculate: (1)Mean, (2)Median, (3)Both:", 1, 3);

  string resultType = RESULT_TYPE_BOTH;
  if (promptResult == 1) {
    resultType = RESULT_TYPE_MEAN;
  } else if (promptResult == 2) {
    resultType = RESULT_TYPE_MEDIAN;
  }

  return resultType;
}

bool isValidGrade(int grade) {
  return grade >= GRADE_MIN && grade <= GRADE_MAX;
}

void printRandomGrades(Student::Student &student) {
  cout << "Generated " << student.grades.size() << " random grades: ";
  for (int i = 0; i < student.grades.size(); i++) {
    cout << student.grades[i] << " ";
  }
  cout << endl;
  cout << "Generated random exam grade: " << student.examGrade << endl;
}

bool shouldReadFromFile(const string &filePath) {
  bool result = false;
  if (File::doesFileExist(filePath)) {
    result = Console::confirm("(y)Read grades from file \"" + filePath + "\"; (n)Enter grades manaully:");
  } else {
    cout << "File does not exist at path \"" << filePath << "\". Switching to manual mode." << endl;
  }

  return result;
}

void Grades_EnterManually(bool numberOfGradesIsKnown, int numGrades, Student::Student &student) {
  if (numberOfGradesIsKnown) {
    if (numGrades > 0) {
      cout << "Enter grades: ";
      while (student.grades.size() != numGrades) {
        int grade;
        cin >> grade;
        if (!isValidGrade(grade)) {
          cout << "Grade " << grade << " at index " << student.grades.size() << " is out of range ("
               << GRADE_MIN << "-" << GRADE_MAX << "). Fix it and continue entering." << endl;
          Console::clearLine();
        } else {
          student.grades.push_back(grade);
        }
      }

      Console::clearLine();
    }
  } else {
    while (true) {
      cout << "Enter grade [" << student.grades.size() << "] (type -1 to quit): ";

      int grade;
      cin >> grade;
      Console::clearLine();

      if (grade == -1) {
        break;
      } else {
        if (!isValidGrade(grade)) {
          cout << "Grade " << grade << " is out of range ("
               << GRADE_MIN << "-" << GRADE_MAX << ")." << endl;
        } else {
          student.grades.push_back(grade);
        }
      }
    }
  }

  cout << "Enter exam grade: ";
  cin >> student.examGrade;
  while (!isValidGrade(student.examGrade)) {
    cout << "Grade " << student.examGrade << " is out of range ("
         << GRADE_MIN << "-" << GRADE_MAX << "). Fix it and continue entering." << endl;
    Console::clearLine();
    cin >> student.examGrade;
  }

  Console::clearLine();
}

void Grades_GenerateRandomly(bool numberOfGradesIsKnown, int numGrades, Student::Student &student) {
  if (numberOfGradesIsKnown) {
    for (int i = 0; i < numGrades; i++) {
      int grade = RND::getIntegerInRange(GRADE_MIN, GRADE_MAX);
      student.grades.push_back(grade);
    }
  } else {
    while (true) {
      int grade = RND::getIntegerInRange(0, GRADE_MAX);
      if (isValidGrade(grade)) {
        student.grades.push_back(grade);
      } else {
        break;
      }
    }
  }
  student.examGrade = RND::getIntegerInRange(GRADE_MIN, GRADE_MAX);
  printRandomGrades(student);
}

void Grades_ReadFromFile(const string &filePath, vector<Student::Student> &students) {
  string line;
  vector<string> lines;
  stringstream buffer = File::getBuffer(filePath);
  Timer timer;
  timer.start();

  while (!buffer.eof()) {
    getline(buffer, line);
    lines.push_back(line);
  }

  int arraySize = lines.size();
  for (int i = 1; i < arraySize; i++) {
    Student::Student student;

    stringstream iss(lines[i]);
    iss >> student.firstName >> student.lastName;

    int grade;
    while (iss >> grade) {
      student.grades.push_back(grade);
    }

    student.grades.pop_back();
    student.examGrade = grade;

    students.push_back(student);
  }

  cout << "Reading data from file took " << timer.elapsed() << endl;
}

int main() {
  vector<Student::Student> students;

  string filePath = "kursiokai.txt";
  if (shouldReadFromFile(filePath)) {
    Grades_ReadFromFile(filePath, students);
  } else {
    while (true) {
      Student::Student student;
      student.firstName = Console::promptForString("Please enter first name: ");
      student.lastName = Console::promptForString("Please enter last name: ");

      const bool numberOfGradesIsKnown = Console::confirm("Do you know the number of grades?");
      const int numGrades = numberOfGradesIsKnown ? getNumberOfGrades() : 0;

      bool shouldGenerateRandomGrades = false;
      if (!numberOfGradesIsKnown || numGrades > 0) {
        shouldGenerateRandomGrades = Console::confirm("Generate RANDOM grades (otherwise, enter grades MANUALLY)?");
      }

      if (shouldGenerateRandomGrades) {
        Grades_GenerateRandomly(numberOfGradesIsKnown, numGrades, student);
      } else {
        Grades_EnterManually(numberOfGradesIsKnown, numGrades, student);
      }

      students.push_back(student);
      if (!Console::confirm("Add another student?")) {
        break;
      }
    }
  }

  string resultType = getResultType();
  Student::processStudents(students, resultType);

  cout << endl;
  Table::printResults(students, resultType);
  cout << endl;

  return 0;
}