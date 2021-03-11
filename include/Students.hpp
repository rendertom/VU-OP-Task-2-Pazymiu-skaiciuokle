#pragma once

#include <algorithm>  // std::sort, copy
#include <deque>
#include <iomanip>  // std::fixed, left,setprecision, setw
#include <iostream>
#include <list>
#include <sstream>  // std:: stringstream,
#include <string>
#include <vector>

#include "Comparator.hpp"
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
using std::deque;
using std::endl;
using std::fixed;
using std::left;
using std::list;
using std::setprecision;
using std::setw;
using std::sort;
using std::string;
using std::stringstream;
using std::vector;

namespace Students {
  void filter(const string &);
  void generateRecords(int);

  template <class A>
  void printFormatted(A &, const string &);

  template <class A>
  void processStudents(A &, const string &);

  template <class A>
  void readFromFile(const string &, A &);

  template <class A>
  void save(A &, const string &);

  void sortByFinalGradeDescending(deque<Student::Student> &);
  void sortByFinalGradeDescending(list<Student::Student> &);
  void sortByFinalGradeDescending(vector<Student::Student> &);

  void sortByNameAscending(deque<Student::Student> &);
  void sortByNameAscending(list<Student::Student> &);
  void sortByNameAscending(vector<Student::Student> &);
}