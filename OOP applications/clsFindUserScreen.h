#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsPerson.h"
#include "clsUser.h"
#include "clsInputValidation.h"

class clsFindUserScreen : protected clsScreen
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
    static void ShowFindUserScreen()
    {

        _DrawScreenHeader("\t  Find User Screen");

        std::string UserName;
        std::cout << "\nPlease Enter UserName: ";
        UserName = clsInputValidation::ReadString();
        while (!clsUser::IsUserExists(UserName))
        {
            std::cout << "\nUser is not found, choose another one: ";
            UserName = clsInputValidation::ReadString();
        }

        clsUser User = clsUser::Find(UserName);

        if (!User.IsEmpty())
        {
            std::cout << "\nUser Found :-)\n";
        }
        else
        {
            std::cout << "\nUser Was not Found :-(\n";
        }

        _PrintUser(User);
    }
};
