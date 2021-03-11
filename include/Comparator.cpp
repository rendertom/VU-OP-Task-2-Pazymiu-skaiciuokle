#include "Comparator.hpp"

bool Comparator::sortByFinalGradeDescending(const Student::Student &a, const Student::Student &b) {
  return a.finalGrade > b.finalGrade;
}

bool Comparator::sortByNameAscending(const Student::Student &a, const Student::Student &b) {
  return a.lastName != b.lastName
             ? a.lastName < b.lastName
             : a.firstName < b.firstName;
}