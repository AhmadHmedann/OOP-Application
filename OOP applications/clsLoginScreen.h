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
    static void _Login()
    {
        bool LoginFailed = false;
        std::string UserName, Password;
        do
        {
            if (LoginFailed)
            {
                std::cout << "\nInvalid UserName/Password!\n";
            }
            std::cout << "\nEnter UserName: ";
            UserName = clsInputValidation::ReadString();
            std::cout << "Enter Password: ";
            Password = clsInputValidation::ReadString();

            CurrentUser = clsUser::Find(UserName, Password);
            LoginFailed = CurrentUser.IsEmpty();

        } while (LoginFailed);
        clsMainScreen::ShowMainMenu();
    }

public:
    static void ShowLoginScreen()
    {
        system("clear");
        _DrawScreenHeader("\tLogin Screen");
        _Login();
    }
};