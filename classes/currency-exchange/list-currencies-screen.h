#pragma once
#include "../main/screen.h"
#include <iostream>

class ListCurrencies : protected Screen {
public:
  static void showListScreen() {
    Screen::_printScreenHeader("\t\tList Currencies Screen");
    std::cout << "Currencies List Screen Will Be Here\n";
  }
};