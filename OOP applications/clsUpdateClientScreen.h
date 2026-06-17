#pragma once
#include <iostream>
#include "clsBankClient.h"
#include "clsScreen.h"
#include "clsInputValidation.h"

class clsUpdateClientScreen : protected clsScreen
{
private:
    static void _ReadClientInfo(clsBankClient &Client)
    {
        std::cout << "\nEnter FirstName: ";
        Client.SetFirstName(clsInputValidation::ReadString());
        std::cout << "\nEnter LastName; ";
        Client.SetLastName(clsInputValidation::ReadString());
        std::cout << "\nEnter Email: ";
        Client.SetEmail(clsInputValidation::ReadString());
        std::cout << "\nEnter Phone: ";
        Client.SetPhone(clsInputValidation::ReadString());
        std::cout << "\nEnter PinCode: ";
        Client.SetPinCode(clsInputValidation::ReadString());
        std::cout << "\nEnter Account Balance; ";
        Client.SetAccountBalance(clsInputValidation::ReadFloatNumber());
    }
    static void _PrintClient(clsBankClient Client)
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
    static void ShowUpdateClientScreen()
    {
        _DrawScreenHeader("\t Update Client Screen");

        std::cout << "\nPlease Enter Account Number: ";
        std::string AccountNumber = clsInputValidation::ReadString();

        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            std::cout << "Account number is not found, Please Enter another one: ";
            AccountNumber = clsInputValidation::ReadString();
        }
        clsBankClient Client = clsBankClient::Find(AccountNumber);
        _PrintClient(Client);

        char Confirm;
        std::cout << "Are you sure you want to update this client? Y/N? ";
        std::cin >> Confirm;
        if (std::tolower(Confirm) == 'y')
        {
            std::cout << "\n\n Update Client Info:";
            std::cout << "\n______________________________________________________________\n";
            _ReadClientInfo(Client);
            // note: this code below is to separate UI
            clsBankClient::enSaveResults SaveResults = Client.Save();
            switch (SaveResults)
            {
            case clsBankClient::enSaveResults::svSucceeded:
            {
                std::cout << "\nAccount Updated successfully :)";
                _PrintClient(Client);

                break;
            }
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
    }
};