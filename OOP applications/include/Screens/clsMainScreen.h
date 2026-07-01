#pragma once
#include <iostream>
#include <iomanip>
#include <limits>
#include "Screens/clsScreen.h"
#include "Lib/clsInputValidation.h"
#include "Screens/Client/clsClientListScreen.h"
#include "Screens/Client/clsAddNewClientScreen.h"
#include "Screens/Client/clsDeleteClientScreen.h"
#include "Screens/Client/clsUpdateClientScreen.h"
#include "Screens/Client/clsFindClientScreen.h"
#include "Screens/Client/clsTransactionScreen.h"
#include "Screens/User/clsManageUserMenu.h"
#include "Global.h"
#include "Screens/Client/clsLoginRegisterScreen.h"
#include "Screens/Currency/clsCurrencyExchangeMenu.h"
class clsMainScreen : protected clsScreen
{
private:
    enum enMainMenuOptions
    {
        eListClients = 1,
        eAddNewClient = 2,
        eDeleteClient = 3,
        eUpdateClient = 4,
        eFindClient = 5,
        eShowTransactionsMenu = 6,
        eManageUsers = 7,
        eLoginRegister = 8,
        eCurrencyExchange =9,
        eLogout = 10,
    };
    static void _ShowAllClientScreen()
    {
        clsClientListScreen::ShowClientList();
    }
    static void _ShowAddNewClientScreen()
    {
        clsAddNewClientScreen::AddNewClientScreen();
    }
    static void _ShowDeleteClientScreen()
    {
        clsDeleteClientScreen::ShowDeleteClientScreen();
    }
    static void _ShowUpdateClientScreen()
    {

        clsUpdateClientScreen::ShowUpdateClientScreen();
    }
    static void _ShowFindClientScreen()
    {
        clsFindClientScreen::ShowFindClientScreen();
    }
    static void _ShowTransactionMenu()
    {

        clsTransactionScreen::ShowTransactionsMenu();
    }
    static void _ShowManageUserMenu()
    {

       clsManageUserMenu::ShowManageUsersMenu();
    }
    static void __ShowLoginRegisterScreen()
    {
        clsLoginRegisterScreen::ShowLoginRegisterScreen();
    }
    static void _ShowCurrencyExchange()
    {
        clsCurrencyExchangeMenuScreen::ShowCurrencyExchangeMenu();
    }
    static void _Logout()
    {
        CurrentUser = clsUser::Find("","");
      
    }
    static int _ReadMainMenuOption()
    {
        std::cout << std::setw(37) << std::left << "" << "Choose what do you want to do [1 to 10]: ";
        int choice = clsInputValidation::ReadIntNumberBetween(1, 10, "Enter Number between 1 to 10? ");

        return choice;
    }
    static void _ClearScreen()
    {
        system("clear");
    }
    static void _GoBackToMainMenu()
    {

        std::cout << std::setw(37) << std::left << "" << "\n\tPress any key to go back to Main Menu...\n";
        std::cin.get();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    static void _PerformMainMenuOption(enMainMenuOptions option)
    {
        switch (option)
        {
        case enMainMenuOptions::eListClients:
        {
            _ClearScreen();
            _ShowAllClientScreen();
            _GoBackToMainMenu();
            break;
        }
        case enMainMenuOptions::eAddNewClient:
        {
            _ClearScreen();
            _ShowAddNewClientScreen();
            _GoBackToMainMenu();
            break;
        }
        case enMainMenuOptions::eDeleteClient:
        {
            _ClearScreen();
            _ShowDeleteClientScreen();
            _GoBackToMainMenu();
            break;
        }
        case enMainMenuOptions::eUpdateClient:
        {
            _ClearScreen();
            _ShowUpdateClientScreen();
            _GoBackToMainMenu();
            break;
        }
        case enMainMenuOptions::eFindClient:
        {
            _ClearScreen();
            _ShowFindClientScreen();
            _GoBackToMainMenu();
            break;
        }
        case enMainMenuOptions::eShowTransactionsMenu:
        {
            _ClearScreen();
            _ShowTransactionMenu();
            break;
        }
        case enMainMenuOptions::eManageUsers:
        {
            _ClearScreen();
            _ShowManageUserMenu();
            break;
        }
        case enMainMenuOptions::eLoginRegister:
        {
            _ClearScreen();
            __ShowLoginRegisterScreen();
            _GoBackToMainMenu();
            break;
        }
        case enMainMenuOptions::eCurrencyExchange:
        {
            _ClearScreen();
            _ShowCurrencyExchange();
            break;
        }
        case enMainMenuOptions::eLogout:
        {
            _ClearScreen();
            _Logout();
            break;
        }
        default:
            break;
        }
    }

public:
    static void ShowMainMenu()
    {
        // Issue:
        // `_GoBackToMainMenu()` calls `ShowMainMenu()` again, which creates recursive function calls.
        // Each time the user goes back to the main menu, a new function call is added to the call stack.
        // This is not a good design for menu navigation. A loop should be used instead.
        enMainMenuOptions Option;
        do
        {
            _ClearScreen();
            _DrawScreenHeader("\t\tMain Screen");

            std::cout << std::setw(37) << std::left << "" << "===========================================\n";
            std::cout << std::setw(37) << std::left << "" << "\t\t\tMain Menu\n";
            std::cout << std::setw(37) << std::left << "" << "===========================================\n";
            std::cout << std::setw(37) << std::left << "" << "\t[1] Show Client List.\n";
            std::cout << std::setw(37) << std::left << "" << "\t[2] Add New Client.\n";
            std::cout << std::setw(37) << std::left << "" << "\t[3] Delete Client.\n";
            std::cout << std::setw(37) << std::left << "" << "\t[4] Update Client Info.\n";
            std::cout << std::setw(37) << std::left << "" << "\t[5] Find Client.\n";
            std::cout << std::setw(37) << std::left << "" << "\t[6] Transactions.\n";
            std::cout << std::setw(37) << std::left << "" << "\t[7] Manage Users.\n";
            std::cout << std::setw(37) << std::left << "" << "\t[8] Login Register.\n";
            std::cout << std::setw(37) << std::left << "" << "\t[9] Currency Exchange.\n";
            std::cout << std::setw(37) << std::left << "" << "\t[10] Logout.\n";
            std::cout << std::setw(37) << std::left << "" << "===========================================\n";
            Option = (enMainMenuOptions)_ReadMainMenuOption();
            _PerformMainMenuOption(Option);
        } while (Option != enMainMenuOptions::eLogout);
    }
};
