// g++ -std=c++11 include/*.cpp 'main.cpp' -o 'main' && './main'

#include <deque>
#include <iostream>
#include <list>
#include <string>
#include <vector>

#include "include/Console.hpp"
#include "include/Definitions.hpp"
#include "include/File.hpp"
#include "include/Grades.hpp"
#include "include/Student.hpp"
#include "include/Students.hpp"
#include "include/Timer.hpp"

using std::cout;
using std::deque;
using std::endl;
using std::list;
using std::string;
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

template <class A>
void Data_EnterManually(A &students) {
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
      Grades::generateRandomly(numberOfGradesIsKnown, numGrades, student);
    } else {
      Grades::enterManually(numberOfGradesIsKnown, numGrades, student);
    }

    students.push_back(student);
    if (!Console::confirm("Add another student?")) {
      break;
    }
  }
}

void Data_GenerateRecords() {
  vector<int> records = Console::promptForInts("How many records:", 1, 10000000);
  if (records.empty()) {
    return;
  }

  int numRecords = records.size();
  cout << "Will create " << numRecords << " " << ((numRecords == 1) ? "file" : "files") << ": ";
  for (int i = 0; i < numRecords; i++) {
    cout << records[i] << ".txt, ";
  }
  cout << endl;
  cout << std::fixed << std::setprecision(int(TIME_PRECISION));

  Timer timer;
  for (int i = 0; i < numRecords; i++) {
    cout << "Creating \"" << records[i] << ".txt\":" << endl;
    timer.reset();
    Students::generateRecords(records[i]);
    cout << "Total time: " << timer.elapsed() << endl;
    cout << "----------------------" << endl;
  }
}

void Data_FilterRecords() {
  string extension = "txt";
  string folderPath = DATA_FOLDER;
  vector<string> fileNames = File::selectFilesInFolder(folderPath, extension);
  if (fileNames.empty()) {
    return;
  }

  int numFilenames = fileNames.size();
  cout << "Will process " << numFilenames << " " << ((numFilenames == 1) ? "file" : "files") << ": ";
  for (int i = 0; i < numFilenames; i++) {
    cout << fileNames[i] << ", ";
  }
  cout << endl;
  cout << std::fixed << std::setprecision(int(TIME_PRECISION));

  Timer timer;
  for (int i = 0; i < numFilenames; i++) {
    timer.reset();
    Students::filter(fileNames[i]);
    cout << "Total time: " << timer.elapsed() << endl;
    cout << "----------------------" << endl;
  }
}

template <class A>
void Data_ReadFromFile(A &students) {
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
    Students::readFromFile(filePath, students);
  }
}

int main() {
  if (ARRAY_TYPE == TYPE_DEQUE) {
    cout << "(using std::deque)" << endl;
  } else if (ARRAY_TYPE == TYPE_LIST) {
    cout << "(using std::list)" << endl;
  } else if (ARRAY_TYPE == TYPE_VECTOR) {
    cout << "(using std::vector)" << endl;
  }

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
#if ARRAY_TYPE == TYPE_DEQUE
      deque<Student::Student> students;
#elif ARRAY_TYPE == TYPE_LIST
      list<Student::Student> students;
#elif ARRAY_TYPE == TYPE_VECTOR
      vector<Student::Student> students;
#endif

      if (selection == 3) {
        Data_ReadFromFile(students);
      } else if (selection == 4) {
        Data_EnterManually(students);
      }

      if (!students.empty()) {
        string resultType = getResultType();
        Students::processStudents(students, resultType);
        Students::printFormatted(students, resultType);
      }
    }

    return 0;
  } catch (std::exception &error) {
    std::cerr << error.what() << endl;
  }
}