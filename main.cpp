#include <iomanip>  // std::setw
#include <iostream>
#include <random>  // std::rand, std::srand
#include <string>

#define GRADE_MIN 1
#define GRADE_MAX 10

using namespace std;

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

bool isValidGrade(int grade) {
  return grade >= GRADE_MIN && grade <= GRADE_MAX;
}

bool isOddNumber(int value) {
  return value % 2 != 0;
}

void ClearLine() {
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void arrayCopy(int *targetArray, int *sourceArray, int size) {
  for (int i = 0; i < size; i++) {
    // cout << "Copying: " << sourceArray[i] << endl;
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

double findMean(int *array, int length) {
  int sum = 0;
  for (int i = 0; i < length; i++) {
    sum += array[i];
  }

  return (double)sum / length;
}

double findMedian(int *array, int arrayLength) {
  sort(array, array + arrayLength);

  if (isOddNumber(arrayLength)) {
    return (double)array[arrayLength / 2];
  }

  return (double)(array[(arrayLength - 1) / 2] + array[arrayLength / 2]) / 2.0;
}

void PrintResult(Student *student, bool showMedianGrade = false) {
  cout << left
       << setw(10) << student->firstName
       << setw(15) << student->lastName
       << setw(12) << fixed << setprecision(2)
       << (showMedianGrade ? student->medianGrade : student->finalGrade)
       << endl;
}

void PrintResults(Student *student, bool showMedianGrade = false) {
  cout << left
       << setw(10) << "Vardas"
       << setw(16) << "Pavardė"
       << "Galutinis " << (showMedianGrade ? "Med." : "Vid.") << endl;
  cout << "-----------------------------------------------------------" << endl;

  PrintResult(student, showMedianGrade);
}

void PrintStudent(Student *student) {
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

void ProcessStudent(Student *student, bool shouldCalculateMedian = false) {
  student->finalGrade = 0;
  student->meanGrade = 0;
  student->medianGrade = 0;
  if (student->numGrades > 0) {
    if (shouldCalculateMedian) {
      student->medianGrade = findMedian(student->grades, student->numGrades);
    } else {
      student->meanGrade = findMean(student->grades, student->numGrades);
      student->finalGrade = 0.4 * student->meanGrade + 0.6 * student->examGrade;
    }
  }
}

bool confirm(const string &message, char yes = 'y', char no = 'n') {
  while (true) {
    cout << message << " (" << yes << "/" << no << "): ";

    char response;
    cin >> response;
    cin.clear();
    ClearLine();
    if (response == yes) {
      return true;
    } else if (response == no) {
      return false;
    } else {
      cout << "Unknown character. ";
    }
  }
}

int getRandomIntegerInRange(int min, int max) {
  static bool first = true;
  if (first) {
    srand(time(NULL));  //seeding for the first time only!
    first = false;
  }
  return min + rand() % ((max + 1) - min);
}

int main() {
  Student student;

  cout << "Please enter first name: ";
  getline(cin, student.firstName);

  cout << "Please enter last name: ";
  getline(cin, student.lastName);

  bool shouldGenerateRandomGrades = confirm("Generate RANDOM grades (otherwise, enter grades MANUALLY)?");
  bool numberOfGradesIsKnown = confirm("Do you know the number of grades?");

  if (shouldGenerateRandomGrades) {
    if (numberOfGradesIsKnown) {
      cout << "Enter number of grades: ";
      cin >> student.numGrades;
      cin.clear();
      ClearLine();
      while (student.numGrades < 0) {
        cout << "Value cannot be negative. Please enter new value: ";
        cin >> student.numGrades;
        cin.clear();
        ClearLine();
      }
      student.grades = new int[student.numGrades];
      for (int i = 0; i < student.numGrades; i++) {
        student.grades[i] = getRandomIntegerInRange(GRADE_MIN, GRADE_MAX);
      }
    } else {
      student.numGrades = 0;
      student.grades = new int[student.numGrades];

      int grade = -1;
      while (grade != 0) {
        grade = getRandomIntegerInRange(0, GRADE_MAX);
        if (isValidGrade(grade)) {
          arrayPush(student.grades, student.numGrades, grade);
        }
      }
    }

    cout << "Generated " << student.numGrades << " random grades: ";
    for (int i = 0; i < student.numGrades; i++) {
      cout << student.grades[i] << " ";
    }

    cout << endl;

    student.examGrade = getRandomIntegerInRange(GRADE_MIN, GRADE_MAX);
    cout << "Generated random exam grade: " << student.examGrade << endl;
  } else {
    if (numberOfGradesIsKnown) {
      cout << "Enter number of grades: ";
      cin >> student.numGrades;
      cin.clear();
      ClearLine();
      while (student.numGrades < 0) {
        cout << "Value cannot be negative. Please enter new value: ";
        cin >> student.numGrades;
        cin.clear();
        ClearLine();
      }
      student.grades = new int[student.numGrades];

      if (student.numGrades > 0) {
        cout << "Enter grades: ";
        int gradeIndex = 0;
        while (gradeIndex != student.numGrades) {
          int grade;
          cin >> grade;
          if (!isValidGrade(grade)) {
            cout << "Grade " << grade << " at index " << gradeIndex << " is out of range ("
                 << GRADE_MIN << "-" << GRADE_MAX << "). Fix it and continue entering." << endl;
            cin.clear();
            ClearLine();
          } else {
            student.grades[gradeIndex] = grade;
            gradeIndex++;
          }
        }

        cin.clear();
        ClearLine();
      }
    } else {
      student.numGrades = 0;
      student.grades = new int[student.numGrades];

      int grade;
      while (grade != -1) {
        cout << "Enter grade [" << student.numGrades << "] (type -1 to quit): ";
        cin >> grade;
        cin.clear();
        ClearLine();
        if (grade != -1) {
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
      cin.clear();
      ClearLine();
      cin >> student.examGrade;
    }

    cin.clear();
    ClearLine();
  }

  bool shouldCalculateMedian = confirm("Calculate MEDIAN (otherwise, calculate MEAN)?");
  ProcessStudent(&student, shouldCalculateMedian);
  PrintResults(&student, shouldCalculateMedian);

  cout << "--------------" << endl;
  PrintStudent(&student);

  return 0;
}