#pragma once
#include "./bank-client.h"
#include "../main/screen.h"
#include <cctype>
#include <input.h>
#include <iostream>
#include <numeric>

class DepositScreen : protected Screen {
private:
  static std::string _readAccNumber() {
    std::string accountNumber = Input::readString("Enter Account Number: ");

    while (!BankClient::isClientExists(accountNumber)) {
      std::cout << "Client Not Exists\n";
      accountNumber = Input::readString("Enter Account Number: ");
    }
    return accountNumber;
  }

  static void _printClient(BankClient &client) {
    std::cout << "Client Card.\n";
    std::cout << "First Name : " << client.getFirstName() << '\n';
    std::cout << "Last Name  : " << client.getLastName() << '\n';
    std::cout << "Full Name  : " << client.getFullName() << '\n';
    std::cout << "Email      : " << client.getEmail() << '\n';
    std::cout << "Phone      : " << client.getPhone() << '\n';
    std::cout << "Acc. Numbe : " << client.getAccountNumber() << '\n';
    std::cout << "Password   : " << client.getPinCode() << '\n';
    std::cout << "Balance    : " << client.getBalance() << '\n';
  }

public:
  static void showDeposit() {

    Screen::_printScreenHeader("\t\tDeposit Screen");

    std::string accountNumber = _readAccNumber();
    BankClient client = BankClient::find(accountNumber);

    _printClient(client);

    double deposit = Input::readDouble("Enter the amount of deposit: ");
    while (deposit < 0) {
      deposit = Input::readDouble("Please enter a positive number: ");
    }

    double currentBalance = client.getBalance();
    double newBalance = currentBalance + deposit;

    std::cout << "New client balance will be: " << newBalance << '\n';
    char wantToContinue =
        Input::readCharacter("Do you want to continue this operation[y, N]: ");

    if (tolower(wantToContinue) == 'y') {
      client.deposit(deposit);
      std::cout << "Deposit Added Successfully\n";
    } else {
      std::cout << "Operation Cancled\n";
    }
  }
};
