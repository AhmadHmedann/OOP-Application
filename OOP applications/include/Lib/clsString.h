#pragma once
#include <iostream>
#include <vector>
using namespace std;

class clsString
{
private:
    string _Value;

public:
    clsString()
    {
        _Value = "";
    }
    clsString(string val)
    {
        this->_Value = val;
    }
    void SetValue(string val)
    {
        _Value = val;
    }
    string Value()
    {
        return _Value;
    }
    static void FirstLetterInEachWord(string s)
    {
        bool isFirstLetter = true;
        for (int i = 0; i < s.length(); i++)
        {
            if (isFirstLetter && (s[i] != ' '))
            {
                cout << s[i] << endl;
            }
            isFirstLetter = (s[i] == ' ' && (s[i + 1] != ' ')) ? true : false;
        }
    }
    void FirstLetterInEachWord()
    {
        FirstLetterInEachWord(_Value);
    }
    static string UpperFirstLetterInEachWord(string s)
    {
        bool isFirstLetter = true;
        for (int i = 0; i < s.length(); i++)
        {
            if (isFirstLetter && (s[i] != ' '))
            {
                s[i] = toupper(s[i]);
            }
            isFirstLetter = (s[i] == ' ' && (s[i + 1] != ' ')) ? true : false;
        }
        return s;
    }
    void UppreFirstLetterInEachWord()
    {
        _Value = UpperFirstLetterInEachWord(_Value);
    }
    static string LowerFirstLetterInEachWord(string s)
    {
        bool isFirstLetter = true;
        for (int i = 0; i < s.length(); i++)
        {
            if (isFirstLetter && (s[i] != ' '))
            {
                s[i] = tolower(s[i]);
            }
            isFirstLetter = (s[i] == ' ' && (s[i + 1] != ' ')) ? true : false;
        }
        return s;
    }
    void LowerFirstLetterInEachWord()
    {
        _Value = LowerFirstLetterInEachWord(_Value);
    }
    static string ToUpper(string s)
    {
        for (int i = 0; i < s.length(); i++)
        {
            s[i] = toupper(s[i]);
        }
        return s;
    }
    void ToUpper()
    {
        _Value = ToUpper(_Value);
    }

    static string ToLower(string s)
    {
        for (int i = 0; i < s.length(); i++)
        {
            s[i] = tolower(s[i]);
        }
        return s;
    }
    void ToLower()
    {
        _Value = ToLower(_Value);
    }
    static char InvertLetterCase(char x)
    {
        return (islower(x)) ? toupper(x) : tolower(x);
    }

    static string InvertAllLettersCase(string s)
    {
        for (int i = 0; i < s.length(); i++)
        {
            s[i] = InvertLetterCase(s[i]);
        }
        return s;
    }

    void InvertAllLettersCase()
    {
        _Value = InvertAllLettersCase(_Value);
    }
    static int CountLetter(string s, char x)
    {
        int counter = 0;
        for (int i = 0; i < s.length(); i++)
        {
            if (s[i] == x)
            {
                counter++;
            }
        }
        return counter;
    }
    int CountLetter(char x, bool Case_sensitive = true)
    {
        if (!Case_sensitive)
        {
            return CountLetter(ToLower(_Value), tolower(x));
        }
        return CountLetter(_Value, x);
    }
    static bool IsVowel(char Ch1)
    {
        Ch1 = tolower(Ch1);
        return ((Ch1 == 'a') || (Ch1 == 'e') || (Ch1 == 'i') || (Ch1 == 'o') || (Ch1 == 'u'));
    }
    static int CountVowel(string s)
    {
        int counter = 0;
        for (int i = 0; i < s.length(); i++)
        {
            if (IsVowel(s[i]))
            {
                counter++;
            }
        }
        return counter;
    }
    int CountVowel()
    {
        return CountVowel(_Value);
    }
    static void PrintVowels(string S1)
    {
        cout << "\nVowels in string are: ";
        for (short i = 0; i < S1.length(); i++)
        {
            if (IsVowel(S1[i]))
                cout << S1[i] << " ";
        }
    }
    void PrintVowels()
    {
        PrintVowels(_Value);
    }

    static vector<string> Split(string s, string delimiter = " ")
    {
        vector<string> vString;
        string word = "";
        size_t pos;
        while ((pos = s.find(delimiter)) != string::npos)
        {
            word = s.substr(0, pos);

            vString.push_back(word);

            s.erase(0, pos + delimiter.length());
        }
        if (s != "")
        {
            vString.push_back(s);
        }
        return vString;
    }

    static void PrintEachWord(string s)
    {
        vector<string> vString = Split(s);
        for (const string &word : vString)
        {
            cout << word << endl;
        }
    }
    void PrintEachWord()
    {
        PrintEachWord(_Value);
    }
    static int CountWords(string s)
    {
        vector<string> vString = Split(s);
        return vString.size();
    }
    int CountWords()
    {
        return CountWords(_Value);
    }
    static string TrimLeft(string s)
    {
        for (int i = 0; i < s.length(); i++)
        {
            if (s[i] != ' ')
            {
                return s.substr(i, s.length() - i);
            }
        }
        return "";
    }
    static string TrimRight(string s)
    {
        for (int i = s.length() - 1; i >= 0; i--)
        {
            if (s[i] != ' ')
            {
                return s.substr(0, i + 1);
            }
        }
        return "";
    }
    static string Trim(string s)
    {
        return TrimLeft(TrimRight(s));
    }
    string Trim()
    {
        return Trim(_Value);
    }

    string ReplaceWord(string s, string WordToReplace, string ReplaceTo)
    {
        size_t pos;
        while ((pos = s.find(WordToReplace)) != string::npos)
        {
            s = s.replace(pos, WordToReplace.length(), ReplaceTo);
        }
        return s;
    }
    string ReversWords(string s)
    {
        vector<string> vString = Split(s);
        // string s2 ="";
        // for( int i = vString.size()-1;i>=0;i--)
        // {
        //     s2 = s2 + vString[i] + " " ;
        // }
        // return s2;
        string s2 = "";
        vector<string>::iterator iter = vString.end();
        while (iter != vString.begin())
        {
            iter--;
            s2 = s2 + *iter + " ";
        }
        return s2.substr(0, s2.length() - 1);
    }
    int Length(string s)
    {
        return s.length();
    }
    int Length()
    {
        return _Value.length();
    }
    static string RemovePunctuations(string S1)
    {

        string S2 = "";

        for (short i = 0; i < S1.length(); i++)
        {
            if (!ispunct(S1[i]))
            {
                S2 += S1[i];
            }
        }

        return S2;
    }

    void RemovePunctuations()
    {
        _Value = RemovePunctuations(_Value);
    }
};
