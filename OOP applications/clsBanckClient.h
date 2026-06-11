#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "clsString.h"
#include "clsPerson.h"
 class clsBankClient : public clsPerson
{
private:
    enum enMode
    {
        EmptyMode = 0,
        UpdateMode = 1,
        AddNewClient = 2,
    };
    enMode _Mode;
    std::string _AccountNumber;
    std::string _PinCode;
    float _AccountBalance;

    static clsBankClient _ConvertLineToClientObject(std::string line, std::string Separator = "#//#")
    {
        std::vector<std::string> vString = clsString::Split(line, Separator);
        return clsBankClient(enMode::UpdateMode, vString[0], vString[1], vString[2], vString[3], vString[4], vString[5], std::stod(vString[6]));
    }
    static clsBankClient _GetEmptyClientObject()
    {
        return clsBankClient(enMode::EmptyMode, "", "", "", "", "", "", 0);
    }
    static std::string _ConvertClientObjectToLine(clsBankClient Client, std::string Separator = "#//#")
    {
        return Client.FirstName() + Separator +
               Client.LastName() + Separator +
               Client.Email() + Separator +
               Client.Phone() + Separator +
               Client.AccountNumber() + Separator +
               Client.PinCode() + Separator + to_string(Client.AccountBalance());
    }

    static std::vector<clsBankClient> _LoadClientsDataFromFile()
    {
        std::vector<clsBankClient> vClients;
        std::fstream MyFile;
        MyFile.open("HmedanBank.txt", std::ios::in);
        if (MyFile.is_open())
        {
            std::string line;
            while (getline(MyFile, line))
            {
                clsBankClient client = _ConvertLineToClientObject(line);
                vClients.push_back(client);
            }
        }
        return vClients;
        MyFile.close();
    }
    static void _SaveClientsDataToFile(std::vector<clsBankClient> vClients)
    {
        std::fstream MyFile;
        MyFile.open("HmedanBank.txt", std::ios::out);
        if (MyFile.is_open())
        {
            std::string line;
            for (const clsBankClient &C : vClients)
            {
                MyFile << _ConvertClientObjectToLine(C) << std::endl;
            }
            MyFile.close();
        }
        MyFile.close();
    }


public:
    clsBankClient(enMode Mode, std::string FirstName, std::string LastName, std::string Email, std::string Phone, std::string AccountNumber, std::string PinCode, float AccountBalance)
        : clsPerson(FirstName, LastName, Email, Phone)
    {
        _Mode = Mode;
        _AccountNumber = AccountNumber;
        _PinCode = PinCode;
        _AccountBalance = AccountBalance;
    }

    bool IsEmpty()
    {
        return _Mode == enMode::EmptyMode;
    }
    std::string AccountNumber()
    {
        return _AccountNumber;
    }
    void SetPinCode(std::string PinCode)
    {
        _PinCode = PinCode;
    }
    std::string PinCode()
    {
        return _PinCode;
    }
    void SetAccountBalance(float AccountBalance)
    {
        _AccountBalance = AccountBalance;
    }
    float AccountBalance()
    {
        return _AccountBalance;
    }
    void Print()
    {
        std::cout << "\nClient Card:";
        std::cout << "\n_______________________________________";
        std::cout << "\nFirstName   : " << FirstName();
        std::cout << "\nLastName    : " << LastName();
        std::cout << "\nFull Name   : " << FullName();
        std::cout << "\nEmail       : " << Email();
        std::cout << "\nPhone       : " << Phone();
        std::cout << "\nAcc. Number : " << _AccountNumber;
        std::cout << "\nPinCode     : " << _PinCode;
        std::cout << "\nBalance     : " << _AccountBalance;
        std::cout << "\n_______________________________________\n";
    }

    static clsBankClient Find(std::string AccountNumber)
    {
        std::vector<clsBankClient> vClients;
        std::fstream MyFile;
        MyFile.open("HmedanBank.txt", std::ios::in);

        if (MyFile.is_open())
        {
            std::string line;
            while (getline(MyFile, line))
            {
                clsBankClient client = _ConvertLineToClientObject(line);
                if (client.AccountNumber() == AccountNumber)
                {
                    MyFile.close();
                    return client;
                }
              
            }

            MyFile.close();
        }
        return _GetEmptyClientObject();
    }
    static clsBankClient Find(std::string AccountNumber, std::string PinCode)
    {
        std::vector<clsBankClient> vClients;
        std::fstream MyFile;
        MyFile.open("HmedanBank.txt", std::ios::in);

        if (MyFile.is_open())
        {
            std::string line;
            while (getline(MyFile, line))
            {
                clsBankClient client = _ConvertLineToClientObject(line);
                if (client.AccountNumber() == AccountNumber && client.PinCode() == PinCode)
                {
                    MyFile.close();
                    return client;
                }
               
            }

            MyFile.close();
        }
        return _GetEmptyClientObject();
    }
    static bool IsClientExist(std::string AccountNumber)
    {
        clsBankClient client = Find(AccountNumber);
        return !client.IsEmpty();
    }
    
 
};