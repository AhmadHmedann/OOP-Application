#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"

class clsTransferLogScreen : protected clsScreen
{
private:
    static void _PrintTransferLogRecordLine(const clsBankClient::stTransferLogRecord &TransferLog)
    {
        std::cout << std::setw(8) << std::left << "" << "| " << setw(20) << std::left << TransferLog.DateTime << "| "
                  << std::setw(15) << std::left << TransferLog.SourceAccountNumber << "| " << std::setw(15) << std::left << TransferLog.DestinationAccountNumber << "| "
                  << std::setw(15) << std::left << TransferLog.Amount << "| " << std::setw(15) << std::left << TransferLog.SourceBalance << "| "
                  << std::setw(15) << std::left << TransferLog.DestinationBalance << "| " << std::setw(15) << std::left << TransferLog.UserName << "\n";
    }

public:
    static void ShowTransferLogScreen()
    {
        std::vector<clsBankClient::stTransferLogRecord> vTransfersLog = clsBankClient::GetTransferLogList();
        std::string Title = "\t Transfer Log List Screen";
        std::string SubTitle = "\t (" + std::to_string(vTransfersLog.size()) + ") Record(s).";
        _DrawScreenHeader(Title, SubTitle);
        std::cout << "\n"
                  << std::setw(8) << std::left << "" << "______________________________________________________________________________________________________________________\n";
        std::cout << std::setw(8) << std::left << "" << "| " << setw(20) << std::left << "Date/Time" << "| " << setw(15) << std::left << "S.Acct"
                  << "| " << setw(15) << std::left << "D.Acct" << "| " << setw(15) << std::left << "Amount" << "| " << setw(15) << std::left << "S.Balance"
                  << "| " << setw(15) << std::left << "D.Balance" << "| " << setw(15) << std::left << "User" << std::endl;
        std::cout << std::setw(8) << std::left << "" << "______________________________________________________________________________________________________________________\n";
        if (vTransfersLog.size() == 0)
        {
            std::cout << "\t\t\t\tNo Transfers Available In the System!";
        }
        else
        {
            for (const clsBankClient::stTransferLogRecord &TL : vTransfersLog)
            {
                _PrintTransferLogRecordLine(TL);
            }
        }
        std::cout << std::setw(8) << std::left << "" << "______________________________________________________________________________________________________________________\n";
    }
};