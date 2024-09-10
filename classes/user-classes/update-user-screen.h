#pragma once
#include "../main/screen.h"
#include <iostream>

class UpdateUserScreen : protected Screen {
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

  static int _readPermissions() {
    int permissions = 0;

    char admin =
        Input::readCharacter("Do you want to make the user an admin [y, N]: ");
    if (char(tolower(admin)) == 'y') {
      return -1;
    }

    {
      char confirmation =
          tolower(Input::readCharacter("Show Users List [y, n]: "));
      if (confirmation == 'y') {
        permissions = permissions | showUsersPermission;
      }
    }

    {
      char confirmation =
          tolower(Input::readCharacter("Add New User [y, n]: "));
      if (confirmation == 'y') {
        permissions = permissions | addNewUserPermission;
      }
    }

    {
      char confirmation = tolower(Input::readCharacter("Delete User [y, n]: "));
      if (confirmation == 'y') {
        permissions = permissions | deleteUserPermission;
      }
    }

    {
      char confirmation =
          tolower(Input::readCharacter("Update User Info [y, n]: "));
      if (confirmation == 'y') {
        permissions = permissions | updateUserPermission;
      }
    }

    {
      char confirmation = tolower(Input::readCharacter("Find User [y, n]: "));
      if (confirmation == 'y') {
        permissions = permissions | findUserPermission;
      }
    }

    {
      char confirmation =
          tolower(Input::readCharacter("Transactions [y, n]: "));
      if (confirmation == 'y') {
        permissions = permissions | transactionsPermission;
      }
    }

    {
      char confirmation =
          tolower(Input::readCharacter("Manage Users [y, n]: "));
      if (confirmation == 'y') {
        permissions = permissions | manageUsersPermission;
      }
    }

    return permissions;
  }

  static void _updateUser(User &user) {
    user.setFirstName(Input::readString("Enter First Name: "));
    user.setLastName(Input::readString("Enter Last Name: "));
    user.setEmail(Input::readString("Enter Email: "));
    user.setPhone(Input::readString("Enter Phone Number: "));
    user.setPassword(Input::readString("Enter password: "));
    user.setPermissions(_readPermissions());
  }

public:
  static void showUpdateScreen() {
    Screen::_printScreenHeader("\t\tUpdate User Screen");
    std::string username = Input::readString("Enter username to update user: ");

    while (!User::isUserExist(username)) {
      std::cout << "User with this username does't exist\n";
      username = Input::readString("Enter username to update user: ");
    }

    User user = User::find(username);

    _printUser(user);

    char confirmation = tolower(
        Input::readCharacter("Do you want to update this user [y, n]: "));

    if (confirmation != 'y') {
      std::cout << "update canceled\n";
      return;
    }

    _updateUser(user);

    switch (user.save()) {
    case User::saveResults::faildEmptyObject:
      std::cout << "Error: User hasn't update it's empty\n";
      break;

    case User::saveResults::faildUnknownError:
      std::cout << "Error: user not saved, Unkown Error\n";
      break;

    case User::saveResults::success:
      std::cout << "User updated successfully\n";
      break;
    }
  }
};
