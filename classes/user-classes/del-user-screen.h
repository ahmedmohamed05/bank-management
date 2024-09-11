#pragma once
#include "../../public/input.h"
#include "../main/screen.h"
#include "./user.h"
#include <iostream>

class DelUserScreen : protected Screen {
private:
  static void _printUser(User &user) {

    if (user.isEmpty()) {
      std::cout << "Empty User, !!!\n";
      return;
    }

    std::cout << "Full Name: " << user.getFullName() << '\n';
    std::cout << "Email: " << user.getEmail() << '\n';
    std::cout << "Phone: " << user.getPhone() << '\n';
    std::cout << "User Name: " << user.getUserName() << '\n';
    std::cout << "Password: " << user.getPassword() << '\n';
    std::cout << "Permissions: " << user.getPermission() << '\n';
  }

public:
  static void showDelUserScreen() {
    Screen::_printScreenHeader("\t\tDelete User Screen");

    std::string username = Input::readString("Enter username to delete user: ");

    while (!User::isUserExist(username)) {
      std::cout << "User with this username does't exist\n";
      username = Input::readString("Enter username to delete user: ");
    }

    User user = User::find(username);

    _printUser(user);

    char confirmation = tolower(
        Input::readCharacter("Do you want to delete this user [y, n]: "));

    if (confirmation != 'y') {
      std::cout << "Deletion canceled\n";
      return;
    }

    if (user.remove()) {
      std::cout << "User deleted successfully\n";
    } else {
      std::cout << "Error: User is not added to database, Can't delete a none "
                   "exist user\n";
    }
  }
};
