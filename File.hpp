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

bool doesFileExist(const string &filePath) {
  ifstream file(filePath);
  return file.good();
}

stringstream getBuffer(const string &filePath) {
  ifstream file;
  file.open(filePath);

  if (!file) {
    cout << "Error: file could not be opened" << endl;
    exit(1);
  }

  stringstream buffer;
  buffer << file.rdbuf();
  file.close();

  return buffer;
}

}  // namespace File