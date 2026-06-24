#pragma once
#include <iostream>
#include <iomanip>
#include <limits>
#include "clsScreen.h"
#include "clsInputValidation.h"
#include "clsUsersListScreen.h"
#include "clsAddNewUserScreen.h"
#include  "clsDeleteUserScreen.h"
#include "clsUpdateUserScreen.h"

class clsManageUserMenu : protected clsScreen
{

private:
    enum enManageUsersMenuOptions
    {
        eListUsers = 1,
        eAddNewUser = 2,
        eDeleteUser = 3,
        eUpdateUser = 4,
        eFindUser = 5,
        eMainMenu = 6
    };

    static int ReadManageUsersMenuOption()
    {
        cout << setw(37) << left << "" << "Choose what do you want to do [1 to 6]: ";
        int Choice = clsInputValidation::ReadIntNumberBetween(1, 6, "Enter Number between 1 to 6: ");
        return Choice;
    }

    static void _GoBackToManageUsersMenu()
    {
        std::cout << std::setw(37) << std::left << "" << "\n\tPress any key to go back to Manage User Menu...\n";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin.get();
    }

    static void _ShowListUsersScreen()
    {
        clsUsersListScreen::ShowUsersList();
    }

    static void _ShowAddNewUserScreen()
    {
        clsAddNewUserScreen::ShowAddNewUser();
    }

    static void _ShowDeleteUserScreen()
    {
      clsDeleteUserScreen::ShowDeleteUserScreen();
    }

    static void _ShowUpdateUserScreen()
    {
        clsUpdateUserScreen::ShowUpdateUserScreen();
    }

    static void _ShowFindUserScreen()
    {
        std::cout << "\nFind User Screen Will Be Here.\n";
    }
    static void _ClearScreen()
    {
        system("clear");
    }
    static void _PerformManageUsersMenuOption(enManageUsersMenuOptions ManageUsersMenuOption)
    {

        switch (ManageUsersMenuOption)
        {
        case enManageUsersMenuOptions::eListUsers:
        {
            _ClearScreen();
            _ShowListUsersScreen();
            _GoBackToManageUsersMenu();
            break;
        }

        case enManageUsersMenuOptions::eAddNewUser:
        {
            _ClearScreen();
            _ShowAddNewUserScreen();
            _GoBackToManageUsersMenu();
            break;
        }

        case enManageUsersMenuOptions::eDeleteUser:
        {
            _ClearScreen();
            _ShowDeleteUserScreen();
            _GoBackToManageUsersMenu();
            break;
        }

        case enManageUsersMenuOptions::eUpdateUser:
        {
            _ClearScreen();
            _ShowUpdateUserScreen();
            _GoBackToManageUsersMenu();
            break;
        }

        case enManageUsersMenuOptions::eFindUser:
        {
            _ClearScreen();
            _ShowFindUserScreen();
            _GoBackToManageUsersMenu();
            break;
        }

        case enManageUsersMenuOptions::eMainMenu:
        {
            break;
        }
        }
    }

public:
    static void ShowManageUsersMenu()
    {
        enManageUsersMenuOptions Option;
        do
        {
            _ClearScreen();
            _DrawScreenHeader("\t Manage Users Screen");

            cout << setw(37) << left << "" << "===========================================\n";
            cout << setw(37) << left << "" << "\t\t  Manage Users Menu\n";
            cout << setw(37) << left << "" << "===========================================\n";
            cout << setw(37) << left << "" << "\t[1] List Users.\n";
            cout << setw(37) << left << "" << "\t[2] Add New User.\n";
            cout << setw(37) << left << "" << "\t[3] Delete User.\n";
            cout << setw(37) << left << "" << "\t[4] Update User.\n";
            cout << setw(37) << left << "" << "\t[5] Find User.\n";
            cout << setw(37) << left << "" << "\t[6] Main Menu.\n";
            cout << setw(37) << left << "" << "===========================================\n";
            Option =(enManageUsersMenuOptions)ReadManageUsersMenuOption();
            _PerformManageUsersMenuOption(Option);
        }while (Option != enManageUsersMenuOptions::eMainMenu);
    }
};