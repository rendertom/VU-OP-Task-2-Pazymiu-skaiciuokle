#pragma once

#include <algorithm>  // std::sort, copy
#include <iomanip>    // std::fixed, left,setprecision, setw
#include <iostream>
#include <sstream>  // std:: stringstream,
#include <string>
#include <vector>
#include <list>

#include "Console.hpp"
#include "Definitions.hpp"
#include "File.hpp"
#include "Grades.hpp"
#include "RND.hpp"
#include "Student.hpp"
#include "Table.hpp"
#include "Timer.hpp"
#include "Utils.hpp"

using std::cout;
using std::endl;
using std::fixed;
using std::left;
using std::setprecision;
using std::setw;
using std::sort;
using std::string;
using std::stringstream;
using std::vector;
using std::list;

namespace Students {
  void filter(const string &);
  void generateRecords(int);
  void printFormatted(vector<Student::Student> &, const string &);
  void processStudents(list<Student::Student> &, const string &);
  void processStudents(vector<Student::Student> &, const string &);
  void readFromFile(const string &, list<Student::Student> &);
  void readFromFile(const string &, vector<Student::Student> &);
  void save(list<Student::Student> &, const string &);
  void save(vector<Student::Student> &, const string &);
  void sortByFinalGradeDescending(list<Student::Student> &);
  void sortByFinalGradeDescending(vector<Student::Student> &);
  void sortByNameAscending(vector<Student::Student> &);
}