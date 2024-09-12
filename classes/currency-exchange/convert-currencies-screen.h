#pragma once
#include "../../public/input.h"
#include "../main/screen.h"
#include "./currency.h"
#include <iostream>

class ConvertCurrenciesScreen : protected Screen {

  static Currency _readCurrency(std::string msg) {
    std::string input =
        Input::readString("Enter code or country name to convert from: ");
    Currency currencyFound = Currency::find(input);

    while (!currencyFound.isValid()) {
      std::cout << "No Currency Fond, Try again\n";
      input = Input::readString("Enter code or country name to convert from: ");
      currencyFound = Currency::find(input);
    }
    return currencyFound;
  }

  static double _convertAmount(Currency &from, Currency &to, double amount) {
    double result = 0;

    double amountInUSD = amount * from.getRate();
    result = amountInUSD * to.getRate();

    return result;
  }

public:
  static void showConvertScreen() {
    Screen::_printScreenHeader("\t\tConvert Currencies Screen");
    char convertAgain = 'y';

    while (char(tolower(convertAgain)) == 'y') {
      system("clear");
      Currency from =
          _readCurrency("Enter code or country name to convert from: ");
      Currency to = _readCurrency("Enter code or country name to convert to: ");

      std::cout << "Convert from " << from.getCode() << " to " << to.getCode()
                << "\n";

      double amount = Input::readDouble("Enter the amount: ");

      while (amount <= 0) {
        std::cout << "Please enter a positive number\n";
        amount = Input::readDouble("Enter the amount: ");
      }

      double result = _convertAmount(from, to, amount);

      std::cout << amount << " " << from.getCode() << " = " << result << " "
                << to.getCode() << '\n';

      convertAgain =
          Input::readCharacter("Do you want to convert again [y, n]: ");
    }
  }
};