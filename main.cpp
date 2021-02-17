#include <algorithm>  // std::sort
#include <fstream>    // std::ifstream
#include <iomanip>    // std::setw
#include <iostream>
#include <random>   // std::rand, std::srand
#include <sstream>  // std::istringstream
#include <string>
#include <vector>

#define GRADE_MIN 1
#define GRADE_MAX 10

using std::cin;
using std::cout;
using std::endl;
using std::fixed;
using std::ifstream;
using std::istringstream;
using std::left;
using std::numeric_limits;
using std::setprecision;
using std::setw;
using std::sort;
using std::streamsize;
using std::string;
using std::vector;

struct Student {
  string firstName;
  string lastName;
  vector<int> grades;
  int examGrade;
  double meanGrade;
  double finalGrade;
  double medianGrade;
};

void clearLine() {
  cin.clear();
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

bool confirm(const string &message, char yes = 'y', char no = 'n') {
  while (true) {
    cout << "-> " << message << " (" << yes << "/" << no << "): ";

    char response;
    cin >> response;
    clearLine();
    if (response == yes) {
      return true;
    } else if (response == no) {
      return false;
    } else {
      cout << "Unknown character. ";
    }
  }
}

double findMean(vector<int> &array) {
  const int arraySize = array.size();
  int sum = 0;
  for (int i = 0; i < arraySize; i++) {
    sum += array[i];
  }

  return (double)sum / arraySize;
}

double findMedian(vector<int> &array) {
  sort(array.begin(), array.end());

  const int arraySize = array.size();
  const bool isOddNumber = arraySize % 2 != 0;

  if (isOddNumber) {
    return (double)array[arraySize / 2];
  }

  return (double)(array[(arraySize - 1) / 2] + array[arraySize / 2]) / 2.0;
}

int getNumberOfGrades() {
  cout << "Enter number of grades: ";
  int numGrades;
  cin >> numGrades;
  clearLine();

  while (numGrades < 0) {
    cout << "Value cannot be negative. Please enter new value: ";
    cin >> numGrades;
    clearLine();
  }

  return numGrades;
}

int getRandomIntegerInRange(int min, int max) {
  static bool first = true;
  if (first) {
    srand(time(NULL));  //seeding for the first time only!
    first = false;
  }
  return min + rand() % ((max + 1) - min);
}

bool isValidGrade(int grade) {
  return grade >= GRADE_MIN && grade <= GRADE_MAX;
}

void printResult(Student *student, int resultType) {
  cout << left
       << setw(10) << student->firstName
       << setw(15) << student->lastName
       << fixed << setprecision(2);

  if (resultType == 1) {  // Mean
    cout << student->finalGrade;
  } else if (resultType == 2) {  // Median
    cout << student->medianGrade;
  } else if (resultType == 3) {  // Both
    cout << setw(16)
         << student->finalGrade
         << student->medianGrade;
  }
  cout << endl;
}

void printResults(vector<Student> &students, int resultType) {
  cout << left
       << setw(10) << "Vardas"
       << setw(16) << "Pavardė";

  if (resultType == 1) {  // Mean
    cout << "Galutinis Vid." << endl;
  } else if (resultType == 2) {  // Median
    cout << "Galutinis Med." << endl;
  } else if (resultType == 3) {  // Both
    cout << "Galutinis Vid.  Galutinis Med." << endl;
  }
  cout << "-----------------------------------------------------------" << endl;

  sort(students.begin(), students.end(),
       [](const Student &a, const Student &b) {
         return a.lastName != b.lastName
                    ? a.lastName < b.lastName
                    : a.firstName < b.firstName;
       });

  for (int i = 0; i < students.size(); i++) {
    printResult(&students[i], resultType);
  }
}

void processStudent(Student *student, int resultType) {
  student->finalGrade = 0;
  student->meanGrade = 0;
  student->medianGrade = 0;
  if (resultType == 1) {  // Mean
    if (student->grades.size() > 0) {
      student->meanGrade = findMean(student->grades);
    }
    student->finalGrade = 0.4 * student->meanGrade + 0.6 * student->examGrade;
  } else if (resultType == 2) {  // Median
    if (student->grades.size() > 0) {
      student->medianGrade = findMedian(student->grades);
    }
  } else if (resultType == 3) {  // Both
    if (student->grades.size() > 0) {
      student->meanGrade = findMean(student->grades);
      student->medianGrade = findMedian(student->grades);
    }
    student->finalGrade = 0.4 * student->meanGrade + 0.6 * student->examGrade;
  }
}

int promptForInt(string message, int min, int max) {
  while (true) {
    cout << "-> " << message << " (" << min << "-" << max << "): ";

    int value;
    cin >> value;
    clearLine();
    if (value >= min && value <= max) {
      return value;
    } else {
      cout << "Value is not in range. ";
    }
  }
}

void printRandomGrades(Student &student) {
  cout << "Generated " << student.grades.size() << " random grades: ";
  for (int i = 0; i < student.grades.size(); i++) {
    cout << student.grades[i] << " ";
  }
  cout << endl;
  cout << "Generated random exam grade: " << student.examGrade << endl;
}

void Grades_EnterManually(bool numberOfGradesIsKnown, int numGrades, Student &student) {
  if (numberOfGradesIsKnown) {
    if (numGrades > 0) {
      cout << "Enter grades: ";
      while (student.grades.size() != numGrades) {
        int grade;
        cin >> grade;
        if (!isValidGrade(grade)) {
          cout << "Grade " << grade << " at index " << student.grades.size() << " is out of range ("
               << GRADE_MIN << "-" << GRADE_MAX << "). Fix it and continue entering." << endl;
          clearLine();
        } else {
          student.grades.push_back(grade);
        }
      }

      clearLine();
    }
  } else {
    while (true) {
      cout << "Enter grade [" << student.grades.size() << "] (type -1 to quit): ";

      int grade;
      cin >> grade;
      clearLine();

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
    clearLine();
    cin >> student.examGrade;
  }

  clearLine();
}

void Grades_GenerateRandomly(bool numberOfGradesIsKnown, int numGrades, Student &student) {
  if (numberOfGradesIsKnown) {
    for (int i = 0; i < numGrades; i++) {
      int grade = getRandomIntegerInRange(GRADE_MIN, GRADE_MAX);
      student.grades.push_back(grade);
    }
  } else {
    while (true) {
      int grade = getRandomIntegerInRange(0, GRADE_MAX);
      if (isValidGrade(grade)) {
        student.grades.push_back(grade);
      } else {
        break;
      }
    }
  }
  student.examGrade = getRandomIntegerInRange(GRADE_MIN, GRADE_MAX);
  printRandomGrades(student);
}

void Grades_ReadFromFile(const string &filePath, vector<Student> &students) {
  ifstream file;
  file.open(filePath);

  if (!file) {
    cout << "Error: file could not be opened" << endl;
    exit(1);
  }

  string line;
  getline(file, line);
  while (getline(file, line)) {
    Student student;

    istringstream iss(line);
    iss >> student.firstName >> student.lastName;

    int grade;
    while (iss >> grade) {
      student.grades.push_back(grade);
    }

    student.grades.pop_back();
    student.examGrade = grade;

    students.push_back(student);
  }

  file.close();
}

int main() {
  vector<Student> students;

  string filePath = "students test.txt";
  bool shouldReadFromFile = confirm("(y) Read data from \"" + filePath + "\"; (n) Enter grades manaully:");
  if (shouldReadFromFile) {
    Grades_ReadFromFile(filePath, students);
  } else {
    while (true) {
      Student student;

      cout << "Please enter first name: ";
      getline(cin, student.firstName);

      cout << "Please enter last name: ";
      getline(cin, student.lastName);

      const bool numberOfGradesIsKnown = confirm("Do you know the number of grades?");
      const int numGrades = numberOfGradesIsKnown ? getNumberOfGrades() : 0;

      bool shouldGenerateRandomGrades = false;
      if (!numberOfGradesIsKnown || numGrades > 0) {
        shouldGenerateRandomGrades = confirm("Generate RANDOM grades (otherwise, enter grades MANUALLY)?");
      }

      if (shouldGenerateRandomGrades) {
        Grades_GenerateRandomly(numberOfGradesIsKnown, numGrades, student);
      } else {
        Grades_EnterManually(numberOfGradesIsKnown, numGrades, student);
      }

      students.push_back(student);
      if (!confirm("Add another student?")) {
        break;
      }
    }
  }

  int resultType = promptForInt("Choose what to calculate: (1)Mean, (2)Median, (3)Both:", 1, 3);
  for (int i = 0; i < students.size(); i++) {
    processStudent(&students[i], resultType);
  }

  cout << endl;
  printResults(students, resultType);
  cout << endl;

  return 0;
}