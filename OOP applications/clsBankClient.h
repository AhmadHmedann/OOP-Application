#pragma once
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
    bool _MarkToDelete = false;

    static clsBankClient _ConvertLineToClientObject(std::string line, std::string Separator = "#//#")
    {
        std::vector<std::string> vString = clsString::Split(line, Separator);
        if (vString.size() != 7)
        {
            return _GetEmptyClientObject();
        }
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
               Client.PinCode() + Separator + std::to_string(Client.AccountBalance());
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
        MyFile.close();
        return vClients;
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
                if (C._MarkToDelete == false)
                {
                    MyFile << _ConvertClientObjectToLine(C) << std::endl;
                }
            }
            MyFile.close();
        }
    }

    void _Update()
    {
        std::vector<clsBankClient> vClients = _LoadClientsDataFromFile();
        for (clsBankClient &C : vClients)
        {
            if (C.AccountNumber() == _AccountNumber)
            {
                C = *this; // Find the old client in the vector and replace it with the current updated object.
                break;
            }
        }
        _SaveClientsDataToFile(vClients);
    }
    void _AddNew()
    {
        _AddNewDataLineToFile(_ConvertClientObjectToLine(*this));
    }
    void _AddNewDataLineToFile(std::string Line)
    {
        std::fstream MyFile;
        MyFile.open("HmedanBank.txt", std::ios::out | std::ios::app);
        if (MyFile.is_open())
        {
            MyFile << Line << std::endl;
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
    //No UI inside My object
    // void Print()
    // {
    //     std::cout << "\nClient Card:";
    //     std::cout << "\n_______________________________________";
    //     std::cout << "\nFirstName   : " << FirstName();
    //     std::cout << "\nLastName    : " << LastName();
    //     std::cout << "\nFull Name   : " << FullName();
    //     std::cout << "\nEmail       : " << Email();
    //     std::cout << "\nPhone       : " << Phone();
    //     std::cout << "\nAcc. Number : " << _AccountNumber;
    //     std::cout << "\nPinCode     : " << _PinCode;
    //     std::cout << "\nBalance     : " << _AccountBalance;
    //     std::cout << "\n_______________________________________\n";
    // }

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

    enum enSaveResults
    {
        svFailedEmptyObject = 0,
        svSucceeded = 1,
        svFailedAccountNumberExists = 2,
    };

    enSaveResults Save()
    {
        switch (_Mode)
        {
        case enMode::UpdateMode:
        {
            _Update();
            return enSaveResults::svSucceeded;
        }
        case enMode::EmptyMode:
        {
            if (IsEmpty())
                return enSaveResults::svFailedEmptyObject;
        }
        case enMode::AddNewClient:
        {
            if (IsClientExist(_AccountNumber))
            {
                return enSaveResults::svFailedAccountNumberExists;
            }
            else
            {

                _AddNew();
                _Mode = enMode::UpdateMode;
                return enSaveResults::svSucceeded;
            }
            break;
        }

        default:
            return enSaveResults::svFailedEmptyObject;
        }
    }
    static clsBankClient GetAddNewClientObject(std::string AccountNumber)
    {
        return clsBankClient(enMode::AddNewClient, "", "", "", "", AccountNumber, "", 0);
    }

    bool Delete()
    {
        std::vector<clsBankClient> vClients = _LoadClientsDataFromFile();
        
        for (clsBankClient &C: vClients)
        {
            if(C.AccountNumber() == _AccountNumber)
            {
                C._MarkToDelete = true;
                break;
            }
        }
        _SaveClientsDataToFile(vClients);
        *this = _GetEmptyClientObject();
        return true ;
    }   
    static std::vector<clsBankClient> GetClientsList()
    {
        return _LoadClientsDataFromFile();
    }
    static double GetTotalBalances()
    {
        vector<clsBankClient> vClients = clsBankClient::GetClientsList();

        double TotalBalances = 0;

        for (clsBankClient &Client : vClients)
        {

            TotalBalances += Client.AccountBalance();
        }

        return TotalBalances;
    }
  
};