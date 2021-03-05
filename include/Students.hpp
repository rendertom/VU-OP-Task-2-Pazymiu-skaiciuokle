#pragma once

#include <algorithm>  // std::sort
#include <iomanip>    // std::fixed, left,setprecision, setw
#include <iostream>
#include <sstream>  // std:: stringstream,
#include <string>
#include <vector>

#include "Console.hpp"
#include "Definitions.hpp"
#include "File.hpp"
#include "RND.hpp"
#include "Student.hpp"
#include "Table.hpp"
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

namespace Students {
  void filter(vector<Student::Student> &,
              vector<Student::Student> &,
              bool (*callback)(Student::Student &));
  void generateRecords(int);
  void printFormated(vector<Student::Student> &, const string &);
  void save(vector<Student::Student> &, const string &);
}