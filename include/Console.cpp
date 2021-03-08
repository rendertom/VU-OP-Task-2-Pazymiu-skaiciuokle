#include "Console.hpp"

void Console::clearLine() {
  std::cin.clear();
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

bool Console::confirm(const string &message, char yes, char no) {
  while (true) {
    std::cout << "-> " << message << " (" << yes << "/" << no << "): ";

    char response;
    std::cin >> response;
    clearLine();
    if (response == yes) {
      return true;
    } else if (response == no) {
      return false;
    } else {
      std::cout << "Unknown character. ";
    }
  }
}

int Console::promptForInt(const string &message, int min, int max, int escapeValue) {
  while (true) {
    std::cout << "-> " << message << " (" << min << "-" << max << "): ";

    int value;
    std::cin >> value;
    clearLine();
    if (value == escapeValue) {
      return escapeValue;
    } else if (value >= min && value <= max) {
      return value;
    } else {
      std::cout << "Value is out of range. ";
    }
  }
}

vector<int> Console::promptForInts(const string &message, int min, int max) {
  std::cout << "-> " << message << " (" << min << "-" << max << "): ";
  string line;
  getline(std::cin, line);

  std::stringstream iss(line);
  int number;
  vector<int> numbers;

  while (iss >> number) {
    if (number >= min && number <= max) {
      numbers.push_back(number);
    } else {
      std::cout << number << " is out of range." << std::endl;
      return promptForInts(message, min, max);
    }
  }

  return numbers;
}

string Console::promptForString(const string &message) {
  string result;
  std::cout << "-> " << message;
  getline(std::cin, result);
  return result;
}