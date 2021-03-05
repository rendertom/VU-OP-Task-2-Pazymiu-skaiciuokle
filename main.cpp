// g++ -std=c++11 include/*.cpp 'main.cpp' -o 'main' && './main'

#include <iostream>
#include <string>
#include <vector>

#include "include/Console.hpp"
#include "include/Definitions.hpp"
#include "include/File.hpp"
#include "include/RND.hpp"  // getIntegerInRange
#include "include/Student.hpp"
#include "include/Students.hpp"
#include "include/Timer.hpp"

using std::cout;
using std::endl;
using std::string;
using std::stringstream;
using std::vector;

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

void printRandomGrades(Student::Student &student) {
  const int arraySize = student.grades.size();
  cout << "Generated " << arraySize << " random grades: ";
  for (int i = 0; i < arraySize; i++) {
    cout << student.grades[i] << " ";
  }
  cout << endl;
  cout << "Generated random exam grade: " << student.examGrade << endl;
}

void Grades_EnterManually(bool numberOfGradesIsKnown, int numGrades, Student::Student &student) {
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

void Grades_GenerateRandomly(bool numberOfGradesIsKnown, int numGrades, Student::Student &student) {
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

void Grades_ReadFromFile(const string &filePath, vector<Student::Student> &students) {
  Timer timer;
  timer.start();

  cout << "Buffering file...";
  stringstream buffer = File::getBuffer(filePath);
  cout << timer.elapsed() << endl;

  timer.reset();
  cout << "Processing buffer...";
  string line;
  getline(buffer, line);
  while (getline(buffer, line)) {
    Student::Student student;

    stringstream iss(line);
    iss >> student.firstName >> student.lastName;

    int grade;
    while (iss >> grade) {
      student.grades.push_back(grade);
    }

    student.grades.pop_back();
    student.examGrade = grade;

    students.push_back(student);
  }

  cout << timer.elapsed() << endl;
}

void Data_EnterManually(vector<Student::Student> &students) {
  while (true) {
    Student::Student student;
    student.firstName = Console::promptForString("Please enter first name: ");
    student.lastName = Console::promptForString("Please enter last name: ");

    int numGrades = 0;
    const bool numberOfGradesIsKnown = Console::confirm("Do you know the number of grades?");
    if (numberOfGradesIsKnown) {
      numGrades = Console::promptForInt("Enter number of grades", 0, 100);
    }

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

void Data_GenerateRecords() {
  const int numRecords = Console::promptForInt("How many records:", 1, 10000000);

  Timer timer;
  timer.start();
  Students::generateRecords(numRecords);
  cout << "Total time: " << timer.elapsed() << endl;
}

void Data_FilterRecords() {
  string extension = "txt";
  string folderPath = DATA_FOLDER;
  string fileName = File::selectFileInFolder(folderPath, extension);

  if (fileName.empty()) {
    return;
  }

  Timer timer;
  Timer timeTotal;
  string filePath = folderPath + fileName;
  vector<Student::Student> students;

  timeTotal.reset();
  timer.reset();
  cout << "Reading data from \"" << fileName << "\"..." << endl;
  Grades_ReadFromFile(filePath, students);
  cout << "Reading data from \"" << fileName << "\"..." << timer.elapsed() << endl;

  if (students.empty()) {
    throw std::runtime_error("Error: file \"" + filePath + "\" contains no student data");
  }

  string resultType = RESULT_TYPE_MEAN;
  cout << "Processing students...";
  timer.reset();
  Student::processStudents(students, resultType);
  cout << timer.elapsed() << endl;

  cout << "Sorting students by final grade (descending)...";
  timer.reset();
  Students::sortByFinalGradeDescending(students);
  cout << timer.elapsed() << endl;

  cout << "Searching for the first loser...";
  timer.reset();
  auto it = std::find_if(
      students.begin(), students.end(), Student::isLoser);
  cout << timer.elapsed() << endl;

  cout << "Copying all the losers to a new vector...";
  timer.reset();
  vector<Student::Student> losers(students.end() - it);
  std::copy(it, students.end(), losers.begin());
  cout << timer.elapsed() << endl;

  cout << "Resizing original vector...";
  timer.reset();
  students.resize(it - students.begin());
  cout << timer.elapsed() << endl;

  string baseName = File::getBaseName(fileName);
  cout << "Writing losers to file..." << endl;
  timer.reset();
  Students::save(losers, folderPath + baseName + " losers.txt");
  cout << "Writing losers to file..." << timer.elapsed() << endl;

  cout << "Writing winners to file..." << endl;
  timer.reset();
  Students::save(students, folderPath + baseName + " winners.txt");
  cout << "Writing winners to file..." << timer.elapsed() << endl;

  cout << "Total time: " << timeTotal.elapsed() << endl;
}

void Data_ReadFromFile(vector<Student::Student> &students) {
  string extension = "txt";
  string folderPath = DATA_FOLDER;
  string filePath = File::selectFileInFolder(folderPath, extension);
  if (filePath.empty()) {
    const bool shouldEnterManually = Console::confirm(
        "Do you want to enter grades manually instead?:");

    if (shouldEnterManually) {
      cout << "Switching to manual mode." << endl;
      Data_EnterManually(students);
    } else {
      cout << "Terminating program." << endl;
    }
  } else {
    filePath = folderPath + filePath;
    cout << "Reading data from \"" << filePath << "\"" << endl;
    Grades_ReadFromFile(filePath, students);
  }
}

int main() {
  cout << "1. Generate new records" << endl;
  cout << "2. Filter records" << endl;
  cout << "3. Read grades from a file" << endl;
  cout << "4. Enter grades manually" << endl;
  int selection = Console::promptForInt("Select:", 1, 4);

  try {
    if (selection == 1) {
      Data_GenerateRecords();
    } else if (selection == 2) {
      Data_FilterRecords();
    } else {
      vector<Student::Student> students;
      if (selection == 3) {
        Data_ReadFromFile(students);
      } else if (selection == 4) {
        Data_EnterManually(students);
      }

      if (!students.empty()) {
        string resultType = getResultType();
        Student::processStudents(students, resultType);
        Students::printFormatted(students, resultType);
      }
    }

    return 0;
  } catch (std::exception &error) {
    std::cerr << error.what() << endl;
  }
}