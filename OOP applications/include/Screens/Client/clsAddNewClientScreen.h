#pragma once
#include <iostream>
#include "Core/clsBankClient.h"
#include "Screens/clsScreen.h"
#include "Lib/clsInputValidation.h"
#include <iomanip>

class clsAddNewClientScreen : protected clsScreen
{
private:
    static void _ReadClientInfo(clsBankClient &Client)
    {
        std::cout << "\nEnter FirstName: ";
        Client.SetFirstName(clsInputValidation::ReadString());
        std::cout << "\nEnter LastName: ";
        Client.SetLastName(clsInputValidation::ReadString());
        std::cout << "\nEnter Email: ";
        Client.SetEmail(clsInputValidation::ReadString());
        std::cout << "\nEnter Phone: ";
        Client.SetPhone(clsInputValidation::ReadString());
        std::cout << "\nEnter PinCode: ";
        Client.SetPinCode(clsInputValidation::ReadString());
        std::cout << "\nEnter Account Balance: ";
        Client.SetAccountBalance(clsInputValidation::ReadFloatNumber());
    }
    static void _PrintClient(const clsBankClient &Client)
    {

        std::cout << "\nClient Card:";
        std::cout << "\n_______________________________________";
        std::cout << "\nFirstName   : " << Client.FirstName();
        std::cout << "\nLastName    : " << Client.LastName();
        std::cout << "\nFull Name   : " << Client.FullName();
        std::cout << "\nEmail       : " << Client.Email();
        std::cout << "\nPhone       : " << Client.Phone();
        std::cout << "\nAcc. Number : " << Client.AccountNumber();
        std::cout << "\nPinCode     : " << Client.PinCode();
        std::cout << "\nBalance     : " << Client.AccountBalance();
        std::cout << "\n_______________________________________\n";
    }

public:
    static void AddNewClientScreen()
    {
        if (!CheckAccessRight(clsUser::enPermissions::pAddNewClient))
        {
            return;
        }
        _DrawScreenHeader("\t Add New client Screen");
        std::cout << "Please Enter Account Number: ";
        std::string AccountNumber = clsInputValidation::ReadString();
        while (clsBankClient::IsClientExist(AccountNumber))
        {
            std::cout << "\nClient with [" << AccountNumber << "] is already exist, please Enter another one.";
            AccountNumber = clsInputValidation::ReadString();
        }
        clsBankClient NewClient = clsBankClient::GetAddNewClientObject(AccountNumber);
        _ReadClientInfo(NewClient);
        clsBankClient::enSaveResults SaveResults = NewClient.Save();
        switch (SaveResults)
        {
        case clsBankClient::enSaveResults::svSucceeded:
            std::cout << "\nClient Added successfully :)";
            _PrintClient(NewClient);
            break;
        case clsBankClient::enSaveResults::svFailedAccountNumberExists:
            std::cout << "\nError account was not saved because account number is used!\n";
            break;
        case clsBankClient::enSaveResults::svFailedEmptyObject:
        {
            std::cout << "\nError, Account was not save because it's Empty. ";
            break;
        }
        default:
        {
            std::cout << "\nUnknown save result.";
            break;
        }
        }
    }
};
