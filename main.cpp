#include <iostream>
#include <string>

using namespace std;

struct Student {
  string firstName;
  string lastName;
  int numGrades;
};

void ClearLine() {
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void PrintStudent(Student *student) {
  cout << "First name: " << student->firstName << endl;
  cout << "Last name: " << student->lastName << endl;
  cout << "Number of grades: " << student->numGrades << endl;
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

  return 0;
}