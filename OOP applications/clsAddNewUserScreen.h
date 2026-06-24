#pragma once
#include <iostream>
#include "clsUser.h"
#include "clsScreen.h"
#include "clsInputValidation.h"

class clsAddNewUserScreen : protected clsScreen
{
private:
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

        return Permissions;
    }

public:
    static void ShowAddNewUser()
    {
        std::cout << "Please Enter User Name: ";
        std::string UserName = clsInputValidation::ReadString();
        while (clsUser::IsUserExists(UserName))
        {
            std::cout << "\nUser with [" << UserName << "] is already exist, please Enter another one.";
            UserName = clsInputValidation::ReadString();
        }
        clsUser NewUser = clsUser::GetAddNewUserObject(UserName);
        _ReadUserInfo(NewUser);
        clsUser::enSaveResults SaveResults = NewUser.Save();
        switch (SaveResults)
        {
        case clsUser::enSaveResults::svSucceeded:
        {
            std::cout << "\nUser Added Successfully";
            _PrintUser(NewUser);
            break;
        }
        case clsUser::enSaveResults::svFailedEmptyObject:
        {
            std::cout << "\nError User was not saved because it's Empty";
            break;
        }
        case clsUser::enSaveResults::svErrorUserIsExists:
        {
            std::cout << "\nError User was not saved because UserName is used!\n";
            break;
        }

        default:
        {
            std::cout << "\nError User was not saved because it's Empty";
            break;
        }
        }
    }
};

// read unique user name  -> create a user object with that user name and Mode AddNewMode -> Read UserInfo (&user) -> enSaveResult SaveResult = USer.save() -> Print(u)