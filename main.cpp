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
#define RESULT_TYPE_MEAN "RESULT_TYPE_MEAN"
#define RESULT_TYPE_MEDIAN "RESULT_TYPE_MEDIAN"
#define RESULT_TYPE_BOTH "RESULT_TYPE_BOTH"

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

struct Names {
  string firstName = "Vardas";
  string lastName = "Pavarde";
  string mean = "Galutinis Vid.";
  string median = "Galutinis Med.";
} names;

struct Student {
  string firstName;
  string lastName;
  vector<int> grades;
  int examGrade;
  double meanGrade;
  double finalGrade;
  double medianGrade;
};

struct Width {
  int firstName = 6 + 6;
  int lastName = 7 + 9;
  int mean = 14 + 1;
  int median = 14 + 1;
} width;

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

bool doesFileExist(string filePath) {
  ifstream file(filePath);
  return file.good();
}

double findFinalGrade(double meanGrade, double examGrade) {
  return 0.4 * meanGrade + 0.6 * examGrade;
}

double findMean(vector<int> &array) {
  if (array.empty()) {
    return 0;
  }

  const int arraySize = array.size();
  int sum = 0;
  for (int i = 0; i < arraySize; i++) {
    sum += array[i];
  }

  return (double)sum / arraySize;
}

double findMedian(vector<int> &array) {
  if (array.empty()) {
    return 0;
  }

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

void printRandomGrades(Student &student) {
  cout << "Generated " << student.grades.size() << " random grades: ";
  for (int i = 0; i < student.grades.size(); i++) {
    cout << student.grades[i] << " ";
  }
  cout << endl;
  cout << "Generated random exam grade: " << student.examGrade << endl;
}

void printResult(Student *student, const string &resultType, Width &width) {
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

void printResults(vector<Student> &students, const string &resultType) {
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
       [](const Student &a, const Student &b) {
         return a.lastName != b.lastName
                    ? a.lastName < b.lastName
                    : a.firstName < b.firstName;
       });

  for (int i = 0; i < students.size(); i++) {
    printResult(&students[i], resultType, width);
  }
}

void processStudent(Student *student, const string &resultType) {
  if (resultType == RESULT_TYPE_MEAN) {
    student->meanGrade = findMean(student->grades);
    student->finalGrade = findFinalGrade(student->meanGrade, student->examGrade);
  } else if (resultType == RESULT_TYPE_MEDIAN) {
    student->medianGrade = findMedian(student->grades);
  } else if (resultType == RESULT_TYPE_BOTH) {
    student->meanGrade = findMean(student->grades);
    student->finalGrade = findFinalGrade(student->meanGrade, student->examGrade);
    student->medianGrade = findMedian(student->grades);
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

string promptForString(const string &message) {
  string result;
  cout << "-> " << message;
  getline(cin, result);
  return result;
}

string getResultType() {
  int promptResult = promptForInt("Choose what to calculate: (1)Mean, (2)Median, (3)Both:", 1, 3);

  string resultType = RESULT_TYPE_BOTH;
  if (promptResult == 1) {
    resultType = RESULT_TYPE_MEAN;
  } else if (promptResult == 2) {
    resultType = RESULT_TYPE_MEDIAN;
  }

  return resultType;
}

bool shouldReadFromFile(const string &filePath) {
  bool result = false;
  if (doesFileExist(filePath)) {
    result = confirm("(y)Read grades from file \"" + filePath + "\"; (n)Enter grades manaully:");
  } else {
    cout << "File does not exist at path \"" << filePath << "\". Switching to manual mode." << endl;
  }

  return result;
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

  string filePath = "kursiokai.txt";
  if (shouldReadFromFile(filePath)) {
    Grades_ReadFromFile(filePath, students);
  } else {
    while (true) {
      Student student;
      student.firstName = promptForString("Please enter first name: ");
      student.lastName = promptForString("Please enter last name: ");

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

  string resultType = getResultType();
  for (int i = 0; i < students.size(); i++) {
    processStudent(&students[i], resultType);
  }

  cout << endl;
  printResults(students, resultType);
  cout << endl;

  return 0;
}