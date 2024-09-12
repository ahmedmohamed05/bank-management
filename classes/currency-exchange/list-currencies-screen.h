#pragma once
#include "../main/screen.h"
#include "./currency.h"
#include <iostream>

class ListCurrencies : protected Screen {
private:
  static void _printHeader(int size) {
    std::cout << "\tThere is " << size << "currencies in the list\n";
    std::cout << "-------------------------------------------------------------"
                 "---------------------------\n";

    std::cout << setw(25) << left << "Country";
    std::cout << " | " << setw(5) << left << "Code";
    std::cout << " | " << setw(30) << left << "Currency name";
    std::cout << " | " << setw(15) << left << "Rate for 1$";

    std::cout << '\n';
    std::cout << "-------------------------------------------------------------"
                 "---------------------------\n";
  }

  static void _printCurrency(Currency &c) {
    std::cout << setw(25) << left << c.getCountry();
    std::cout << " | " << setw(5) << left << c.getCode();
    std::cout << " | " << setw(30) << left << c.getCurrencyName();
    std::cout << " | " << setw(15) << left << c.getRate();

    std::cout << '\n';
  }

public:
  static void showListScreen() {
    Screen::_printScreenHeader("\t\tList Currencies Screen");
    std::vector<Currency> currencies = Currency::getCurrencies();

    _printHeader(currencies.size());

    for (Currency &currency : currencies) {
      _printCurrency(currency);
    }
    std::cout << '\n';
  }
};