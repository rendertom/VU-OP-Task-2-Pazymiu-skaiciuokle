#include "File.hpp"

void printFilenames(vector<string> &fileNames) {
  for (int i = 0, il = fileNames.size(); i < il; i++) {
    std::cout << i + 1 << ": " << fileNames[i] << std::endl;
  }
}

bool File::fileExists(const string &filePath) {
  struct stat info{};
  return stat(filePath.c_str(), &info) == 0;
}

string File::getBaseName(const string &fileName) {
  size_t lastIndex = fileName.find_last_of('.');
  string baseName = fileName.substr(0, lastIndex);
  return baseName;
}

stringstream File::getBuffer(const string &filePath) {
  std::ifstream file;
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

  if (directory != nullptr) {
    while ((entry = readdir(directory)) != nullptr) {
      string fileName = entry->d_name;
      if (String::hasSuffix(fileName, extension)) {
        fileNames.push_back(fileName);
      }
    }
    closedir(directory);
  }

  return fileNames;
}

__unused bool File::isFile(const string &filePath) {
  struct stat info{};
  if (stat(filePath.c_str(), &info) == 0) {
    if (info.st_mode & S_IFREG) {
      return true;
    }
  }
  return false;
}

bool File::isFolder(const string &filePath) {
  struct stat info{};
  if (stat(filePath.c_str(), &info) == 0) {
    if (info.st_mode & S_IFDIR) {
      return true;
    }
  }
  return false;
}

void File::saveBuffer(const string &filePath, stringstream &buffer) {
  std::ofstream file;
  file.open(filePath);

  if (!file) {
    throw std::runtime_error("Error: file \"" + filePath + "\" could not be opened");
  }

  file << buffer.str();
  file.close();
}

string File::selectFileInFolder(const string &folderPath, const string &extension) {
  string fileName;
  if (!fileExists(folderPath)) {
    std::cout << "Folder \"" << folderPath << "\" does not exist." << std::endl;
  } else if (!isFolder(folderPath)) {
    std::cout << "\"" << folderPath << "\" is not a folder." << std::endl;
  } else {
    vector<string> fileNames = getFilenamesInFolder(folderPath, extension);
    int numFiles = fileNames.size();
    if (numFiles == 0) {
      std::cout << "Folder \"" << folderPath << "\" contains no files with extension \"" << extension << "\"." << std::endl;
    } else if (numFiles == 1) {
      fileName = fileNames[0];
    } else {
      std::sort(fileNames.begin(), fileNames.end());

      std::cout << "Folder \"" << folderPath << "\" contains multiple files. Please select one:" << std::endl;
      printFilenames(fileNames);

      int index = Console::promptForInt("Please select a file:", 1, numFiles);
      fileName = fileNames[index - 1];
    }
  }

  return fileName;
}

vector<string> File::selectFilesInFolder(const string &folderPath, const string &extension) {
  vector<string> selectedFileNames;

  if (!fileExists(folderPath)) {
    std::cout << "Folder \"" << folderPath << "\" does not exist." << std::endl;
  } else if (!isFolder(folderPath)) {
    std::cout << "\"" << folderPath << "\" is not a folder." << std::endl;
  } else {
    vector<string> fileNames = getFilenamesInFolder(folderPath, extension);
    int numFiles = fileNames.size();
    if (numFiles == 0) {
      std::cout << "Folder \"" << folderPath << "\" contains no files with extension \"" << extension << "\"." << std::endl;
    } else if (numFiles == 1) {
      selectedFileNames.push_back(fileNames[0]);
    } else {
      std::sort(fileNames.begin(), fileNames.end());
      std::cout << "Folder \"" << folderPath << "\" contains multiple files. Please select some:" << std::endl;

      printFilenames(fileNames);
      vector<int> numbers = Console::promptForInts("Please select some files:", 1, fileNames.size());
      for (int i = 0, il = numbers.size(); i < il; i++) {
        selectedFileNames.push_back(fileNames[numbers[i] - 1]);
      }
    }
  }

  return selectedFileNames;
}