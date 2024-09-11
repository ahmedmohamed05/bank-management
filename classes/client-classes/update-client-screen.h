#pragma once
#include "../../public/input.h"
#include "../main/screen.h"
#include "./bank-client.h"
#include <iostream>

class UpdateClientScreen : protected Screen {
private:
  static void _readClientInfo(BankClient &client) {
    client.setFirstName(Input::readString("Enter First Name: "));
    client.setLastName(Input::readString("Enter Last Name: "));
    client.setEmail(Input::readString("Enter Email: "));
    client.setPhone(Input::readString("Enter Phone: "));
    client.setPinCode(Input::readString("Enter PinCode: "));
    client.setBalance(Input::readDouble("Enter Balance: "));
  }
  static void _printClient(BankClient &client) {
    std::cout << "Client Card.\n";
    std::cout << "First Name  : " << client.getFirstName() << '\n';
    std::cout << "Last Name   : " << client.getLastName() << '\n';
    std::cout << "Full Name   : " << client.getFullName() << '\n';
    std::cout << "Email       : " << client.getEmail() << '\n';
    std::cout << "Phone       : " << client.getPhone() << '\n';
    std::cout << "Acc. Number : " << client.getAccountNumber() << '\n';
    std::cout << "Password    : " << client.getPinCode() << '\n';
    std::cout << "Balance     : " << client.getBalance() << '\n';
  }

public:
  static void updateClient() {
    Screen::_printScreenHeader("Update Client", 40);

    std::string accountNumber = Input::readString("Enter Account Number: ");

    while (!BankClient::isClientExists(accountNumber)) {
      std::cout << "Client Not Exists\n";
      accountNumber = Input::readString("Enter Account Number: ");
    }

    BankClient clientFound = BankClient::find(accountNumber);
    _printClient(clientFound);

    char edit =
        Input::readCharacter("Do you want to update this client [y, n]: ",
                             "Enter single character\n");
    if (edit == 'y') {
      _readClientInfo(clientFound);
      BankClient::saveResult saveResult = clientFound.save();

      switch (saveResult) {
      case BankClient::saveResult::faildClientEmpty:
        std::cout << "Faild To Save client, Because It's Empty\n";
        break;
      case BankClient::saveResult::succeed:
        std::cout << "Client Updated\n";
        _printClient(clientFound);
        break;
      }
    } else {
      std::cout << "Operation canceled\n";
    }
  }
};
