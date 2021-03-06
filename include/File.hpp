#pragma once

#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>

#include <algorithm>  // std::sort
#include <fstream>    // std::ifstream
#include <iostream>
#include <sstream>  // std::stringstream
#include <string>
#include <vector>

#include "Console.hpp"
#include "String.hpp"

using std::string;
using std::stringstream;
using std::vector;

namespace File {
  bool fileExists(const string &);
  string getBaseName(const string &);
  stringstream getBuffer(const string &);
  vector<string> getFilenamesInFolder(const string &, const string &);
  __unused bool isFile(const string &);
  bool isFolder(const string &);
  void saveBuffer(const string &, stringstream &);
  string selectFileInFolder(const string &, const string &);
  vector<string> selectFilesInFolder(const string &, const string &);
}