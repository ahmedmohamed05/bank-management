#pragma once

#include <iostream>

class Person {
private:
  std::string _firstName, _lastName, _email, _phone;

public:
  Person(std::string firstName, std::string lastName, std::string email,
         std::string phone) {
    _firstName = firstName;
    _lastName = lastName;
    _email = email;
    _phone = phone;
  }

  void setFirstName(std::string newName) { _firstName = newName; }
  std::string getFirstName() { return _firstName; }

  void setLastName(std::string newName) { _lastName = newName; }
  std::string getLastName() { return _lastName; }

  void setEmail(std::string newEmail) { _email = newEmail; }
  std::string getEmail() { return _email; }

  void setPhone(std::string newPhone) { _phone = newPhone; }
  std::string getPhone() { return _phone; }

  std::string getFullName() { return _firstName + " " + _lastName; }
};
