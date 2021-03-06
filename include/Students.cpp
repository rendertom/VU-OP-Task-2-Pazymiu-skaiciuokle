#include "Students.hpp"

void addFormattedStudentToBuffer(Student::Student *student, const string &resultType, stringstream &buffer) {
  struct Table::Width width;

  buffer << left
         << setw(width.firstName) << student->firstName
         << setw(width.lastName) << student->lastName
         << fixed << setprecision(2);

  if (resultType == RESULT_TYPE_MEAN) {
    buffer << setw(width.mean) << student->finalGrade;
  } else if (resultType == RESULT_TYPE_MEDIAN) {
    buffer << setw(width.median) << student->medianGrade;
  } else if (resultType == RESULT_TYPE_BOTH) {
    buffer << setw(width.mean) << student->finalGrade;
    buffer << setw(width.median) << student->medianGrade;
  }

  buffer << "\n";
}

void addFormattedHeaderToBuffer(stringstream &buffer, const string &resultType) {
  struct Table::Width width;
  struct Table::Names names;

  buffer << left
         << setw(width.firstName) << names.firstName
         << setw(width.lastName) << names.lastName;

  int tableWidth = width.firstName + width.lastName;

  if (resultType == RESULT_TYPE_MEAN) {
    buffer << setw(width.mean) << names.mean;
    tableWidth += width.mean;
  } else if (resultType == RESULT_TYPE_MEDIAN) {
    buffer << setw(width.median) << names.median;
    tableWidth += width.median;
  } else if (resultType == RESULT_TYPE_BOTH) {
    buffer << setw(width.mean) << names.mean;
    tableWidth += width.mean;
    buffer << setw(width.median) << names.median;
    tableWidth += width.median;
  }

  buffer << "\n";
  buffer << string(tableWidth, '-') << "\n";
}

void addHeaderToBuffer(stringstream &buffer, int numGrades) {
  const struct Table::Names names;
  const struct Table::Width width;

  const int gradeWidth = names.homework.size() + Utils::getNumberOfDigits(numGrades) + 1;
  buffer << left
         << setw(width.firstName) << names.firstName
         << setw(width.lastName) << names.lastName;

  for (int i = 1; i <= numGrades; i++) {
    buffer << setw(gradeWidth) << names.homework + std::to_string(i);
  }

  buffer << names.exam << "\n";
}

void addStudentToBuffer(Student::Student &student, stringstream &buffer) {
  const struct Table::Width width;

  buffer << setw(width.firstName) << student.firstName
         << setw(width.lastName) << student.lastName;

  for (const int &grade : student.grades) {
    buffer << setw(5) << grade;
  }

  buffer << student.examGrade << "\n";
}

void addRandomStudentsToBuffer(stringstream &buffer, int numStudents, int numGrades) {
  const struct Table::Names names;
  const struct Table::Width width;

  for (int i = 1; i <= numStudents; i++) {
    buffer << setw(width.firstName) << names.firstName + std::to_string(i)
           << setw(width.lastName) << names.lastName + std::to_string(i);

    for (int j = 1; j <= numGrades; j++) {
      buffer << setw(5) << RND::getIntegerInRange(GRADE_MIN, GRADE_MAX);
    }

    buffer << RND::getIntegerInRange(GRADE_MIN, GRADE_MAX) << "\n";
  }
}

template <class A>
void copyStudents(A &students, A &losers, typename A::iterator &it) {
  losers.resize(students.end() - it);
  std::copy(it, students.end(), losers.begin());
}

void copyStudents(list<Student::Student> &students,
                  list<Student::Student> &losers,
                  list<Student::Student>::iterator &it) {
  losers.assign(it, students.end());
}

template <class A>
void writeToFile(A &array, const string &name, const string &baseName) {
  if (array.empty()) {
    cout << "Class contains no " << name << endl;
  } else {
    string folderPath = DATA_FOLDER;
    Timer timer;

    cout << "Writing " << name << " to file..." << endl;
    timer.reset();
    Students::save(array, folderPath + baseName + " " + name + ".txt");
    cout << "Writing " << name << " to file..." << timer.elapsed() << endl;
  }
}

template <class A>
void doFiltering(A &students, A &losers, A &winners, const string &fileName, const int &filteringIndex) {
  Timer timer;
  string folderPath = DATA_FOLDER;
  string filePath = folderPath + fileName;
  string baseName = File::getBaseName(fileName);

  timer.reset();
  cout << "Reading data from \"" << fileName << "\"..." << endl;
  Students::readFromFile(filePath, students);
  cout << "Reading data from \"" << fileName << "\"..." << timer.elapsed() << endl;

  if (students.empty()) {
    throw std::runtime_error("Error: file \"" + filePath + "\" contains no student data");
  }

  string resultType = RESULT_TYPE_MEAN;
  cout << "Processing students...";
  timer.reset();
  Students::processStudents(students, resultType);
  cout << timer.elapsed() << endl;

  cout << "Using filtering strategy #" << filteringIndex << endl;

  if (filteringIndex == 1) {
    cout << "Sorting students into 2 containers...";
    timer.reset();
    for (auto &student : students) {
      if (Student::isLoser(student)) {
        losers.push_back(student);
      } else {
        winners.push_back(student);
      }
    }
    cout << timer.elapsed() << endl;

    writeToFile(losers, "losers", baseName);
    writeToFile(winners, "winners", baseName);
  } else if (filteringIndex == 2) {
    cout << "Sorting students and erasing...";
    timer.reset();
    typename A::iterator it = students.begin();
    while (it != students.end()) {
      if (Student::isLoser(*it)) {
        losers.push_back(*it);
        it = students.erase(it);
      } else {
        ++it;
      }
    }
    cout << timer.elapsed() << endl;

    writeToFile(losers, "losers", baseName);
    writeToFile(students, "winners", baseName);
  } else if (filteringIndex == 3) {
    cout << "Sorting students by final grade (descending)...";
    timer.reset();
    Students::sortByFinalGradeDescending(students);
    cout << timer.elapsed() << endl;

    cout << "Searching for the first loser...";
    timer.reset();
    typename A::iterator it = std::find_if(
        students.begin(), students.end(), Student::isLoser);
    cout << timer.elapsed() << endl;

    cout << "Copying all the losers to a new vector...";
    timer.reset();
    copyStudents(students, losers, it);
    cout << timer.elapsed() << endl;

    cout << "Resizing original vector...";
    timer.reset();
    students.resize(students.size() - losers.size());
    cout << timer.elapsed() << endl;

    writeToFile(losers, "losers", baseName);
    writeToFile(students, "winners", baseName);
  } else {
    cout << "Filtering strategy #" << filteringIndex << " not implemented" << endl;
    exit(1);
  }
}

