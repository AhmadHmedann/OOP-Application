#pragma once
#include <iostream>
#include "clsDate.h"
// std::string;
//     std::cout;
//         std::endl;

    class clsUtilities
{

public:
    enum enCharType
    {
        SmallLetter = 1,
        CapitalLetter = 2,
        Digit = 3,
        MixChar = 4,
        SpecialCharacter = 5,
    };
    static void Srand()
    {
        srand((unsigned)time(NULL));
    }
    static int RandomNumber(int From, int To)
    {
        return (rand() % (To - From + 1)) + From;
    }
    static char GetRandomCharacters(enCharType CharType)
    {
        switch (CharType)
        {
        case enCharType::SmallLetter:
            return char(RandomNumber(97, 122));
            break;
        case enCharType::CapitalLetter:
            return char(RandomNumber(65, 90));
        case enCharType::Digit:
            return char(RandomNumber(48, 57));
        case enCharType::SpecialCharacter:
            return char(RandomNumber(32, 47));
        case enCharType::MixChar:
            return GetRandomCharacters((enCharType)RandomNumber(1, 3));
        default:
            return char(RandomNumber(65, 90));
            break;
        }
    }
    static string GenerateRandomWord(enCharType CharType, int Length)

    {
        string Word = "";
        for (int i = 0; i < Length; i++)
        {
            Word += GetRandomCharacters(CharType);
        }
        return Word;
    }
    static string GenerateKey(enCharType CharType)
    {
        string key = "";
        for (int i = 0; i < 4; i++)
        {
            key += GenerateRandomWord(CharType, 4) + "-";
        }
        key.pop_back();
        return key;
    }
    static void GenerateKeys(int length, enCharType CharType)
    {
        for (int i = 0; i < length; i++)
        {
            cout << "Key [" << i + 1 << "]: " << GenerateKey(CharType) << endl;
        }
    }
    static void Swap(int &num1, int &num2)
    {
        int temp = num1;
        num1 = num2;
        num2 = temp;
    }
    static void Swap(bool &A, bool &B)
    {
        bool Temp;

        Temp = A;
        A = B;
        B = Temp;
    }

    static void Swap(char &A, char &B)
    {
        char Temp;

        Temp = A;
        A = B;
        B = Temp;
    }
    static void Swap(double &num1, double &num2)
    {
        double temp = num1;
        num1 = num2;
        num2 = temp;
    }
    static void Swap(string &s1, string &s2)
    {
        string temp = s1;
        s1 = s2;
        s2 = temp;
    }
    static void Swap(clsDate &date1, clsDate &date2)
    {
        clsDate tempDate = date1;
        date1 = date2;
        date2 = tempDate;
    }
    static void ShuffleArray(int arr[], int length)
    {
        for (int i = 0; i < length; i++)
        {
            Swap(arr[RandomNumber(0, length - 1)], arr[RandomNumber(0, length - 1)]);
        }
    }
    static void ShuffleArray(string arr[], int length)
    {
        for (int i = 0; i < length; i++)
        {
            Swap(arr[RandomNumber(0, length - 1)], arr[RandomNumber(0, length - 1)]);
        }
    }
    static void FillArrayWithRandomNumbers(int arr[], int length, int from, int to)
    {
        for (int i = 0; i < length; i++)
        {
            arr[i] = RandomNumber(from, to);
        }
    }
    static void FillArrayWithRandomWords(string arr[], int length, enCharType CharType, int WordLength)
    {
        for (int i = 0; i < length; i++)
        {
            arr[i] = GenerateRandomWord(CharType, WordLength);
        }
    }
    static void FillArrayWithRandomKeys(string arr[], int length, enCharType CharType)
    {
        for (int i = 0; i < length; i++)
        {
            arr[i] = GenerateKey(CharType);
        }
    }
    static string Tabs(short NumberOfTabs)
    {
        string t = "";

        for (int i = 1; i < NumberOfTabs; i++)
        {
            t = t + "\t";
            cout << t;
        }
        return t;
    }
    static string EncryptText(string Text, short EncryptionKey = 2)
    {

        for (int i = 0; i <= Text.length(); i++)
        {

            Text[i] = char((int)Text[i] + EncryptionKey);
        }

        return Text;
    }

    static string DecryptText(string Text, short EncryptionKey = 2)
    {

        for (int i = 0; i <= Text.length(); i++)
        {

            Text[i] = char((int)Text[i] - EncryptionKey);
        }
        return Text;
    }
      static std::string NumberToText(int Number)
    {

        if (Number == 0)
        {
            return "";
        }

        if (Number >= 1 && Number <= 19)
        {
            std::string arr[] = {"", "One", "Two", "Three", "Four", "Five", "Six", "Seven",
                                 "Eight", "Nine", "Ten", "Eleven", "Twelve", "Thirteen", "Fourteen",
                                 "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen"};

            return arr[Number] + " ";
        }

        if (Number >= 20 && Number <= 99)
        {
            std::string arr[] = {"", "", "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety"};
            return arr[Number / 10] + " " + NumberToText(Number % 10);
        }

        if (Number >= 100 && Number <= 199)
        {
            return "One Hundred " + NumberToText(Number % 100);
        }

        if (Number >= 200 && Number <= 999)
        {
            return NumberToText(Number / 100) + "Hundreds " + NumberToText(Number % 100);
        }

        if (Number >= 1000 && Number <= 1999)
        {
            return "One Thousand " + NumberToText(Number % 1000);
        }

        if (Number >= 2000 && Number <= 999999)
        {
            return NumberToText(Number / 1000) + "Thousands " + NumberToText(Number % 1000);
        }

        if (Number >= 1000000 && Number <= 1999999)
        {
            return "One Million " + NumberToText(Number % 1000000);
        }

        if (Number >= 2000000 && Number <= 999999999)
        {
            return NumberToText(Number / 1000000) + "Millions " + NumberToText(Number % 1000000);
        }

        if (Number >= 1000000000 && Number <= 1999999999)
        {
            return "One Billion " + NumberToText(Number % 1000000000);
        }
        else
        {
            return NumberToText(Number / 1000000000) + "Billions " + NumberToText(Number % 1000000000);
        }
    }
};
