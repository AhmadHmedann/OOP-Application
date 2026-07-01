#pragma once
#include <iostream>
#include "Screens/clsScreen.h"
#include "Lib/clsInputValidation.h"
#include "Core/clsUser.h"
#include <cctype>

class clsUpdateUserScreen : protected clsScreen
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

    static int _ReadPermissionsToSet()
    {
        int Permissions = 0;
        char Answer;
        std::cout << "\nDo you want to give full access? y/n? ";
        std::cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            return -1;
        }
        std::cout << "\nDo you want to give access to : \n ";

        std::cout << "\nShow Client List? y/n? ";
        std::cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions = Permissions + clsUser::enPermissions::pListClient;
        }

        std::cout << "\nAdd New Client? y/n? ";
        std::cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enPermissions::pAddNewClient;
        }

        std::cout << "\nDelete Client? y/n? ";
        std::cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enPermissions::pDeleteClient;
        }

        std::cout << "\nUpdate Client? y/n? ";
        std::cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enPermissions::pUpdateClient;
        }

        std::cout << "\nFind Client? y/n? ";
        std::cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enPermissions::pFindClient;
        }

        std::cout << "\nTransactions? y/n? ";
        std::cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enPermissions::pTransaction;
        }

        std::cout << "\nManage Users? y/n? ";
        std::cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enPermissions::pManageUserMenu;
        }
        std::cout << "\nShow Login Register Screen? y/n? ";
        std::cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += clsUser::enPermissions::pShowLoginRegister;
        }
        return Permissions;
    }

    static void _ReadUserInfo(clsUser &User)
    {
        // clsUser(enMode Mode, std::string FirstName, std::string LastName, std::string Email, std::string Phone, std::string UserName, std::string Password, int Permissions)
        std::cout << "\nEnter FirstName: ";
        User.SetFirstName(clsInputValidation::ReadString());
        std::cout << "\nEnter LastName; ";
        User.SetLastName(clsInputValidation::ReadString());
        std::cout << "\nEnter Email: ";
        User.SetEmail(clsInputValidation::ReadString());
        std::cout << "\nEnter Phone: ";
        User.SetPhone(clsInputValidation::ReadString());
        std::cout << "\nEnter Password: ";
        User.SetPassword(clsInputValidation::ReadString());
        std::cout << "\nEnter Permissions: ";
        User.SetPermissions(_ReadPermissionsToSet());
    }

public:
    static void ShowUpdateUserScreen()
    {
        _DrawScreenHeader("\t Update User Screen");

        std::cout << " Please enter username :  ";
        std::string UserName = clsInputValidation::ReadString();
        while (!clsUser::IsUserExists(UserName))
        {
            std::cout << "UserName not found, please enter another one: ";
            UserName = clsInputValidation::ReadString();
        }
        clsUser User = clsUser::Find(UserName);
        _PrintUser(User);
        char Confirm;
        std::cout << "Are you sure you want to Update this User? Y/N: ";
        std::cin >> Confirm;
        if (std::tolower(Confirm) == 'y')
        {
            cout << "\n\nUpdate User Info:";
            cout << "\n____________________\n";
            _ReadUserInfo(User);
            clsUser::enSaveResults SaveResult = User.Save();
            switch (SaveResult)
            {
            case clsUser::enSaveResults::svSucceeded:
                std::cout << "\nUser Updated Successfully.";
                _PrintUser(User);
                break;
            case clsUser::enSaveResults::svFailedEmptyObject:
                std::cout << "\nError, User was not save because it's Empty. ";
                break;

            default:
                std::cout << "\nUnknown save result.";
                break;
            }
        }
        else
        {
            std::cout << "\nUpdate operation was cancelled.\n";
        }
    }
};