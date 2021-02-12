#include <algorithm>  //std::sort
#include <iomanip>    // std::setw
#include <iostream>
#include <random>  // std::rand, std::srand
#include <string>

#define GRADE_MIN 1
#define GRADE_MAX 10

using std::cin;
using std::cout;
using std::endl;
using std::fixed;
using std::left;
using std::numeric_limits;
using std::setprecision;
using std::setw;
using std::sort;
using std::streamsize;
using std::string;

struct Student {
  string firstName;
  string lastName;
  int numGrades;
  int *grades;
  int examGrade;
  double meanGrade;
  double finalGrade;
  double medianGrade;
};

void arrayCopy(int *targetArray, int *sourceArray, int size) {
  for (int i = 0; i < size; i++) {
    targetArray[i] = sourceArray[i];
  }
}

void arrayPush(int *&array, int &size, int value) {
  int *tempArray = new int[size + 1];
  arrayCopy(tempArray, array, size);
  tempArray[size] = value;

  delete[] array;
  array = tempArray;
  size++;
}

void clearLine() {
  cin.clear();
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

bool confirm(const string &message, char yes = 'y', char no = 'n') {
  // https://stackoverflow.com/a/9158263
  string colorYellow = "\033[33m";
  string colorReset = "\033[0m";

  while (true) {
    cout << colorYellow << "-> " << message << " (" << yes << "/" << no << "): " << colorReset;

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

double findMean(int *array, int length) {
  int sum = 0;
  for (int i = 0; i < length; i++) {
    sum += array[i];
  }

  return (double)sum / length;
}

double findMedian(int *array, int arrayLength) {
  sort(array, array + arrayLength);

  bool isOddNumber = arrayLength % 2 != 0;

  if (isOddNumber) {
    return (double)array[arrayLength / 2];
  }

  return (double)(array[(arrayLength - 1) / 2] + array[arrayLength / 2]) / 2.0;
}

void freeMemory(Student *students, int numStudents) {
  for (int i = 0; i < numStudents; i++) {
    delete[] students[i].grades;
  }
  delete[] students;
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

void printResult(Student *student, bool showMeanGrade = true) {
  cout << left
       << setw(10) << student->firstName
       << setw(15) << student->lastName
       << setw(12) << fixed << setprecision(2)
       << (showMeanGrade ? student->finalGrade : student->medianGrade)
       << endl;
}

void printResults(Student *students, int numStudents, bool showMeanGrade = true) {
  cout << left
       << setw(10) << "Vardas"
       << setw(16) << "Pavardė"
       << "Galutinis " << (showMeanGrade ? "Vid." : "Med.") << endl;
  cout << "-----------------------------------------------------------" << endl;

  for (int i = 0; i < numStudents; i++) {
    printResult(&students[i], showMeanGrade);
  }
}

void printStudent(Student *student) {
  cout << "First name: " << student->firstName << endl;
  cout << "Last name: " << student->lastName << endl;
  cout << "Number of grades: " << student->numGrades << endl;

  cout << "Grades: ";
  for (int i = 0; i < student->numGrades; i++) {
    cout << student->grades[i] << " ";
  }
  cout << endl;

  cout << "Exam grade: " << student->examGrade << endl;
  cout << "Mean grade: " << student->meanGrade << endl;
  cout << "Final grade: " << student->finalGrade << endl;
  cout << "Median grade: " << student->medianGrade << endl;
}

void processStudent(Student *student, bool shouldCalculateMean = true) {
  student->finalGrade = 0;
  student->meanGrade = 0;
  student->medianGrade = 0;
  if (shouldCalculateMean) {
    if (student->numGrades > 0) {
      student->meanGrade = findMean(student->grades, student->numGrades);
    }
    student->finalGrade = 0.4 * student->meanGrade + 0.6 * student->examGrade;
  } else {
    if (student->numGrades > 0) {
      student->medianGrade = findMedian(student->grades, student->numGrades);
    }
  }
}

void printRandomGrades(Student *student) {
  cout << "Generated " << student->numGrades << " random grades: ";
  for (int i = 0; i < student->numGrades; i++) {
    cout << student->grades[i] << " ";
  }
  cout << endl;
  cout << "Generated random exam grade: " << student->examGrade << endl;
}

void pushStudent(Student *&students, int &numStudents, Student student) {
  Student *tempArray = new Student[numStudents + 1];

  for (int i = 0; i < numStudents; i++) {
    tempArray[i] = students[i];
  }

  tempArray[numStudents] = student;

  delete[] students;
  students = tempArray;
  numStudents++;
}

int main() {
  int numStudents = 0;
  Student *students = new Student[numStudents];

  while (true) {
    Student student;

    cout << "Please enter first name: ";
    getline(cin, student.firstName);

    cout << "Please enter last name: ";
    getline(cin, student.lastName);

    bool numberOfGradesIsKnown = confirm("Do you know the number of grades?");
    student.numGrades = numberOfGradesIsKnown ? getNumberOfGrades() : 0;
    student.grades = new int[student.numGrades];

    bool shouldGenerateRandomGrades = false;
    if (student.numGrades > 0) {
      shouldGenerateRandomGrades = confirm("Generate RANDOM grades (otherwise, enter grades MANUALLY)?");
    }

    if (shouldGenerateRandomGrades) {
      if (numberOfGradesIsKnown) {
        for (int i = 0; i < student.numGrades; i++) {
          student.grades[i] = getRandomIntegerInRange(GRADE_MIN, GRADE_MAX);
        }
      } else {
        while (true) {
          int grade = getRandomIntegerInRange(0, GRADE_MAX);
          if (isValidGrade(grade)) {
            arrayPush(student.grades, student.numGrades, grade);
          } else {
            break;
          }
        }
      }
      student.examGrade = getRandomIntegerInRange(GRADE_MIN, GRADE_MAX);
      printRandomGrades(&student);
    } else {
      if (numberOfGradesIsKnown) {
        if (student.numGrades > 0) {
          cout << "Enter grades: ";
          int gradeIndex = 0;
          while (gradeIndex != student.numGrades) {
            int grade;
            cin >> grade;
            if (!isValidGrade(grade)) {
              cout << "Grade " << grade << " at index " << gradeIndex << " is out of range ("
                   << GRADE_MIN << "-" << GRADE_MAX << "). Fix it and continue entering." << endl;
              clearLine();
            } else {
              student.grades[gradeIndex] = grade;
              gradeIndex++;
            }
          }

          clearLine();
        }
      } else {
        while (true) {
          cout << "Enter grade [" << student.numGrades << "] (type -1 to quit): ";

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
              arrayPush(student.grades, student.numGrades, grade);
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

    pushStudent(students, numStudents, student);
    if (!confirm("Add another student?")) {
      break;
    }
  }

  bool shouldCalculateMean = confirm("Calculate MEAN (otherwise, calculate MEDIAN)?");
  for (int i = 0; i < numStudents; i++) {
    processStudent(&students[i], shouldCalculateMean);
  }

  cout << endl;
  printResults(students, numStudents, shouldCalculateMean);
  cout << endl;

  freeMemory(students, numStudents);

  return 0;
}