#pragma once
#include <iostream>
#include "Screens/clsScreen.h"
#include "Core/clsCurrency.h"
#include "Lib/clsInputValidation.h"

class clsUpdateCurrencyRateScreen : protected clsScreen

{
private:
    static float _ReadRate()
    {
        std::cout << "\nEnter New Rate: ";
        float NewRate = 0;

        NewRate = clsInputValidation::ReadFloatNumber();
        return NewRate;
    }

    static void _PrintCurrency(clsCurrency Currency)
    {
        std::cout << "\nCurrency Card:\n";
        std::cout << "_____________________________\n";
        std::cout << "\nCountry    : " << Currency.Country();
        std::cout << "\nCode       : " << Currency.CurrencyCode();
        std::cout << "\nName       : " << Currency.CurrencyName();
        std::cout << "\nRate(1$) = : " << Currency.Rate();

        std::cout << "\n_____________________________\n";
    }

public:
    static void ShowUpdateCurrencyRateScreen()
    {

        _DrawScreenHeader("\tUpdate Currency Screen");

        std::string CurrencyCode = "";

        std::cout << "\nPlease Enter Currency Code: ";
        CurrencyCode = clsInputValidation::ReadString();

        while (!clsCurrency::IsCurrencyExist(CurrencyCode))
        {
            std::cout << "\nCurrency is not found, choose another one: ";
            CurrencyCode = clsInputValidation::ReadString();
        }

        clsCurrency Currency = clsCurrency::FindCurrencyByCurrencyCode(CurrencyCode);
        _PrintCurrency(Currency);

        std::cout << "\nAre you sure you want to update the rate of this Currency y/n? ";

        char Answer = 'n';
        std::cin >> Answer;

        if (Answer == 'y' || Answer == 'Y')
        {

            std::cout << "\n\nUpdate Currency Rate:";
            std::cout << "\n____________________\n";

            Currency.UpdateRate(_ReadRate());

            std::cout << "\nCurrency Rate Updated Successfully :-)\n";
            _PrintCurrency(Currency);
        }
    }
};
