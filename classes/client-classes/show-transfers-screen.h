#pragma once
#include "../../public/cstring.h"
#include "../main/screen.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>

class TransfersScreen : protected Screen {
private:
  static void _printHeader(int size) {
    if (size < 0) {
      std::cout << "No transfers yet\n";
      return;
    }
    std::cout << setw(13) << left << "We took from";
    std::cout << " | " << setw(11) << left << "He/She had";
    std::cout << " | " << setw(18) << left << "This amount taken";
    std::cout << " | " << setw(15) << left << "Now he/she has";
    std::cout << " | " << setw(18) << left << "And added them to";
    std::cout << " | " << setw(11) << left << "He/She had";
    std::cout << " | " << setw(15) << left << "Now he/she has";
    std::cout << " | " << setw(20) << left << "That was at";
    std::cout << " | " << setw(12) << left << "And done by";
    std::cout << '\n';
  }

  struct _sTransfer {
    std::string fromAccNumber, toAccNumber, doneBy, timeDate;
    double oldFromBalance, newFromBalance, oldToBalance, newToBalance, amount;
  };

  static void _printTransfer(_sTransfer &transfer) {
    std::cout << setw(13) << left << transfer.fromAccNumber;
    std::cout << " | " << setw(11) << left << transfer.oldFromBalance;
    std::cout << " | " << setw(18) << left << transfer.amount;
    std::cout << " | " << setw(15) << left << transfer.newFromBalance;
    std::cout << " | " << setw(18) << left << transfer.toAccNumber;
    std::cout << " | " << setw(11) << left << transfer.oldToBalance;
    std::cout << " | " << setw(15) << left << transfer.newToBalance;
    std::cout << " | " << setw(20) << left << transfer.timeDate;
    std::cout << " | " << setw(12) << left << transfer.doneBy;
    std::cout << '\n';
  }

  // from | oldFromBalance | amount | newFromBalance | to | oldToBalance |
  // newToBalance | at | doneBy
  static _sTransfer _convertLineToSTransfer(std::string line,
                                            std::string separator = " | ") {
    _sTransfer transfer;
    std::vector<std::string> vTransfer = Mstring::split(line, separator);

    transfer.fromAccNumber = vTransfer.at(0);
    transfer.oldFromBalance = stod(vTransfer.at(1));
    transfer.amount = stod(vTransfer.at(2));
    transfer.newFromBalance = stod(vTransfer.at(3));
    transfer.toAccNumber = vTransfer.at(4);
    transfer.oldToBalance = stod(vTransfer.at(5));
    transfer.newToBalance = stod(vTransfer.at(6));
    transfer.timeDate = vTransfer.at(7);
    transfer.doneBy = vTransfer.at(8);

    return transfer;
  }

  static std::vector<_sTransfer> _loadTransfers() {
    std::fstream file("transfers.txt", ios::in);
    std::vector<_sTransfer> transfers;
    if (file.is_open()) {
      std::string line;

      while (getline(file, line)) {
        transfers.push_back(_convertLineToSTransfer(line));
      }

      file.close();
    }

    return transfers;
  }

public:
  static void showTransfersScreen() {
    Screen::_printScreenHeader("\t\t\t\t\t\t\t\tTransfers Log Screen", 150);

    std::vector<_sTransfer> transfers = _loadTransfers();

    int size = transfers.size();

    _printHeader(size);

    for (_sTransfer &transfer : transfers) {
      _printTransfer(transfer);
    }

    if (size > 0) {
      std::cout << "\t\t\t\t\t\t\t"
                << "There are " << size << " transfer(s) in the system\n";
    }
  }
};
