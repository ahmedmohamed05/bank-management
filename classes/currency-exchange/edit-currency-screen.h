#pragma once
#include "../../public/input.h"
#include "../main/screen.h"
#include "./currency.h"
#include <iostream>

class UpdateCurrencyRate : protected Screen {
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
  static void showUpdateScreen() {
    Screen::_printScreenHeader("\t\tUpdate Currency Rate");
    Currency currencyToChange = _read();

    _printCurrency(currencyToChange);

    char confirmation = tolower(Input::readCharacter(
        "Do you want to update this currency's rate[y, n]: "));
    if (confirmation != 'y') {
      std::cout << "Operation canceled\n";
      return;
    }

    float newRate = Input::readFloat("Enter new rate: ");

    while (newRate <= 0) {
      std::cout << "Rate must be grater than zero\n";
      newRate = Input::readFloat("Enter new rate: ");
    }

    currencyToChange.setRate(newRate);
    system("clear");
    std::cout << "Currency's rate updated successfully, Here are the new "
                 "information\n";
    _printCurrency(currencyToChange);
  }
};