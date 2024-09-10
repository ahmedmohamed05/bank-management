#pragma once
#include "./bank-client.h"
#include "../main/screen.h"
#include <iomanip>
#include <iostream>

class ClientsScreen : protected Screen {
private:
  static void _printHeader(int size) {
    std::string msg = "\t\t\t\t\t\t\tClient List Screen\n\t\t\t\t\t\t\t";

    if (size == 0) {
      msg += "You don't have any clients yet...";
      return;
    } else {
      msg += std::to_string(size) + " Client(s)";
    }

    Screen::_printScreenHeader(msg, 124);

    std::cout << setw(25) << left << "Account Number";
    std::cout << " | " << setw(20) << left << "Full Name";
    std::cout << " | " << setw(25) << left << "Email";
    std::cout << " | " << setw(15) << left << "Phone";
    std::cout << " | " << setw(15) << left << "Pin Code";
    std::cout << " | " << setw(15) << left << "Balance";
  }

  static void _printClientRecordInTable(BankClient &client) {
    std::cout << setw(25) << left << client.getAccountNumber();
    std::cout << " | " << setw(20) << left << client.getFullName();
    std::cout << " | " << setw(25) << left << client.getEmail();
    std::cout << " | " << setw(15) << left << client.getPhone();
    std::cout << " | " << setw(15) << left << client.getPinCode();
    std::cout << " | " << setw(15) << left << client.getBalance();
    std::cout << '\n';
  }

public:
  static void showAllClients() {
    std::vector<BankClient> vClients = BankClient::getClientsList();
    _printHeader(vClients.size());

    std::cout << '\n';
    std::cout << "--------------------------------------------------";
    std::cout << "--------------------------------------------------";
    std::cout << "------------------------\n";

    for (BankClient &client : vClients) {
      _printClientRecordInTable(client);
    }

    std::cout << '\n';
  }
};
