#pragma once
#include <iostream>
#include <iomanip>
#include <cctype>
#include <limits>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidation.h"

class clsTransferScreen : protected clsScreen
{
private:
    static void _PrintClientCard(const clsBankClient &Client)
    {
        std::cout << "\nUser Card:";
        std::cout << "\n________________________________";
        std::cout << "\nFull Name   : " << Client.FullName();
        std::cout << "\nAcc. Number : " << Client.AccountNumber();
        std::cout << "\nBalance     : " << Client.AccountBalance();
        std::cout << "\n________________________________\n";
    }
    static double _ReadAmount(const clsBankClient SourceClient)
    {
        double Amount;

        std::cout << "\nEnter Transfer Amount? ";

        Amount = clsInputValidation::ReadDblNumberBetween(0, __DBL_MAX__, "Enter a positive amount: ");

        while (Amount > SourceClient.AccountBalance())
        {
            cout << "\nAmount Exceeds the available Balance, Enter another Amount ? ";
            Amount = clsInputValidation::ReadDblNumberBetween(0, __DBL_MAX__, "Enter a positive amount: ");
        }
        return Amount;
    }
    static std::string ReadAccountNumber(std::string messages)
    {
        std::string AccountNumber;
        std::cout << "\nPlease Enter Account Number to Transfer "<<messages<<": ";
        AccountNumber = clsInputValidation::ReadString();
        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            std::cout << "Account Number is not Found. Please Enter another one: ";
            AccountNumber = clsInputValidation::ReadString();
        }
        return AccountNumber;
    }
public:
    static void ShowTransferScreen()
    {
        
        clsBankClient SourceClient = clsBankClient::Find(ReadAccountNumber("From"));
        _PrintClientCard(SourceClient);
        
        clsBankClient DestinationClient = clsBankClient::Find(ReadAccountNumber("To"));
        _PrintClientCard(DestinationClient);
        double Amount = _ReadAmount(SourceClient);
        char Confirm;
        std::cout << "Are you sure you want to perform this operation? Y/N: ";
        std::cin >> Confirm;
        if (std::tolower(Confirm) == 'y')
        {
            if (SourceClient.Transfer(Amount, DestinationClient,CurrentUser.UserName()))
            {
                cout << "\nTransfer done successfully\n";
            }
            else
            {
                cout << "\nTransfer Failed \n";
            }
        }
        _PrintClientCard(SourceClient);
        _PrintClientCard(DestinationClient);
    }
};
