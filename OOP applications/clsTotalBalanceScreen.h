
#pragma once
#include <iostream>
#include <iomanip>
#include "clsBankClient.h"
#include "clsScreen.h"
#include "clsInputValidation.h"

class clsTotalBalanceScreen : protected clsScreen
{
    static void _PrintClientRecordBalanceLine(clsBankClient Client)
    {

        std::cout << "| " << std::setw(15) << std::left << Client.AccountNumber();
        std::cout << "| " << std::setw(40) << std::left << Client.FullName();
        std::cout << "| " << std::setw(12) << std::left << Client.AccountBalance();
    }

public:
    static void ShowTotalBalances()
    {

        std::vector<clsBankClient> vClients = clsBankClient::GetClientsList();
        std::string Title = "\t Balance list Screen";
        std::string SubTitle = "\t   (" + to_string(vClients.size()) + ") Client (s).\n";
        _DrawScreenHeader(Title, SubTitle);

        std::cout << "\n_______________________________________________________";
        cout << "_________________________________________\n"
             << std::endl;

        std::cout << "| " << left << setw(15) << "Account Number";
        std::cout << "| " << left << setw(40) << "Client Name";
        std::cout << "| " << left << setw(12) << "Balance";
        std::cout << "\n_______________________________________________________";
        std::cout << "_________________________________________\n"
                  << std::endl;

        double TotalBalances = clsBankClient::GetTotalBalances();

        if (vClients.size() == 0)
            cout << "\t\t\t\tNo Clients Available In the System!";
        else

            for (clsBankClient &Client : vClients)
            {
                _PrintClientRecordBalanceLine(Client);
                std::cout << std::endl;
            }

        std::cout << "\n_______________________________________________________";
        std::cout << "_________________________________________\n"
                  << endl;
        std::cout << "\t\t\t\t\t   Total Balances = " << TotalBalances << endl;
        std::cout << "\t\t\t\t\t   ( " << clsUtilities::NumberToText(TotalBalances) << ")";
    }
};