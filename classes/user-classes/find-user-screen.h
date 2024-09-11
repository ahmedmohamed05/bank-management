#pragma once
#include "../../public/input.h"
#include "../main/screen.h"

class FindUserScreen : protected Screen {
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
  static void showFindScreen() {
    Screen::_printScreenHeader("\t\tFind User Screen");

    std::string username = Input::readString("Enter username to find user: ");

    while (!User::isUserExist(username)) {
      std::cout << "User with this username does't exist\n";
      username = Input::readString("Enter username to find user: ");
    }

    User user = User::find(username);

    if (user.isEmpty()) {
      std::cout << "User Not Found\n";
      return;
    }

    _printUser(user);
  }
};
