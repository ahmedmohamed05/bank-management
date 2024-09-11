#pragma once
#include "../../public/global.h"
#include "../../public/input.h"
#include "../client-classes/bank-client.h"
#include "./screen.h"
#include <cstdlib>
#include <iostream>
// Screens
#include "../client-classes/delete-client-screen.h"
#include "../client-classes/find-screen.h"
#include "../client-classes/new-client-screen.h"
#include "../client-classes/show-clients-screen.h"
#include "../client-classes/transactions-screen.h"
#include "../client-classes/update-client-screen.h"
#include "../user-classes/manage-users-screen.h"
#include "./login-register-screen.h"

class MainScreen : protected Screen {
private:
  enum _options {
    showClients,
    newClient,
    delClient,
    updateClient,
    findClient,
    showTransactions,
    manage,
    showLoginRegister,
    logOut,
    endProg,
  };

  static short _readUserOption() {
    short option;
    option = Input::readShortInRange("What do you want to do: ", 1, 10);
    return option;
  }

  static void _showAllClientsScreen() { ClientsScreen::showAllClients(); }

  static void _showAddNewClientsScreen() { NewClientScreen::addNewClient(); }

  static void _showDeleteClientScreen() { DeleteClientScreen::deleteClient(); }

  static void _showUpdateClientScreen() { UpdateClientScreen::updateClient(); }

  static void _showFindClientScreen() { FindClientScreen::findClient(); }

  static void _showTransactionsMenu() {
    Transactions::showTransactionsScreen();
  }

  static void _showLoginRegisterScreen() {
    LoginRegisterScreen::showLoginRegistersScreen();
  }

  static void _showManageUsersMenu() {
    ManageUsersScreen::showManageUsersScreen();
  }

  static void endProgramme() {
    std::cout << "Good Bye :-)\n";
    exit(EXIT_SUCCESS);
  }

  static void _performMainMenuOption(_options MainMenuOption) {
    system("clear");

    // MainMenuOption < 8: so that the user can logout and exit without
    // permissions
    if (!currentUser.checkPermission(MainMenuOption) && MainMenuOption < 8) {
      Screen::_printAccessDenied("\t\tAccess Denied\n\t\tContact your admin");
    } else {
      switch (MainMenuOption) {
      case _options::showClients:
        _showAllClientsScreen();
        break;
      case _options::newClient:
        _showAddNewClientsScreen();
        break;
      case _options::delClient:
        _showDeleteClientScreen();
        break;
      case _options::updateClient:
        _showUpdateClientScreen();
        break;
      case _options::findClient:
        _showFindClientScreen();
        break;
      case _options::showTransactions:
        _showTransactionsMenu();
        break;
      case _options::manage:
        _showManageUsersMenu();
        break;
      case _options::showLoginRegister:
        _showLoginRegisterScreen();
        break;
      case _options::logOut:
        currentUser = User::find("", "");
        return;
      case _options::endProg:
        endProgramme();
        break;
      }
    }
    printMainScreen();
  }

public:
  static void printMainScreen() {
    Screen::_printScreenHeader("\t\tMain Screen", 43);

    std::cout << "[1] Show Client List.\n";
    std::cout << "[2] Add New Client.\n";
    std::cout << "[3] Delete Client.\n";
    std::cout << "[4] Update Client Info.\n";
    std::cout << "[5] Find Client.\n";
    std::cout << "[6] Transactions.\n";
    std::cout << "[7] Manage Users.\n";
    std::cout << "[8] Show Logins.\n";
    std::cout << "[9] Logout.\n";
    std::cout << "[10] Exit.\n";
    std::cout << "===========================================\n";

    _performMainMenuOption(_options(_readUserOption() - 1));
  }
};
