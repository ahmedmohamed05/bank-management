#pragma once
#include "./screen.h"
#include "cstring.h"
#include <iostream>
#include <vector>

class LoginRegisterScreen : protected Screen {
private:
  static void _printHeader() {
    std::cout << setw(25) << left << "Date/Time";
    std::cout << " | " << setw(20) << left << "Username";
    std::cout << " | " << setw(20) << left << "Password";
    std::cout << " | " << setw(10) << left << "Permissions";
  }

  struct login {
    std::string timeDate, username, password;
    int permission;
  };

  static login _convertLineToLogin(std::string line) {
    std::vector<std::string> log = Mstring::split(line, " | ");

    login l;
    l.timeDate = log.at(0);
    l.username = log.at(1);
    l.password = log.at(2);
    l.permission = stoi(log.at(3));

    return l;
  }

  static std::vector<login> _loadLogins() {
    std::fstream file("log.txt", ios::in);
    std::vector<login> logins;

    if (file.is_open()) {
      std::string line;
      while (getline(file, line)) {
        logins.push_back(_convertLineToLogin(line));
      }
      file.close();
    }

    return logins;
  }

  static void _printSingleLogin(login &l) {
    std::cout << setw(25) << left << l.timeDate;
    std::cout << " | " << setw(20) << left << l.username;
    std::cout << " | " << setw(20) << left << l.password;
    std::cout << " | " << setw(10) << left << l.permission;
    std::cout << '\n';
  }

public:
  static void showLoginRegistersScreen() {
    Screen::_printScreenHeader("Login Register Screen", 100);

    std::vector<login> log = _loadLogins();

    _printHeader();

    std::cout << '\n';
    std::cout << "--------------------------------------------------";
    std::cout << "--------------------------------------------------\n";

    for (login &l : log) {
      _printSingleLogin(l);
    }
  }
};