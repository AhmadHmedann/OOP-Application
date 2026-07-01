#pragma once
#include <iostream>
#include "Screens/clsScreen.h"
#include "Core/clsPerson.h"
#include "Core/clsBankClient.h"
#include "Lib/clsInputValidation.h"

class clsFindClientScreen : protected clsScreen
{

private:
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
    static void ShowFindClientScreen()
    {
        if (!CheckAccessRight(clsUser::enPermissions::pFindClient))
        {
            return;
        }
        _DrawScreenHeader("\tFind Client Screen");

        std::cout << "\nPlease Enter Account Number: ";
        std::string AccountNumber = clsInputValidation::ReadString();

        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            std::cout << "Account number is not found, Please Enter another one: ";
            AccountNumber = clsInputValidation::ReadString();
        }
        clsBankClient Client = clsBankClient::Find(AccountNumber);
        

        if (!Client.IsEmpty())
        {
            cout << "\nClient Found :-)\n";
        }
        else
        {
            cout << "\nClient Was not Found :-(\n";
        }

        _PrintClient(Client);
    }
};