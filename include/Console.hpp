#include <iostream>
#include <limits>  // std::numeric_limits
#include <string>

using std::cin;
using std::cout;
using std::numeric_limits;
using std::streamsize;
using std::string;

namespace Console {

  void clearLine() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
  }

  bool confirm(const string &message, char yes = 'y', char no = 'n') {
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

  int promptForInt(const string &message, int min, int max) {
    while (true) {
      cout << "-> " << message << " (" << min << "-" << max << "): ";

      int value;
      cin >> value;
      clearLine();
      if (value >= min && value <= max) {
        return value;
      } else {
        cout << "Value is not in range. ";
      }
    }
  }

  string promptForString(const string &message) {
    string result;
    cout << "-> " << message;
    getline(cin, result);
    return result;
  }
}