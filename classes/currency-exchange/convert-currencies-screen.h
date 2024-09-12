#pragma once
#include "../main/screen.h"
#include <iostream>

class ConvertCurrenciesScreen : protected Screen {
public:
  static void showConvertScreen() {
    Screen::_printScreenHeader("\t\tConvert Currencies Screen");
    std::cout << "Convert Currencies Screen Will Be Here\n";
  }
};