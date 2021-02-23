#include "Console.hpp"

void Console::clearLine() {
  cin.clear();
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

bool Console::confirm(const string &message, char yes, char no) {
  while (true) {
    cout << "-> " << message << " (" << yes << "/" << no << "): ";

    char response;
    cin >> response;
    clearLine();
    if (response == yes) {
      return true;
    } else if (response == no) {
      return false;
    } else {
      cout << "Unknown character. ";
    }
  }
}

int Console::promptForInt(const string &message, int min, int max, int escapeValue) {
  while (true) {
    cout << "-> " << message << " (" << min << "-" << max << "): ";

    int value;
    cin >> value;
    clearLine();
    if (value == escapeValue) {
      return escapeValue;
    } else if (value >= min && value <= max) {
      return value;
    } else {
      cout << "Value is out of range. ";
    }
  }
}

string Console::promptForString(const string &message) {
  string result;
  cout << "-> " << message;
  getline(cin, result);
  return result;
}