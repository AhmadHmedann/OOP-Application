#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsInputValidation.h"
#include "clsUser.h"

class clsDeleteUserScreen : protected clsScreen
{
private:
    static void _PrintUser(const clsUser &User)
    {
        std::cout << "\nUser Card:";
        std::cout << "\n___________________";
        std::cout << "\nFirstName   : " << User.FirstName();
        std::cout << "\nLastName    : " << User.LastName();
        std::cout << "\nFull Name   : " << User.FullName();
        std::cout << "\nEmail       : " << User.Email();
        std::cout << "\nPhone       : " << User.Phone();
        std::cout << "\nUser Name   : " << User.UserName();
        std::cout << "\nPassword    : " << User.Password();
        std::cout << "\nPermissions : " << User.Permissions();
        std::cout << "\n___________________\n";
    }

public:
    static void ShowDeleteUserScreen()
    {
        _DrawScreenHeader("\t Delete User Screen");

        std::cout << "Please Enter UserName: ";
        std::string UserName = clsInputValidation::ReadString();
        while (!clsUser::IsUserExists(UserName))
        {
            std::cout << "User name not found, please enter another one: ";
            UserName = clsInputValidation::ReadString();
        }
        clsUser User = clsUser::Find(UserName);
        _PrintUser(User);
        char Confirm;
        std::cout << "Are you sure you want to Delete this User? Y/N? ";
        std::cin >> Confirm;
        if (std::tolower(Confirm) == 'y')
        {
            if (User.Delete())
            {
                std::cout << "\nUser Deleted Successfully :-)\n";
               
            }
            else
            {
                std::cout << "\nError User Was not Deleted\n";
            }
        }
    }
};