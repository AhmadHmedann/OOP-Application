#pragma once
#include <iostream>
#include <iomanip>
#include <limits>
#include "clsScreen.h"
#include "clsInputValidation.h"
#include "clsDepositScreen.h"
#include "clsWithdrawScreen.h"
#include "clsTotalBalanceScreen.h"
#include "clsTransferScreen.h"
#include "clsTransferLogScreen.h"

class clsTransactionScreen : protected clsScreen
{
    enum enTransactionsMenuOptions
    {
        eDeposit = 1,
        eWithdraw = 2,
        eShowTotalBalance = 3,
        eTransfer = 4,
        eTransferLog = 5,
        eShowMainMenu = 6,
    };
    static int _ReadTransactionMenuOption()
    {
        std::cout << std::setw(36) << std::left << "" << "Choose what  you want to do [1 to 6]: ";
        int choose = clsInputValidation::ReadIntNumberBetween(1, 6, "Enter Number Between 1 to 6? ");
        return choose;
    }

    static void _ShowDepositScreen()
    {
        clsDepositScreen::ShowDepositScreen();
    }

    static void _ShowWithdrawScreen()
    {
        clsWithdrawScreen::ShowWithdrawScreen();
    }

    static void _ShowTotalBalancesScreen()
    {
        clsTotalBalanceScreen::ShowTotalBalances();
    }
    static void _ShowTransferScreen()
    {
        clsTransferScreen::ShowTransferScreen();
    }
    static void _ShowTransferLogScreen()
    {
       clsTransferLogScreen::ShowTransferLogScreen();
    }
    static void _GoBackToTransactionsMenu()
    {

        std::cout << std::setw(37) << std::left << "" << "\n\tPress any key to go back to Transaction Menu...\n";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin.get();
    }
    static void _ClearScreen()
    {
        system("clear");
    }
    static void _PerformTransactionMenu(enTransactionsMenuOptions Option)
    {
        switch (Option)
        {
        case enTransactionsMenuOptions::eDeposit:
        {
            _ClearScreen();
            _ShowDepositScreen();
            _GoBackToTransactionsMenu();
            break;
        }
        case enTransactionsMenuOptions::eWithdraw:
        {
            _ClearScreen();
            _ShowWithdrawScreen();
            _GoBackToTransactionsMenu();
            break;
        }
        case enTransactionsMenuOptions::eShowTotalBalance:
        {
            _ClearScreen();
            _ShowTotalBalancesScreen();
            _GoBackToTransactionsMenu();
            break;
        }
        case enTransactionsMenuOptions::eTransfer:
        {
            _ClearScreen();
            _ShowTransferScreen();
            _GoBackToMainMenu();
            break;
        }
        case enTransactionsMenuOptions::eTransferLog:
        {
            _ClearScreen();
            _ShowTransferLogScreen();
            _GoBackToMainMenu();
            break;
        }
        case enTransactionsMenuOptions::eShowMainMenu:
        {
            break;
        }
        }
    }

public:
    static void ShowTransactionsMenu()
    {
        if (!CheckAccessRight(clsUser::enPermissions::pTransaction))
        {
            _GoBackToMainMenu();
            return;
        }
        enTransactionsMenuOptions Option;
        do
        {
            _ClearScreen();
            _DrawScreenHeader("\t  Transactions Screen");

            std::cout << std::setw(37) << std::left << "" << "===========================================\n";
            std::cout << std::setw(37) << std::left << "" << "\t\t  Transactions Menu\n";
            std::cout << std::setw(37) << std::left << "" << "===========================================\n";
            std::cout << std::setw(37) << std::left << "" << "\t[1] Deposit.\n";
            std::cout << std::setw(37) << std::left << "" << "\t[2] Withdraw.\n";
            std::cout << std::setw(37) << std::left << "" << "\t[3] Total Balances.\n";
            std::cout << std::setw(37) << std::left << "" << "\t[4] Transfer.\n";
            std::cout << std::setw(37) << std::left << "" << "\t[5] Transfer Log.\n";
            std::cout << std::setw(37) << std::left << "" << "\t[6] Main Menu.\n";
            std::cout << std::setw(37) << std::left << "" << "===========================================\n";

            Option = (enTransactionsMenuOptions)_ReadTransactionMenuOption();
            _PerformTransactionMenu(Option);
        } while (Option != enTransactionsMenuOptions::eShowMainMenu);
    }
};
