#pragma once
#include <iostream>
#include <limits>
#include "clsDate.h"
#include "clsUtilities.h"

class clsInputValidation
{
public:
    static bool IsNumberBetween(int Num, int From, int To)
    {
        return (Num >= From && Num <= To);
    }
    static bool IsNumberBetween(double Num, double From, double To)
    {
        return (Num >= From && Num <= To);
    }
    static bool IsNumberBetween(float Num, float From, float To)
    {
        return (Num >= From && Num <= To);
    }

    static int ReadIntNumber(string ErrorMessage = "Invalid Number, Enter again\n")
    {
        int num;
        while (!(cin >> num))
        {
            cin.clear(); //reset the Error flag  
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); //That removes bad input from the buffer.
            cout << ErrorMessage;
        }
        return num;
    }

    static int ReadIntNumberBetween(int From, int To, string ErrorMessage = "Number is not within range, Enter again:\n")
    {
        int num = ReadIntNumber();
        while (!(IsNumberBetween(num, From, To)))
        {
            cout << ErrorMessage;
            num = ReadIntNumber();
        }
        return num;
    }
    static double ReadDblNumber(string ErrorMessage = "Invalid Number, Enter again\n")
    {
        double Number;
        while (!(cin >> Number))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << ErrorMessage;
        }
        return Number;
    }

    static double ReadDblNumberBetween(double From, double To, string ErrorMessage = "Number is not within range, Enter again:\n")
    {
        double Number = ReadDblNumber();

        while (!IsNumberBetween(Number, From, To))
        {
            cout << ErrorMessage;
            Number = ReadDblNumber();
        }
        return Number;
    }
    static float ReadFloatNumber(string ErrorMessage = "Invalid Number, Enter again\n")
    {
        float Number;
        while (!(cin >> Number))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << ErrorMessage;
        }
        return Number;
    }
    static bool IsDateBetween(clsDate Date, clsDate DateFrom, clsDate DateTo)
    {
        if (clsDate::IsDate1AfterDate2(DateFrom, DateTo))
        {
            clsUtilities::Swap(DateFrom, DateTo);
        }
        // Date>=DateFrom and Date<=DateTo
        return !clsDate::IsDate1BeforeDate2(Date, DateFrom) &&
               !clsDate::IsDate1AfterDate2(Date, DateTo);
    }
    static bool IsValidateDate(clsDate Date)
    {
        return clsDate::IsValidDate(Date);
    }
    static std::string ReadString()
    {
        std::string s;
        
         getline(std::cin>>std::ws,s);
         return s;
    }
};