#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include "Lib/clsString.h"

class clsCurrency
{

private:
    enum enMode
    {
        emptyMode = 0,
        UpdateMode = 1,
    };
    enMode _Mode;
    std::string _Country;
    std::string _CurrencyCode;
    std::string _CurrencyName;
    float _Rate;

    static clsCurrency GetEmptyCurrencyObject()
    {
        return clsCurrency(enMode::emptyMode, "", "", "", 0);
    }
    static std::string _ConvertCurrencyObjectToLine(const clsCurrency &Currency, const std::string &Separator = "#//#")
    {
        return Currency.Country() + Separator + Currency.CurrencyCode() + Separator + Currency.CurrencyName() + Separator + std::to_string(Currency.Rate());
    }
    static clsCurrency _ConvertDataLineTocurrencyObject(const std::string &DataLine, const std::string &Separator = "#//#")
    {
        std::vector<std::string> vString = clsString::Split(DataLine,Separator);

        if (vString.size() != 4)
        {
            //must send an error in the future I will work in error handling
            // std::cerr << "\nInvalid currency record format:\n";
            // std::cerr << DataLine << "\n";
            return GetEmptyCurrencyObject();
        }
        return clsCurrency(enMode::UpdateMode, vString[0], vString[1], vString[2], std::stof(vString[3]));
    }

    static void _SaveCurrencyToFile(std::vector<clsCurrency> vCurrencies)
    {
        std::fstream MyFile;
        MyFile.open("data/Currencies.txt", std::ios::out);
        if (MyFile.is_open())
        {
            for (const clsCurrency C : vCurrencies)
            {
                MyFile << _ConvertCurrencyObjectToLine(C) << std::endl;
            }
            MyFile.close();
        }
    }
    static std::vector<clsCurrency> _LoadCurrenciesFromFile()
    {
        std::vector<clsCurrency> vCurrencies;
        std::fstream MyFile;
        MyFile.open("data/Currencies.txt", std::ios::in);
        if (MyFile.is_open())
        {
            std::string Line;
            while (getline(MyFile, Line))
            {
                vCurrencies.push_back(_ConvertDataLineTocurrencyObject(Line));
            }
            MyFile.close();
        }
        return vCurrencies;
    }

    void _Update()
    {
        std::vector<clsCurrency> vCurrencies = _LoadCurrenciesFromFile();

        for (clsCurrency &C : vCurrencies)
        {
            if (C.CurrencyCode() == _CurrencyCode)
            {
                C = *this;
                break;
            }
        }
        _SaveCurrencyToFile(vCurrencies);
    }

public:
    clsCurrency(enMode Mode, std::string Country, std::string CurrencyCode, std::string CurrencyName, float Rate)
    {
        _Mode = Mode;
        _Country = Country;
        _CurrencyCode = CurrencyCode;
        _CurrencyName = CurrencyName;
        _Rate = Rate;
    }
    bool IsEmpty()
    {
        return (_Mode == enMode::emptyMode);
    }
    std::string Country() const
    {
        return _Country;
    }
    std::string CurrencyCode() const
    {
        return _CurrencyCode;
    }
    std::string CurrencyName() const
    {
        return _CurrencyName;
    }

    float Rate() const
    {
        return _Rate;
    }

    void UpdateRate(float NewRate)
    {
        _Rate = NewRate;
        _Update();
    }
    static clsCurrency FindCurrencyByCountry(std::string Country)
    {
        Country = clsString::ToUpper(Country);
        std::fstream MyFile;
        MyFile.open("data/Currencies.txt", std::ios::in);
        if (MyFile.is_open())
        {
            std::string Line;
            while (getline(MyFile, Line))
            {
                clsCurrency currency = _ConvertDataLineTocurrencyObject(Line);
                if (clsString::ToUpper(currency.Country()) == Country)
                {
                    MyFile.close();
                    return currency;
                }
            }
            MyFile.close();
        }
        return GetEmptyCurrencyObject();
    }
    static clsCurrency FindCurrencyByCurrencyCode(std::string CurrencyCode)
    {
        CurrencyCode = clsString::ToUpper(CurrencyCode);
        std::fstream MyFile;
        MyFile.open("data/Currencies.txt", std::ios::in);
        if (MyFile.is_open())
        {
            std::string Line;
            while (getline(MyFile, Line))
            {
                clsCurrency currency = _ConvertDataLineTocurrencyObject(Line);
                if (currency.CurrencyCode() == CurrencyCode)
                {
                    MyFile.close();
                    return currency;
                }
            }
            MyFile.close();
        }
        return GetEmptyCurrencyObject();
    }
    static bool IsCurrencyExist(std::string CurrencyCode)
    {
        clsCurrency Currency = FindCurrencyByCurrencyCode(CurrencyCode);
        return(!Currency.IsEmpty());
    }
    static std::vector<clsCurrency> GetCurrenciesList()
    {

        return _LoadCurrenciesFromFile();
    }

    float ConvertToUSD(float Amount)
    {
        return (float)(Amount / Rate());
    }

    float ConvertToOtherCurrency(float Amount, const clsCurrency &Currency2)
    {
        float AmountInUSD = ConvertToUSD(Amount);

        if (Currency2.CurrencyCode() == "USD")
        {
            return AmountInUSD;
        }

        return (float)(AmountInUSD * Currency2.Rate());
    }
};