#pragma once

#include "Student.hpp"

namespace Comparator {
  bool sortByFinalGradeDescending(const Student::Student &, const Student::Student &);
  bool sortByNameAscending(const Student::Student &, const Student::Student &);
};