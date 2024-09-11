#pragma once
#include "../../public/global.h"
#include "../../public/input.h"
#include "../user-classes/user.h"
#include "./main-screen.h"
#include "./screen.h"
#include <ctime>
#include <fstream>
#include <iostream>

class LoginScreen : protected Screen {
private:
  static std::string _getUserLog(User &user) {
    int permissions = user.getPermission();

    std::string log = "";
    log += user.getFullName() + " | ";
    log += Util::encrypt(user.getPassword(), permissions % 5) + " | ";
    log += std::to_string(permissions);

    return log;
  }

  static bool _writeLog() {

    fstream logFile("log.txt", ios::app);

    if (logFile.is_open()) {
      std::string log =
          Date::getTodayTimeAndDate() + " | " + _getUserLog(currentUser);

      logFile << log << '\n';

      logFile.close();
      return true;
    }
    return false;
  }

public:
  static void showLoginScreen() {
    Screen::_printScreenHeader("\t\tLogin Screen");

    bool loginFaild = false;

    for (int i = 1; i <= 3; i++) {
      std::string username = Input::readString("Enter username: ");
      std::string password = Input::readString("Enter password: ");

      currentUser = User::find(username, password);
      if (currentUser.isEmpty()) {
        std::cout << "Incorrect username or password, Try again\n";
      } else {
        i = 0;
        system("clear");

        if (!_writeLog()) {
          std::cout << "Error: this session not added to the log\n";
        };

        MainScreen::printMainScreen();
      }
    }

    std::cout << "System locked, Too many faild login  tries\n";
    exit(EXIT_FAILURE);
  }
};
