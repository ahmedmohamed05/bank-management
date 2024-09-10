#pragma once
#include "./bank-client.h"
#include "../main/screen.h"
#include <iomanip>
#include <iostream>
#include <string>

class TotalBalancesScreen : protected Screen {
public:
  static void showBalances() {

    std::vector<BankClient> vClients = BankClient::getClientsList();
    int size = vClients.size();
    Screen::_printScreenHeader("\t\t\tTotal Balances Screen\n\t\t\tYou have " +
                                   std::to_string(size) + " client(s)",
                               63);

    if (size == 0) {
      std::cout << "You don't have any clients yet...\n";
      return;
    }

    std::cout << "\t\t\tYou have " << size << " client(s)\n";
    std::cout
        << "---------------------------------------------------------------\n";
    std::cout << setw(25) << left << "Account Number";
    std::cout << " | " << setw(20) << left << "Full Name";
    std::cout << " | " << setw(15) << left << "Balance";

    std::cout << '\n';

    for (BankClient &client : vClients) {
      std::cout << setw(25) << left << client.getAccountNumber();
      std::cout << " | " << setw(20) << left << client.getFullName();
      std::cout << " | " << setw(15) << left << client.getBalance();
      std::cout << '\n';
    }

    long double totoalBalances = BankClient::getTotalBalances();

    std::cout
        << "---------------------------------------------------------------\n";
    std::cout << "\t\tTotal Balances: " << totoalBalances << '\n';
  }
};
