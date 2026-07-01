
#pragma once
#include <iostream>
#include "Core/clsBankClient.h"
#include "Screens/clsScreen.h"
#include "Lib/clsInputValidation.h"

class clsWithdrawScreen : protected clsScreen
{
    static void _PrintClient(const clsBankClient& Client)
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
    static void ShowWithdrawScreen()
    {

        _DrawScreenHeader("\t Withdraw Screen");

        std::cout << "\nPlease Enter Account Number: ";
        std::string AccountNumber = clsInputValidation::ReadString();

        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            std::cout << "\nClient with [" << AccountNumber << "] does not exist.\n";
            AccountNumber = clsInputValidation::ReadString();
        }
        clsBankClient Client = clsBankClient::Find(AccountNumber);
        _PrintClient(Client);
        double Amount = 0;
        std::cout << "\nPlease enter Withdraw amount? ";
        Amount = clsInputValidation::ReadDblNumberBetween(0, __DBL_MAX__, "Enter a positive amount: ");
        char Confirm;
        std::cout << "Are you sure you want to perform this transaction? Y/N? ";
        std::cin >> Confirm;
        if (std::tolower(Confirm) == 'y')
        {
            if (Client.Withdraw(Amount))
            {
                std::cout << "\nAmount Withdraw Successfully.\n"; // i must add to check if the amount bigger than
                std::cout << "\nNew Balance Is: " << Client.AccountBalance();
            }
            else
            {
                std::cout<<"\nCan not withdraw, insufficient Balance!\n";
                std::cout<<"\nAmount to withdraw is: "<<Amount;
                std::cout<<"\nYour Balance is: "<<Client.AccountBalance();
            }
        }
        else
        {
            std::cout << "\nOperation was cancelled.\n";
        }
    }
};