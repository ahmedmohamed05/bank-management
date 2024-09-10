#pragma once
#include "../main/screen.h"
#include <input.h>

#include "./del-user-screen.h"
#include "./find-user-screen.h"
#include "./list-users-screen.h"
#include "./new-user-screen.h"
#include "./update-user-screen.h"

class ManageUsersScreen : protected Screen {
private:
  enum options {
    listUsers,
    addNewUser,
    delUser,
    updateUser,
    findUser,
    mainMenu
  };

  static short _readManageOption() {
    short option = Input::readShortInRange("What do you want to do: ", 1, 6);
    return option;
  }

  static void _showListUsersScreen() { ListUsersScreen::showUsers(); }
  static void _showAddNewUserScreen() { AddNewUserScreen::showAddNewScreen(); }
  static void _showDeleteUserScreen() { DelUserScreen::showDelUserScreen(); }
  static void _showUpdateUserScreen() { UpdateUserScreen::showUpdateScreen(); }
  static void _showFindUserScreen() { FindUserScreen::showFindScreen(); }

  static void _performManagementOperation(options option) {
    system("clear");

    switch (option) {
    case options::listUsers:
      _showListUsersScreen();
      break;
    case options::addNewUser:
      _showAddNewUserScreen();
      break;
    case options::delUser:
      _showDeleteUserScreen();
      break;
    case options::updateUser:
      _showUpdateUserScreen();
      break;
    case options::findUser:
      _showFindUserScreen();
      break;
    case options::mainMenu:
      return;
      break;
    }

    showManageUsersScreen();
  }

public:
  static void showManageUsersScreen() {
    Screen::_printScreenHeader("Manage Users Screen");
    std::cout << "[1] List Users.\n";
    std::cout << "[2] Add New User.\n";
    std::cout << "[3] Delete User.\n";
    std::cout << "[4] Update User Information.\n";
    std::cout << "[5] Find User.\n";
    std::cout << "[6] Main Menu.\n";
    std::cout << "===========================================\n";

    _performManagementOperation(options(_readManageOption() - 1));
  }
};
