#pragma once

#include "Console.hpp"
#include "RND.hpp"
#include "Student.hpp"

namespace Grades {
  void enterManually(bool, int, Student::Student &);
  void generateRandomly(bool, int, Student::Student &);
}