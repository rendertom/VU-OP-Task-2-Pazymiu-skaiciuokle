#pragma once

#include <iostream>
#include <sstream>  // std:: stringstream,
#include <string>
#include <vector>

#include "File.hpp"
#include "Student.hpp"
#include "Table.hpp"
#include "Utils.hpp"

using std::cout;
using std::endl;
using std::string;
using std::stringstream;
using std::vector;

namespace Students {
  void filter(vector<Student::Student> &,
                      vector<Student::Student> &,
                      bool (*callback)(Student::Student &));
  void save(vector<Student::Student> &, const string &);
}