void Students::filter(const string &fileName, const string &containerType, const int &filteringStrategy) {
  if (containerType == CONTAINER_DEQUE) {
    deque<Student::Student> students;
    deque<Student::Student> losers;
    deque<Student::Student> winners;
    doFiltering(students, losers, winners, fileName, filteringStrategy);
  } else if (containerType == CONTAINER_LIST) {
    list<Student::Student> students;
    list<Student::Student> losers;
    list<Student::Student> winners;
    doFiltering(students, losers, winners, fileName, filteringStrategy);
  } else if (containerType == CONTAINER_VECTOR) {
    vector<Student::Student> students;
    vector<Student::Student> losers;
    vector<Student::Student> winners;
    doFiltering(students, losers, winners, fileName, filteringStrategy);
  }
}

void Students::generateRecords(int numStudents) {
  Timer timer;
  const int numGrades = 10;
  std::stringstream buffer;

  cout << "Buffering students...";
  timer.reset();
  addHeaderToBuffer(buffer, numGrades);
  addRandomStudentsToBuffer(buffer, numStudents, numGrades);
  cout << timer.elapsed() << endl;

  const string filePath = string(DATA_FOLDER) + "Random " + std::to_string(numStudents) + ".txt";
  cout << "Saving buffer...";
  timer.reset();
  File::saveBuffer(filePath, buffer);
  cout << timer.elapsed() << endl;
}

template <class A>
void Students::printFormatted(A &students, const string &resultType) {
  stringstream buffer;
  addFormattedHeaderToBuffer(buffer, resultType);

  cout << "Sorting students by name..." << endl;
  sortByNameAscending(students);

  cout << "Buffering students..." << endl;
  for (auto &student : students) {
    addFormattedStudentToBuffer(&student, resultType, buffer);
  }

  bool shouldSaveFile = Console::confirm("Print to (y)file or (n)console:");

  if (shouldSaveFile) {
    string filePath = string(DATA_FOLDER) + "Formatted.txt";
    cout << "Saving file..." << endl;
    File::saveBuffer(filePath, buffer);
    cout << "File saved" << endl;
  } else {
    cout << buffer.str() << endl;
  }
}

template <class A>
void Students::processStudents(A &students, const string &resultType) {
  // TODO: Does not compile with -O3 flag on
  // VSCode and CLion without cout << endl;
  cout << endl;

  for (auto &student : students) {
    Student::processStudent(&student, resultType);
  }
}

template <class A>
void Students::readFromFile(const string &filePath, A &students) {
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

template <class A>
void Students::save(A &students, const string &filePath) {
  stringstream buffer;
  const int numGrades = students.front().grades.size();

  Timer timer;
  cout << "Buffering students...";
  timer.reset();
  addHeaderToBuffer(buffer, numGrades);
  for (auto &student : students) {
    addStudentToBuffer(student, buffer);
  }

  cout << timer.elapsed() << endl;

  timer.reset();
  cout << "Writing buffer to file...";
  File::saveBuffer(filePath, buffer);
  cout << timer.elapsed() << endl;
}

template <class A>
void Students::sortByFinalGradeDescending(A &students) {
  sort(students.begin(), students.end(), Comparator::sortByFinalGradeDescending);
}

void Students::sortByFinalGradeDescending(list<Student::Student> &students) {
  students.sort(Comparator::sortByFinalGradeDescending);
}

template <class A>
void Students::sortByNameAscending(A &students) {
  sort(students.begin(), students.end(), Comparator::sortByNameAscending);
}

void Students::sortByNameAscending(list<Student::Student> &students) {
  students.sort(Comparator::sortByNameAscending);
}

// No need to call this STUDENTS_happyLinter() function,
// it's just to avoid link error. Method #1
// https://www.codeproject.com/Articles/48575/How-to-define-a-template-class-in-a-h-file-and-imp
__unused void STUDENTS_happyLinter() {
  deque<Student::Student> dequeArray;
  Students::printFormatted(dequeArray, "");
  Students::processStudents(dequeArray, "");
  Students::readFromFile("", dequeArray);

  list<Student::Student> listArray;
  Students::printFormatted(listArray, "");
  Students::processStudents(listArray, "");
  Students::readFromFile("", listArray);

  vector<Student::Student> vectorArray;
  Students::printFormatted(vectorArray, "");
  Students::processStudents(vectorArray, "");
  Students::readFromFile("", vectorArray);
}