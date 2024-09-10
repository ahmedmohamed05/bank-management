#pragma once
#include "./bank-client.h"
#include "../main/screen.h"
#include <input.h>
#include <iostream>

class WithdrawScreen : protected Screen {
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
  static void showWithdraw() {

    Screen::_printScreenHeader("\t\tWithdraw Screen");

    std::string accountNumber = _readAccNumber();
    BankClient client = BankClient::find(accountNumber);

    _printClient(client);

    double amount = Input::readDouble("Enter the amount of withdraw: ");
    while (amount < 0) {
      amount = Input::readDouble("Please enter a positive number: ");
    }

    double currentBalance = client.getBalance();

    while (amount > currentBalance) {
      std::cout << "You can withdraw up to " << currentBalance << '\n';
      amount = Input::readDouble("Enter vaild amount to withdraw: ");
    }

    double newBalance = currentBalance - amount;

    std::cout << "Client new balance will be: " << newBalance << '\n';
    char wantToContinue =
        Input::readCharacter("Do you want to continue this operation[y, N]: ");

    if (tolower(wantToContinue) == 'y') {

      if (client.withdraw(amount)) {
        std::cout << "amount Widthdraow Successfully\n";
      } else {
        std::cout << "Error: Operation faild\n";
      }

    } else {
      std::cout << "Operation Cancled\n";
    }
  }
};
