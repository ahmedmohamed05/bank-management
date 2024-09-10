#include "../../public/global.h"
#include "date.h"
#include <iostream>
#include <util.h>

#pragma once

class Screen {
protected:
  static void _printScreenHeader(std::string headerName, int lineLength = 50) {
    std::string line = Util::repeat("-", lineLength);

    std::string name =
        currentUser.getUserName() == "" ? "Unknow" : currentUser.getFullName();

    Date today;

    std::cout << line << '\n';
    std::cout << headerName << '\n';
    std::cout << "logged in as: " << name;
    std::cout << ", At: " << Date::convertDateToString(today) << '\n';
    std::cout << line << '\n';
  }
  static void _printAccessDenied(std::string msg) {
    std::string line = Util::repeat("-", 50);

    std::cout << line << '\n';
    std::cout << msg << '\n';
    std::cout << line << '\n';
  }
};
