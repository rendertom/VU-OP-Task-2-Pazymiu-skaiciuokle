#pragma once

#include <iostream>
#include <limits>  // std::numeric_limits
#include <string>

using std::cin;
using std::cout;
using std::numeric_limits;
using std::streamsize;
using std::string;

namespace Console {
  void clearLine();
  bool confirm(const string &, char = 'y', char = 'n');
  int promptForInt(const string &, int, int, int = -100);
  string promptForString(const string &);
}