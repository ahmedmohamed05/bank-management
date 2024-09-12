#pragma once
#include "../../public/input.h"
#include "../main/screen.h"
#include <iostream>

// Screens
#include "./convert-currencies-screen.h"
#include "./edit-currency-screen.h"
#include "./find-currency-screen.h"
#include "./list-currencies-screen.h"

class CurrencyMainScreen : protected Screen {

private:
  enum _options { list, find, updateRate, convert, mainMenu };

  static short _readUserOption() {
    short option;
    option = Input::readShortInRange("What do you want to do: ", 1, 5);
    return option;
  }

  static void _performAction(_options option) {
    system("clear");
    switch (option) {
    case _options::list:
      ListCurrencies::showListScreen();
      break;
    case _options::find:
      FindCurrencyScreen::showFindScreen();
      break;
    case _options::updateRate:
      UpdateCurrencyRate::showUpdateScreen();
      break;
    case _options::convert:
      ConvertCurrenciesScreen::showConvertScreen();
      break;
    case _options::mainMenu:
      break;
    }
    showMainScreen();
  }

public:
  static void showMainScreen() {
    Screen::_printScreenHeader("\tCurrency Exchange Main Screen");

    std::cout << "[1]: List Currencies.\n";
    std::cout << "[2]: Find Currency.\n";
    std::cout << "[3]: Update Currency Rate.\n";
    std::cout << "[4]: Currency Converter.\n";
    std::cout << "[5]: Main Menu.\n";

    _performAction(_options(_readUserOption() - 1));
  }
};