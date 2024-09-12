#pragma once
#include "../../public/input.h"
#include "../main/screen.h"
#include "./currency.h"
#include <iostream>

class FindCurrencyScreen : protected Screen {
  static void _printCurrency(Currency &c) {
    if (!c.isValid()) {
      std::cout << "Not a valid Currency\n";
      return;
    }
    std::cout << "Country: " << c.getCountry() << '\n';
    std::cout << "Code   : " << c.getCode() << '\n';
    std::cout << "Name   : " << c.getCurrencyName() << '\n';
    std::cout << "Rate   : " << c.getRate() << '\n';
    std::cout << "-------------------------------------\n";
  }

  static Currency _read() {
    std::string input = Input::readString("Enter currency's country or code: ");

    Currency currencyFound = Currency::find(input);

    while (!currencyFound.isValid()) {
      std::cout << "No Currency Fond, Try again\n";
      input = Input::readString("Enter currency's country or code: ");
      currencyFound = Currency::find(input);
    }
    return currencyFound;
  }

public:
  static void showFindScreen() {
    Screen::_printScreenHeader("\t\t\tFind Currency Screen");

    Currency c = _read();

    _printCurrency(c);
  }
};