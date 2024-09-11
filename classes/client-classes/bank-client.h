#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "../main/person.h"
#include "cstring.h"

class BankClient : public Person {
private:
  std::string _accountNumber;
  std::string _pinCode;
  double _balance;
  bool _markForDelete = false;

  enum mode { empty, updated, addNew };
  mode _mode;

  static BankClient convertStringToClient(std::string record) {
    std::vector<std::string> vRecord = Mstring::split(record, " | ");

    std::string firstName = vRecord.at(0);
    std::string lastName = vRecord.at(1);
    std::string email = vRecord.at(2);
    std::string phone = vRecord.at(3);
    std::string accountNumber = vRecord.at(4);
    std::string pinCode = vRecord.at(5);
    double balance = std::stod(vRecord.at(6));

    return BankClient(mode::updated, firstName, lastName, email, phone,
                      accountNumber, pinCode, balance);
  }

  static std::string _convertClientToString(BankClient client) {
    std::string record = "";
    std::string separator = " | ";

    record += client.getFirstName() + separator;
    record += client.getLastName() + separator;
    record += client.getEmail() + separator;
    record += client.getPhone() + separator;
    record += client.getAccountNumber() + separator;
    record += client.getPinCode() + separator;
    record += std::to_string(client.getBalance());

    return record;
  }

  static BankClient _createEmptyClient() {
    BankClient client(mode::empty, "", "", "", "", "", "", 0);
    return client;
  }

  static std::vector<BankClient> _loadClientFromFile() {
    std::vector<BankClient> vClients;

    fstream clientsFile("clients.txt", std::ios::in);

    if (clientsFile.is_open()) {

      std::string clientRecord;

      while (getline(clientsFile, clientRecord)) {
        vClients.push_back(convertStringToClient(clientRecord));
      }

      clientsFile.close();
    }

    return vClients;
  }

  static void _saveClientsToFile(const std::vector<BankClient> &vClients) {
    fstream clientsFile("clients.txt", std::ios::out);

    if (clientsFile.is_open()) {
      for (const BankClient &client : vClients) {
        std::string record = _convertClientToString(client);
        if (!client._markForDelete) {
          clientsFile << record << '\n';
        }
      }
      clientsFile.close();
    }
  }

  void _update() {
    std::vector<BankClient> vClients = _loadClientFromFile();

    fstream clientsFile("clients.txt", std::ios::out);

    if (clientsFile.is_open()) {
      for (BankClient &client : vClients) {
        if (this->getAccountNumber() == client.getAccountNumber()) {
          client = *this;
          break;
        }
      }
      clientsFile.close();
    }

    _saveClientsToFile(vClients);
  }

  void _addNewRecordToFile(std::string record) {
    fstream file("clients.txt", std::ios::app);

    if (file.is_open()) {
      file << record << '\n';
      file.close();
    }
  }

  void _addNewClient() {
    std::string record = _convertClientToString(*this);
    _addNewRecordToFile(record);
  }

public:
  BankClient(mode mode, std::string firstName, std::string lastName,
             std::string email, std::string phone, std::string accountNumber,
             std::string pinCode, double balance)
      : Person(firstName, lastName, email, phone) {
    _mode = mode;
    _accountNumber = accountNumber;
    _pinCode = pinCode;
    _balance = balance;
  }

  std::string getAccountNumber() { return _accountNumber; }

  void setPinCode(std::string newPin) { _pinCode = newPin; }
  std::string getPinCode() { return _pinCode; }

  void setBalance(double newBalance) { _balance = newBalance; }
  double getBalance() { return _balance; }

  mode getMode() { return _mode; }
  bool isEmpty() { return _mode == mode::empty; }

  static BankClient find(std::string accountNumber) {
    std::fstream file("clients.txt", std::ios::in);

    if (file.is_open()) {
      std::string line;

      while (getline(file, line)) {
        BankClient client = convertStringToClient(line);

        if (client.getAccountNumber() == accountNumber) {
          file.close();
          return client;
        }
      }
      file.close();
    }

    return _createEmptyClient();
  }

  static BankClient find(std::string accountNumber, std::string pinCode) {
    std::fstream file("clients.txt", std::ios::in);

    if (file.is_open()) {
      std::string line;

      while (getline(file, line)) {
        BankClient client = convertStringToClient(line);

        if (client.getAccountNumber() == accountNumber &&
            client.getPinCode() == pinCode) {
          file.close();
          return client;
        }
      }
      file.close();
    }

    return _createEmptyClient();
  }

  static bool isClientExists(std::string accountNumber) {
    return !find(accountNumber).isEmpty();
  }

  enum saveResult { faildClientEmpty, faildClientExists, succeed };

  saveResult save() {
    switch (_mode) {
    case mode::empty:
      return saveResult::faildClientEmpty;
    case mode::updated:
      _update();
      return saveResult::succeed;
    case mode::addNew:
      if (isClientExists(this->getAccountNumber())) {
        return saveResult::faildClientEmpty;
      }
      _addNewClient();
      this->_mode = mode::updated;
      return saveResult::succeed;
    }

    return saveResult::faildClientEmpty;
  }

  static BankClient getNewObj(std::string accNum) {
    BankClient client(mode::addNew, "", "", "", "", accNum, "", 0);
    return client;
  }

  bool del() {
    std::vector<BankClient> vClients = _loadClientFromFile();

    for (BankClient &client : vClients) {
      if (client.getAccountNumber() == this->getAccountNumber()) {
        this->_markForDelete = true;
        client = *this;
        break;
      }
    }

    _saveClientsToFile(vClients);
    *this = _createEmptyClient();
    return true;
  }

  void deposit(double amount) {
    this->_balance += amount;
    save();
  }

  // Returns false if withdraw operation faild
  bool withdraw(double amount) {
    if (amount > this->_balance) {
      return false;
    }

    this->_balance -= amount;
    save();
    return true;
  }

  static std::vector<BankClient> getClientsList() {
    return _loadClientFromFile();
  }

  static double getTotalBalances() {
    double balances = 0;

    std::vector<BankClient> vClients = _loadClientFromFile();

    for (BankClient &client : vClients) {
      balances += client.getBalance();
    }

    return balances;
  }

  bool transfer(double amount, BankClient &destinationClient) {
    if (amount > this->_balance) {
      return false;
    }
    this->withdraw(amount);
    destinationClient.deposit(amount);
    return save() == saveResult::succeed;
  }
};
