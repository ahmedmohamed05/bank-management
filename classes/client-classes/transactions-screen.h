#pragma once
#include "../main/screen.h"
#include "./bank-client.h"
#include <input.h>
#include <istream>
// Screens
#include "./deposit-screen.h"
#include "./total-balances-screen.h"
#include "./transfer-screen.h"
#include "./withdraw-screen.h"

class Transactions : protected Screen {
private:
  enum transactionsOptions {
    showDeposit,
    showWithdraw,
    totalBalances,
    transfer,
    mainMenu
  };

  static short _readTransactionOption() {
    short option = Input::readShortInRange("What do you want to do: ", 1, 5);
    return option;
  }

  static void _showDepositScreen() { DepositScreen::showDeposit(); }

  static void _showWithDraw() { WithdrawScreen::showWithdraw(); }

  static void _showTotalBalances() { TotalBalancesScreen::showBalances(); }

  static void _showTransferScreen() { TransferScreen::showTransferScreen(); }

  static void _performTransactionOperation(transactionsOptions option) {
    system("clear");
    switch (option) {
    case transactionsOptions::showDeposit:
      _showDepositScreen();
      break;
    case transactionsOptions::showWithdraw:
      _showWithDraw();
      break;
    case transactionsOptions::totalBalances:
      _showTotalBalances();
      break;
    case transactionsOptions::transfer:
      _showTransferScreen();
      break;
    case transactionsOptions::mainMenu:
      return;
      break;
    }
    showTransactionsScreen();
  }

public:
  static void showTransactionsScreen() {
    Screen::_printScreenHeader("Transactions Screen");
    std::cout << "[1] Deposit.\n";
    std::cout << "[2] Withdraw.\n";
    std::cout << "[3] Total Balances.\n";
    std::cout << "[4] Transfer.\n";
    std::cout << "[5] Main Menu.\n";
    std::cout << "===========================================\n";
    _performTransactionOperation(
        transactionsOptions(_readTransactionOption() - 1));
  }
};
