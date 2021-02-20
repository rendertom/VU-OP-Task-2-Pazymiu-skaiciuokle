#include "File.hpp"

bool File::fileExists(const string &filePath) {
  struct stat info;
  return stat(filePath.c_str(), &info) == 0;
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

vector<string> File::getFilenamesInFolder(const string &folderPath, const string &extension) {
  DIR *directory = opendir(folderPath.c_str());
  struct dirent *entry;
  vector<string> fileNames;

  if (directory != NULL) {
    while ((entry = readdir(directory)) != NULL) {
      string fileName = entry->d_name;
      if (String::hasSuffix(fileName, extension)) {
        fileNames.push_back(fileName);
      }
    }
    closedir(directory);
  }

  return fileNames;
}

bool File::isFile(const string &filePath) {
  struct stat info;
  if (stat(filePath.c_str(), &info) == 0) {
    if (info.st_mode & S_IFREG) {
      return true;
    }
  }
  return false;
}

bool File::isFolder(const string &filePath) {
  struct stat info;
  if (stat(filePath.c_str(), &info) == 0) {
    if (info.st_mode & S_IFDIR) {
      return true;
    }
  }
  return false;
}

string File::selectFileInFolder(const string &folderPath, const string &extension) {
  if (!fileExists(folderPath)) {
    cout << "Folder \"" << folderPath << "\" does not exist." << endl;
  } else if (!isFolder(folderPath)) {
    cout << "\"" << folderPath << "\" is not a folder." << endl;
  } else {
    vector<string> fileNames = getFilenamesInFolder(folderPath, extension);
    int numFiles = fileNames.size();
    if (numFiles == 0) {
      cout << "Folder \"" << folderPath << "\" contains no files with extension \"" << extension << "\"." << endl;
    } else if (numFiles == 1) {
      return fileNames[0];
    } else {
      std::sort(fileNames.begin(), fileNames.end());

      cout << "Folder \"" << folderPath << "\" contains multiple files. Please select one:" << endl;
      for (int i = 0; i < numFiles; i++) {
        cout << i + 1 << ": " << fileNames[i] << endl;
      }

      int index = Console::promptForInt("Please select a file:", 1, numFiles);
      return fileNames[index - 1];
    }
  }

  return "";
}
