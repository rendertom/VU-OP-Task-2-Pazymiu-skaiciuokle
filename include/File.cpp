#include "File.hpp"

bool File::doesFileExist(const string &filePath) {
  ifstream file(filePath);
  return file.good();
}

stringstream File::getBuffer(const string &filePath) {
  ifstream file;
  file.open(filePath);

  if (!file) {
    throw std::runtime_error("Error: file \"" + filePath + "\" could not be opened");
  }

  stringstream buffer;
  buffer << file.rdbuf();
  file.close();

  return buffer;
}