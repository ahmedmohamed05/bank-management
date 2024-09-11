#pragma once
#include "../../public/input.h"
#include "../main/screen.h"
#include "./user.h"
#include <iostream>

class AddNewUserScreen : protected Screen {
private:
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

    {
      char confirmation = tolower(Input::readCharacter("Show Logs [y, n]: "));
      if (confirmation == 'y') {
        permissions = permissions | ShowLogPermission;
      }
    }

    return permissions;
  }

  static User readUser() {

    std::string userName = Input::readString("Enter Username: ");

    while (User::isUserExist(userName)) {
      std::cout << "Error: User with this username already exist\n";
      std::string userName = Input::readString("Enter Username: ");
    }

    std::string firstName = Input::readString("Enter First Name: ");
    std::string lastName = Input::readString("Enter Last Name: ");
    std::string email = Input::readString("Enter Email: ");
    std::string phone = Input::readString("Enter Phone Number: ");
    std::string password = Input::readString("Enter password: ");
    int permissions = _readPermissions();

    return User(firstName, lastName, email, phone, userName, password,
                permissions);
  }

public:
  static void showAddNewScreen() {
    Screen::_printScreenHeader("\tAdd New User Screen");
    User user = readUser();

    char confirmation =
        tolower(Input::readCharacter("Are you sure adding this user [y, n]: "));

    if (confirmation != 'y') {
      system("clear");
      std::cout << "Operation canceled\n";
      return;
    }

    switch (user.save()) {
    case User::saveResults::faildEmptyObject:
      std::cout << "Error: User not save it's empty\n";
      break;

    case User::saveResults::faildUserExists:
      std::cout << "Error: User already exists\n";
      break;
    case User::saveResults::faildUnknownError:
      std::cout << "Error: user not saved, Unkown Error\n";
      break;

    case User::saveResults::success:
      std::cout << "User added successfully\n";
      break;
    }
  }
};
