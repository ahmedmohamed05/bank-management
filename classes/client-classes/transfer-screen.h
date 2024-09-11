#pragma once
#include "../main/screen.h"
#include "bank-client.h"
#include "input.h"
#include <iostream>

class TransferScreen : protected Screen {
private:
  static BankClient _findClient(std::string msg) {
    std::string accNumber = Input::readString(msg);

    BankClient clientFound = BankClient::find(accNumber);

    while (clientFound.isEmpty()) {
      std::cout << "Client with this account number not exist\n";
      accNumber = Input::readString(msg);
      clientFound = BankClient::find(accNumber);
    }

    return clientFound;
  }

  static void _simplePrint(BankClient &client) {
    std::cout << "-----------------------------------------\n";
    std::cout << "Acc. number: " << client.getAccountNumber() << '\n';
    std::cout << "Full Name  : " << client.getFullName() << '\n';
    std::cout << "Balance    : " << client.getBalance() << '\n';
    std::cout << "-----------------------------------------\n";
  }

public:
  static void showTransferScreen() {
    BankClient transferFromClient =
        _findClient("Enter account number for client to transfer from: ");
    _simplePrint(transferFromClient);

    BankClient transferToClient =
        _findClient("Enter account number for client to transfer to: ");
    _simplePrint(transferToClient);

    double amount = Input::readDouble("Enter transfer amount: ");

    while (amount > transferFromClient.getBalance()) {
      std::cout << "Amount Entered out of balance range\n";
      std::cout << "You can transfer up to " << transferFromClient.getBalance()
                << '\n';
      amount = Input::readDouble("Enter transfer amount: ");
    }

    char confirmation =
        Input::readCharacter("Do you want to apply the transfer [y, n]: ");

    if (confirmation != 'y') {
      std::cout << "Transfer canceled\n";
      return;
    }

    system("clear");

    if (transferFromClient.transfer(amount, transferFromClient)) {
      std::cout << "Transfer down successfully\n";
    } else {
      std::cout << "Error something went wrong\n";
      return;
    }

    _simplePrint(transferFromClient);
    _simplePrint(transferToClient);
  }
};