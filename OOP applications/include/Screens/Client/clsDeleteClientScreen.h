#pragma once
#include <iostream>
#include "Core/clsBankClient.h"
#include "Screens/clsScreen.h"
#include "Lib/clsInputValidation.h"

class clsDeleteClientScreen : protected clsScreen
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
    static void ShowDeleteClientScreen()
    {
        if (!CheckAccessRight(clsUser::enPermissions::pDeleteClient))
        {
            return;
        }
        _DrawScreenHeader("\tDelete Client Screen");
        std::cout << "\nPlease Enter an Account Number: ";
        std::string AccountNumber = clsInputValidation::ReadString();
        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            std::cout << "Account Number is not Found. Please Enter another one: ";
            AccountNumber = clsInputValidation::ReadString();
        }
        clsBankClient Client = clsBankClient::Find(AccountNumber);
        _PrintClient(Client);

        char Confirm;
        std::cout << "Are you sure you want to Delete this client? Y/N? ";
        std::cin >> Confirm;
        if (std::tolower(Confirm) == 'y')
        {
            if (Client.Delete())
            {
                std::cout << "\nClient Deleted Successfully. \n";
                _PrintClient(Client);
            }
            else
            {
                std::cout << "Error: Client was not Deleted \n";
            }
        }
    }
};