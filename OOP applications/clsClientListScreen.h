#pragma once
#include <iostream>
#include "clsBankClient.h"
#include "clsScreen.h"
#include <iomanip>

class clsClientListScreen : protected clsScreen
{
private:
    static void PrintClientRecordLine(clsBankClient Client)
    {
        std::cout << std::setw(8) << std::left << "" << "| " << std::setw(15) << std::left << Client.AccountNumber()
                  << "| " << std::setw(20) << std::left << Client.FullName()
                  << "| " << std::setw(12) << std::left << Client.Phone()
                  << "| " << std::setw(20) << std::left << Client.Email()
                  << "| " << std::setw(10) << std::left << Client.PinCode()
                  << "| " << std::setw(12) << std::left << Client.AccountBalance();
    }

public:
    static void ShowClientList()
    {
        std::vector<clsBankClient> vClients = clsBankClient::GetClientsList();
        std::string Title = "\tClient List Screen";
        std::string SubTitle = "\t   (" + to_string(vClients.size()) + ") Client (s).\n";
        _DrawScreenHeader(Title, SubTitle);
        std::cout<< "\n\t____________________________________________________________________________________________________________________\n";
        std::cout<<setw(8)<< std::left<<"" << "| " << std::setw(15) << std::left << "Account Number"
                  << "| " << std::setw(20) << std::left << "Full Name"
                  << "| " << std::setw(12) << std::left << "Phone"
                  << "| " << std::setw(20) << std::left << "Email"
                  << "| " << std::setw(10) << std::left << "PinCode"
                  << "| " << std::setw(12) << std::left << "Balance";
        std::cout << std::setw(8) << "" << std::left << "\n\t____________________________________________________________________________________________________________________\n\n";

        if (vClients.size() == 0)
        {
            std::cout << "\t\t\t\tNo Clients Available In the System!";
        }
        else
        {

            for (const clsBankClient &c : vClients)
            {
                PrintClientRecordLine(c);
                std::cout << std::endl;
            }
            std::cout << "\n\t____________________________________________________________________________________________________________________\n";
        }
    }
};