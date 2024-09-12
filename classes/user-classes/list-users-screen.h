#pragma once
#include "../main/screen.h"
#include "./user.h"
#include <vector>

class ListUsersScreen : protected Screen {

private:
  static void _printHeader(int size) {
    std::string msg = "\t\t\t\t\t\t\tUsers List Screen\n\t\t\t\t\t\t\t";
    msg += std::to_string(size) + " Users(s)";

    Screen::_printScreenHeader(msg, 124);

    // Ahmed | Mohamed | mom@g.c | 07708972714 | am | AhmedMohamed | -1

    std::cout << setw(25) << left << "Full Name";
    std::cout << " | " << setw(25) << left << "Email";
    std::cout << " | " << setw(15) << left << "Phone";
    std::cout << " | " << setw(10) << left << "Username";
    std::cout << " | " << setw(20) << left << "Password";
    std::cout << " | " << setw(10) << left << "Permissions";
  }

  static void _printUserRecord(User &user) {
    std::cout << setw(25) << left << user.getFullName();
    std::cout << " | " << setw(25) << left << user.getEmail();
    std::cout << " | " << setw(15) << left << user.getPhone();
    std::cout << " | " << setw(10) << left << user.getUserName();
    std::cout << " | " << setw(20) << left << user.getPassword();
    std::cout << " | " << setw(10) << left << user.getPermission();
    std::cout << '\n';
  }

public:
  static void showUsers() {
    std::vector<User> users = User::getUsers();

    _printHeader(users.size());

    std::cout << '\n';
    std::cout << "--------------------------------------------------";
    std::cout << "--------------------------------------------------";
    std::cout << "------------------------\n";

    for (User &user : users) {
      _printUserRecord(user);
    }
    std::cout << '\n';
  }
};
