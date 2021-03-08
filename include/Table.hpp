#pragma once

#include <iostream>
#include <string>

namespace Table {
  struct Names {
    std::string firstName = "Vardas";
    std::string lastName = "Pavarde";
    std::string mean = "Galutinis Vid.";
    std::string median = "Galutinis Med.";
    std::string homework = "ND";
    std::string exam = "Egz.";
  };

  struct Width {
    int firstName = 6 + 6;
    int lastName = 7 + 9;
    int mean = 14 + 1;
    int median = 14 + 1;
  };
}