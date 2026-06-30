#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsCurrency.h"
#include "clsInputValidation.h"

class clsFindCurrencyScreen : protected clsScreen
{

private:
    static void _PrintCurrency(const clsCurrency& Currency)
    {
        std::cout << "\nCurrency Card:\n";
        std::cout << "_____________________________\n";
        std::cout << "\nCountry    : " << Currency.Country();
        std::cout << "\nCode       : " << Currency.CurrencyCode();
        std::cout << "\nName       : " << Currency.CurrencyName();
        std::cout << "\nRate(1$) = : " << Currency.Rate();

        std::cout << "\n_____________________________\n";
    }

    static void _ShowResults(clsCurrency Currency)
    {
        if (!Currency.IsEmpty())
        {
            std::cout << "\nCurrency Found :-)\n";
            _PrintCurrency(Currency);
        }
        else
        {
            std::cout << "\nCurrency Was not Found :-(\n";
        }
    }

public:
    static void ShowFindCurrencyScreen()
    {

        _DrawScreenHeader("\t  Find Currency Screen");

        std::cout << "\nFind By: [1] Code or [2] Country ? ";
        short Answer = clsInputValidation::ReadIntNumberBetween(1, 2, "Find By: [1] Code or [2] Country ?");


            if (Answer == 1)
        {
            string CurrencyCode;
            std::cout << "\nPlease Enter CurrencyCode: ";
            CurrencyCode = clsInputValidation::ReadString();
            clsCurrency Currency = clsCurrency::FindCurrencyByCurrencyCode(CurrencyCode);
            _ShowResults(Currency);
        }
        else
        {
            string Country;
            std::cout << "\nPlease Enter Country Name: ";
            Country = clsInputValidation::ReadString();
            clsCurrency Currency = clsCurrency::FindCurrencyByCountry(Country);
            _ShowResults(Currency);
        }
    }
};
