#pragma once
#include "../../public/cstring.h"
#include "../../public/util.h"
#include "../main/person.h"
#include <fstream>
#include <iostream>

const int showUsersPermission = 1 << 0;
const int addNewUserPermission = 1 << 1;
const int deleteUserPermission = 1 << 2;
const int updateUserPermission = 1 << 3;
const int findUserPermission = 1 << 4;
const int transactionsPermission = 1 << 5;
const int manageUsersPermission = 1 << 6;
const int ShowLogPermission = 1 << 7;
const int fullPermissions = -1;

class User : public Person {
private:
  int _permissions;
  std::string _userName, _password;
  bool _markedForDeletion = false;
  enum mode { empty, addNew, update };
  mode _mode;

  User(mode m, std::string firstName, std::string lastName, std::string email,
       std::string phone, std::string userName, std::string password,
       int permissions)
      : Person(firstName, lastName, email, phone) {
    _mode = mode::update;
    _userName = userName;
    _password = password;
    _permissions = permissions;
  }

  static User _convertRecordToObject(std::string record) {
    std::vector<std::string> vRecord = Mstring::split(record, " | ");

    std::string firstName = vRecord.at(0);
    std::string lastName = vRecord.at(1);
    std::string email = vRecord.at(2);
    std::string phone = vRecord.at(3);
    std::string userName = vRecord.at(4);
    int permissions = std::stoi(vRecord.at(6));
    std::string password = Util::decrypt(vRecord.at(5), permissions % 5);

    User user(mode::update, firstName, lastName, email, phone, userName,
              password, permissions);

    return user;
  }

  static std::string _convertObjectToRecord(User user) {
    std::string record = "";
    int permissions = user.getPermission();

    record += user.getFirstName() + " | ";
    record += user.getLastName() + " | ";
    record += user.getEmail() + " | ";
    record += user.getPhone() + " | ";
    record += user.getUserName() + " | ";
    record += Util::encrypt(user.getPassword(), permissions % 5) + " | ";
    record += std::to_string(permissions);

    return record;
  }

  User(mode m) : Person("", "", "", "") { _mode = m; }

  static User _createEmptyUser(mode m = mode::empty) { return User(m); }

  static std::vector<User> _loadDataFromFile() {
    std::fstream file("users.txt", ios::in);
    std::vector<User> users;

    if (file.is_open()) {
      std::string line;
      while (getline(file, line)) {
        users.push_back(_convertRecordToObject(line));
      }
      file.close();
    }

    return users;
  }

  void _addNew() {
    std::fstream file("users.txt", std::ios::app);

    if (file.is_open()) {
      file << _convertObjectToRecord(*this) << '\n';
    }
  }

  void _update() {
    std::vector<User> users = _loadDataFromFile();
    std::fstream file("users.txt", std::ios::out);

    if (file.is_open()) {
      for (User &user : users) {

        if (user.getUserName() == this->getUserName()) {
          // Skip the user if it's mark for deletion
          if (this->_markedForDeletion) {
            _mode = mode::empty;
            *this = _createEmptyUser();
            continue;
          }

          user = *this;
        }

        file << _convertObjectToRecord(user) << '\n';
      }
    }
  }

  void setMode(mode mode) { _mode = mode; }

public:
  User(std::string firstName, std::string lastName, std::string email,
       std::string phone, std::string userName, std::string password,
       int permissions)
      : Person(firstName, lastName, email, phone) {
    _mode = mode::addNew;
    _userName = userName;
    _password = password;
    _permissions = permissions;
  }

  bool isEmpty() { return _mode == mode::empty; };

  bool isMarkedForDeletion() { return _markedForDeletion; };

  void setUserName(std::string userName) { _userName = userName; }
  std::string getUserName() { return _userName; }

  void setPassword(std::string password) { _password = password; }
  std::string getPassword() { return _password; };

  void setPermissions(int permissions) { _permissions = permissions; }

  bool checkPermission(int permissionToCheck) {
    if (this->_permissions == -1)
      return true;

    return (this->_permissions & permissionToCheck) != 0;
  }

  mode getMode() { return _mode; }

  enum permissions {};
  int getPermission() { return _permissions; }

  static User find(std::string userName) {
    std::fstream file("users.txt", ios::in);

    if (file.is_open()) {
      std::string line;
      while (getline(file, line)) {
        User user = _convertRecordToObject(line);
        if (user.getUserName() == userName) {
          return user;
        }
      }
      file.close();
    }
    return _createEmptyUser();
  }

  static User find(std::string userName, std::string password) {
    std::fstream file("users.txt", std::ios::in);

    if (file.is_open()) {
      std::string line;
      while (getline(file, line)) {
        User user = _convertRecordToObject(line);
        if (user.getUserName() == userName && user.getPassword() == password) {
          return user;
        }
      }
      file.close();
    }
    return _createEmptyUser();
  }

  enum saveResults {
    faildEmptyObject,
    success,
    faildUserExists,
    faildUnknownError
  };

  saveResults save() {

    switch (_mode) {
    case mode::empty:
      return saveResults::faildEmptyObject;

    case mode::addNew:
      if (User::isUserExist(this->_userName)) {
        return saveResults::faildUserExists;
      }

      _addNew();
      _mode = mode::update;

      return saveResults::success;

    case mode::update:
      _update();
      return saveResults::success;
    }

    return saveResults::faildUnknownError;
  }

  static bool isUserExist(std::string userName) {
    return !find(userName).isEmpty();
  }

  // return false if the user haven't added yet so can't delete it
  bool remove() {
    // Can't remove user haven't added yet
    if (_mode == mode::addNew) {
      return false;
    }

    _markedForDeletion = true;
    _update();
    return true;
  }

  static std::vector<User> getUsers() { return _loadDataFromFile(); }

  void markForDeletion() { _markedForDeletion = true; }

  static User newUser(std::string userName) {
    User user = _createEmptyUser(mode::addNew);
    user.setUserName(userName);
    return user;
  }
};
