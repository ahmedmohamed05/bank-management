#pragma once
#include "../../public/input.h"
#include "../main/screen.h"
#include "./bank-client.h"
#include <iostream>

class DeleteClientScreen : protected Screen {
private:
  static void _printClient(BankClient &client) {
    std::cout << "Client Card.\n";
    std::cout << "First Name : " << client.getFirstName() << '\n';
    std::cout << "Last Name  : " << client.getLastName() << '\n';
    std::cout << "Full Name  : " << client.getFullName() << '\n';
    std::cout << "Email      : " << client.getEmail() << '\n';
    std::cout << "Phone      : " << client.getPhone() << '\n';
    std::cout << "Acc. Number : " << client.getAccountNumber() << '\n';
    std::cout << "Password   : " << client.getPinCode() << '\n';
    std::cout << "Balance    : " << client.getBalance() << '\n';
  }

public:
  static void deleteClient() {
    _printScreenHeader("Delete Client Sccreen");
    std::string accountNumber = Input::readString("Enter Account Number: ");

    while (!BankClient::isClientExists(accountNumber)) {
      std::cout << "Client Not Exists\n";
      accountNumber = Input::readString("Enter Account Number: ");
    }

    BankClient clientFound = BankClient::find(accountNumber);
    _printClient(clientFound);

    char deletionConfirmation =
        Input::readCharacter("Do you want to delete this clien [y, n]: ",
                             "Enter signle character\n");
    if (deletionConfirmation == 'y') {
      if (clientFound.del()) {
        std::cout << "Client deleted successfully\n";
      } else {
        std::cout << "Error client was not deleted successfully\n";
      }
    }
  }
};
