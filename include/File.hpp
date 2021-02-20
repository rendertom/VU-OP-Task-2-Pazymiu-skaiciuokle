#pragma once

#include <fstream>  // std::ifstream
#include <iostream>
#include <sstream>  // std::stringstream
#include <string>

using std::cout;
using std::endl;
using std::ifstream;
using std::string;
using std::stringstream;

namespace File {
  bool doesFileExist(const string &);
  stringstream getBuffer(const string &);
}