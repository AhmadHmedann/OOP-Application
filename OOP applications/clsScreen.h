// This Screen is for future feature by example if I want to Add a clock for all screen that I have
// so I will make all screen inherits this screen with  a Protected mode
#pragma once
#include <iostream>
#include "clsUser.h"
#include "Global.h"
class clsScreen
{
protected:
    static void _DrawScreenHeader(std::string Title, std::string SubTitle = "")
    {
        std::cout << "\t\t\t\t\t______________________________________";
        std::cout << "\n\n\t\t\t\t\t  " << Title;
        if (SubTitle != "")
        {
            std::cout << "\n\t\t\t\t\t  " << SubTitle;
        }
        std::cout << "\n\t\t\t\t\t______________________________________\n\n";
    }
    static bool CheckAccessRight(clsUser::enPermissions Permissions)
    {
        if(!CurrentUser.CheckAccessPermission(Permissions))
        {
            {
                std::cout << "\t\t\t\t\t______________________________________";
                std::cout << "\n\n\t\t\t\t\t  Access Denied! Contact your Admin.";
                std::cout << "\n\t\t\t\t\t______________________________________\n\n";
                return false;
            }
        }else
        return true;
    }
    static void _GoBackToMainMenu()
    {

        std::cout << std::setw(37) << std::left << "" << "\n\tPress any key to go back to Main Menu...\n";
        std::cin.get();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
};
