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
};

void ClearLine() {
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
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
}

int main() {
  Student student;

  cout << "Please enter first name: ";
  getline(cin, student.firstName);

  cout << "Please enter last name: ";
  getline(cin, student.lastName);

  cout << "Enter number of grades: ";
  cin >> student.numGrades;
  student.grades = new int[student.numGrades];
  cin.clear();
  ClearLine();

  cout << "Enter grades: ";
  int gradeIndex = 0;
  while (gradeIndex != student.numGrades) {
    int grade;
    cin >> grade;
    if (grade < GRADE_MIN || grade > GRADE_MAX) {
      cout << "Grade " << grade << " at index " << gradeIndex << " is out of range ("
           << GRADE_MIN << "-" << GRADE_MAX << "). Fix it and continue entering." << endl;
      cin.clear();
      ClearLine();
    } else {
      student.grades[gradeIndex] = grade;
      gradeIndex++;
    }
  }

  return 0;
}