#include "File.hpp"

bool File::doesFileExist(const string &filePath) {
  ifstream file(filePath);
  return file.good();
}

stringstream File::getBuffer(const string &filePath) {
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