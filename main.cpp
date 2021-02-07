#include <iomanip>  // std::setw
#include <iostream>
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

bool isGradeInRange(int grade) {
  return grade >= GRADE_MIN && grade <= GRADE_MAX;
}

bool isOddNumber(int value) {
  return value % 2 != 0;
}

void ClearLine() {
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
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

void PrintResult(Student *student) {
  cout << left
       << setw(10) << student->firstName
       << setw(15) << student->lastName
       << setw(12) << fixed << setprecision(2)
       << student->finalGrade << student->medianGrade
       << endl;
}

void PrintResults(Student *student) {
  cout << left
       << setw(10) << "Vardas"
       << setw(16) << "Pavardė"
       << "Galutinis / Medianas" << endl;
  cout << "-----------------------------------------------------------" << endl;

  PrintResult(student);
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

void ProcessStudent(Student *student) {
  student->finalGrade = 0;
  student->meanGrade = 0;
  student->medianGrade = 0;
  if (student->numGrades > 0) {
    student->meanGrade = findMean(student->grades, student->numGrades);
    student->finalGrade = 0.4 * student->meanGrade + 0.6 * student->examGrade;
    student->medianGrade = findMedian(student->grades, student->numGrades);
  }
}

int main() {
  Student student;

  cout << "Please enter first name: ";
  getline(cin, student.firstName);

  cout << "Please enter last name: ";
  getline(cin, student.lastName);

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
      if (!isGradeInRange(grade)) {
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

  cout << "Enter exam grade: ";
  cin >> student.examGrade;
  while (!isGradeInRange(student.examGrade)) {
    cout << "Grade " << student.examGrade << " is out of range ("
         << GRADE_MIN << "-" << GRADE_MAX << "). Fix it and continue entering." << endl;
    cin.clear();
    ClearLine();
    cin >> student.examGrade;
  }

  cin.clear();
  ClearLine();

  ProcessStudent(&student);
  PrintResults(&student);

  cout << "--------------" << endl;
  PrintStudent(&student);

  return 0;
}