#pragma once
#include "../main/screen.h"
#include <iostream>

class UpdateCurrencyRate : protected Screen {
public:
  static void showUpdateScreen() {
    Screen::_printScreenHeader("\t\tUpdate Currency Rate");
    std::cout << "Update Currency Screen Will Be Here\n";
  }
};