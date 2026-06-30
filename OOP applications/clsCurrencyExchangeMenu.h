#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsCurrenciesLisScreen.h"
#include "clsFindCurrencyScreen.h"
#include "clsUpdateCurrencyRateScreen.h"
#include "clsCurrencyCalculaterScreen.h"

class clsCurrencyExchangeMenuScreen : protected clsScreen
{
private:
    enum enCurrencyExchangeOption
    {
        eListCurrency = 1,
        eFindCurrency = 2,
        eUpdateRate = 3,
        eCurrencyCalculator = 4,
        eMainMenu = 5, // it's may case bug
    };
    static int _ReadCurrencyExchangeOption()
    {
        std::cout << std::setw(37) << std::left << "" << "Choose what do you want to do [1 to 5]: ";
        int choice = clsInputValidation::ReadIntNumberBetween(1, 5, "Enter Number between 1 to 5? ");

        return choice;
    }
    static void _ClearScreen()
    {
        system("clear");
    }
    static void _GoBackToMainMenu()
    {

        std::cout << std::setw(37) << std::left << "" << "\n\tPress any key to go back to Main Menu...\n";
        std::cin.get();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    static void _ShowListScreen()
    {
        clsCurrenciesListScreen::ShowCurrenciesListScreen();
    }
    static void _ShowFindCurrencyScreen()
    {
        clsFindCurrencyScreen::ShowFindCurrencyScreen();
    }
    static void _ShowUpdateRateScreen()
    {
        clsUpdateCurrencyRateScreen::ShowUpdateCurrencyRateScreen();
    }
    static void _ShowCurrencyCalculator()
    {
        clsCurrencyCalculatorScreen::ShowCurrencyCalculatorScreen();
    }
    static void PerformCurrencyExchangeOption(enCurrencyExchangeOption Option)

    {
        switch (Option)
        {
        case enCurrencyExchangeOption::eListCurrency:
        {
            _ClearScreen();
            _ShowListScreen();
            _GoBackToMainMenu();
            break;
        }
        case enCurrencyExchangeOption::eFindCurrency:
        {
            _ClearScreen();
            _ShowFindCurrencyScreen();
            _GoBackToMainMenu();
            break;
        }
        case enCurrencyExchangeOption::eUpdateRate:
        {
            _ClearScreen();
            _ShowUpdateRateScreen();
            _GoBackToMainMenu();
            break;
        }
        case enCurrencyExchangeOption::eCurrencyCalculator:
        {
            _ClearScreen();
            _ShowCurrencyCalculator();
            _GoBackToMainMenu();
            break;
        }
        case enCurrencyExchangeOption::eMainMenu:
        {
            break;
        }
        default:
            break;
        }
    }

public:
    static void ShowCurrencyExchangeMenu()
    {
        enCurrencyExchangeOption Option;
        do
        {
            _ClearScreen();
            _DrawScreenHeader("    Currency Exchange Main Screen");

            std::cout << std::setw(37) << std::left << "" << "===========================================\n";
            std::cout << std::setw(37) << std::left << "" << "\t\t  Currency Exchange Menu\n";
            std::cout << std::setw(37) << std::left << "" << "===========================================\n";
            std::cout << std::setw(37) << std::left << "" << "\t[1] List Currencies.\n";
            std::cout << std::setw(37) << std::left << "" << "\t[2] Find Currency.\n";
            std::cout << std::setw(37) << std::left << "" << "\t[3] Update Rate.\n";
            std::cout << std::setw(37) << std::left << "" << "\t[4] Currency Calculator.\n";
            std::cout << std::setw(37) << std::left << "" << "\t[5] Main Menu.\n";
            std::cout << std::setw(37) << std::left << "" << "===========================================\n";

            Option = (enCurrencyExchangeOption)_ReadCurrencyExchangeOption();
            PerformCurrencyExchangeOption(Option);
        } while (Option != enCurrencyExchangeOption::eMainMenu);
    }
};