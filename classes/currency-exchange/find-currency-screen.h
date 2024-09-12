#pragma once
#include "../main/screen.h"
#include <iostream>

class FindCurrencyScreen : protected Screen {
public:
  static void showFindScreen() {
    Screen::_printScreenHeader("\t\t\tFind Currency Screen");
    std::cout << "Find Currency Screen Will Be Here\n";
  }
};