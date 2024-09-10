#pragma once
#include "../main/screen.h"
#include "./bank-client.h"
#include <cstdlib>
#include <input.h>
#include <iostream>

class NewClientScreen : protected Screen {
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
  static void addNewClient() {
    Screen::_printScreenHeader("Add New Client", 40);

    std::string accountNumber = Input::readString("Enter Account Number: ");

    while (BankClient::isClientExists(accountNumber)) {
      std::cout << "Account number already used, choose another one\n";
      accountNumber = Input::readString("Enter Account Number: ");
    }

    BankClient client = BankClient::getNewObj(accountNumber);

    _readClientInfo(client);

    BankClient::saveResult saveResult = client.save();

    switch (saveResult) {
    case BankClient::saveResult::faildClientEmpty:
      std::cout << "Faild To Save Client, Because It's Empty\n";
      break;
    case BankClient::saveResult::succeed:
      system("clear");
      std::cout << "Client Added Successfully\n";
      _printClient(client);
      break;
    }
  }
};
