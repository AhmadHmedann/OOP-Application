#pragma once
#include <iostream>
#include <iomanip>
#include <limits>
#include "clsScreen.h"
#include "clsInputValidation.h"
#include "clsClientListScreen.h"
#include "clsAddNewClientScreen.h"
#include "clsDeleteClientScreen.h"
#include "clsUpdateClientScreen.h"
#include "clsFindClientScreen.h"
#include "clsTransactionScreen.h"
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
        eExit = 8
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

        std::cout << "\n Manage User menu, Coming soon...\n";
    }
    static void _ShowEndScreen()
    {

        std::cout << "\n Show End screen, Coming soon...\n";
    }
    static int _ReadMainMenuOption()
    {
        std::cout << std::setw(37) << std::left << "" << "Choose what do you want to do [1 to 8]: ";
        int choice = clsInputValidation::ReadIntNumberBetween(1, 8, "Enter Number between 1 to 8? ");

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
        case enMainMenuOptions::eExit:
        {
            _ClearScreen();
            _ShowEndScreen();
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
            std::cout << std::setw(37) << std::left << "" << "\t[8] Logout.\n";
            std::cout << std::setw(37) << std::left << "" << "===========================================\n";
            Option = (enMainMenuOptions)_ReadMainMenuOption();
            _PerformMainMenuOption(Option);
        } while (Option != enMainMenuOptions::eExit);
    }
};
