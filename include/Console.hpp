#pragma once

#include <iostream>
#include <limits>  // std::numeric_limits
#include <sstream>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::numeric_limits;
using std::streamsize;
using std::string;
using std::stringstream;
using std::vector;

namespace Console {
  void clearLine();
  bool confirm(const string &, char = 'y', char = 'n');
  int promptForInt(const string &, int, int, int = -100);
  vector<int> promptForInts(const string &, int, int);
  string promptForString(const string &);
}