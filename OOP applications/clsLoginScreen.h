#pragma once
#include <iostream>
#include "clsScreen.h"
#include "Global.h"
#include "clsMainScreen.h"
#include <cstdlib>
#include "clsInputValidation.h"
#include "clsUser.h"
class clsLoginScreen : protected clsScreen
{

private:
    static bool _Login()
    {
        bool LoginFailed = false;
        std::string UserName, Password;
        int Counter = 2;
        do
        {
            if (LoginFailed)
            {
                std::cout << "\nInvalid UserName/Password!\n";
                std::cout << "You have " << Counter << " Trials to login.\n";
                Counter--;
            }
            if (Counter < 0)
            {
                return false;
            }
            std::cout << "\nEnter UserName: ";
            UserName = clsInputValidation::ReadString();
            std::cout << "Enter Password: ";
            Password = clsInputValidation::ReadString();

            CurrentUser = clsUser::Find(UserName, Password);
            LoginFailed = CurrentUser.IsEmpty();

        } while (LoginFailed);
        clsMainScreen::ShowMainMenu();
        return true;
    }

public:
    static bool ShowLoginScreen()
    {
        system("clear");
        _DrawScreenHeader("\tLogin Screen");
        return _Login();
    }
};