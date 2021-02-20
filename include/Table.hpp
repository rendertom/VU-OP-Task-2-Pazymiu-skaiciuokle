#pragma once

#include <algorithm>  // std::sort
#include <iomanip>    // std::fixed, left,setprecision, setw
#include <iostream>
#include <string>

#include "Definitions.hpp"
#include "Student.hpp"

using std::cout;
using std::endl;
using std::fixed;
using std::left;
using std::setprecision;
using std::setw;
using std::sort;
using std::string;

namespace Table {
  struct Names {
    string firstName = "Vardas";
    string lastName = "Pavarde";
    string mean = "Galutinis Vid.";
    string median = "Galutinis Med.";
  };

  struct Width {
    int firstName = 6 + 6;
    int lastName = 7 + 9;
    int mean = 14 + 1;
    int median = 14 + 1;
  };

  void printResult(Student::Student *, const string &);
  void printResults(vector<Student::Student> &, const string &);
}