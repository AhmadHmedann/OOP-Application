#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "Lib/clsString.h"
#include "Core/clsPerson.h"
#include "Lib/clsDate.h"
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
        MyFile.open("data/HmedanBank.txt", std::ios::in);
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
        MyFile.open("data/HmedanBank.txt", std::ios::out);
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
        MyFile.open("data/HmedanBank.txt", std::ios::out | std::ios::app);
        if (MyFile.is_open())
        {
            MyFile << Line << std::endl;
        }

        MyFile.close();
    }
    std::string _PrepareTransferLog(const clsBankClient &DestinationClient, const double &Amount, std::string UserName, std::string Separator = "#//#")
    {
        return clsDate::GetSystemDateTimeString() + Separator + _AccountNumber + Separator + DestinationClient.AccountNumber() + Separator + std::to_string(Amount) + Separator + std::to_string(_AccountBalance) + Separator + std::to_string(DestinationClient.AccountBalance()) + Separator + UserName;
    }

    void _RegisterTransferLog(const clsBankClient &DestinationClient, const double &Amount, std::string UserName)
    {
        std::fstream MyFile;
        std::string DataLine = _PrepareTransferLog(DestinationClient, Amount, UserName);
        MyFile.open("data/TransferLog.txt", std::ios::out | std::ios::app);
        if (MyFile.is_open())
        {
            MyFile << DataLine << std::endl;
            MyFile.close();
        }
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
    std::string AccountNumber() const
    {
        return _AccountNumber;
    }
    void SetPinCode(std::string PinCode)
    {
        _PinCode = PinCode;
    }
    std::string PinCode() const
    {
        return _PinCode;
    }
    void SetAccountBalance(float AccountBalance)
    {
        _AccountBalance = AccountBalance;
    }
    float AccountBalance() const
    {
        return _AccountBalance;
    }
    // No UI inside My object
    //  void Print()
    //  {
    //      std::cout << "\nClient Card:";
    //      std::cout << "\n_______________________________________";
    //      std::cout << "\nFirstName   : " << FirstName();
    //      std::cout << "\nLastName    : " << LastName();
    //      std::cout << "\nFull Name   : " << FullName();
    //      std::cout << "\nEmail       : " << Email();
    //      std::cout << "\nPhone       : " << Phone();
    //      std::cout << "\nAcc. Number : " << _AccountNumber;
    //      std::cout << "\nPinCode     : " << _PinCode;
    //      std::cout << "\nBalance     : " << _AccountBalance;
    //      std::cout << "\n_______________________________________\n";
    //  }

    static clsBankClient Find(std::string AccountNumber)
    {
        std::vector<clsBankClient> vClients;
        std::fstream MyFile;
        MyFile.open("data/HmedanBank.txt", std::ios::in);

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
        MyFile.open("data/HmedanBank.txt", std::ios::in);

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

        for (clsBankClient &C : vClients)
        {
            if (C.AccountNumber() == _AccountNumber)
            {
                C._MarkToDelete = true;
                break;
            }
        }
        _SaveClientsDataToFile(vClients);
        *this = _GetEmptyClientObject();
        return true;
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

    void Deposit(double amount)
    {
        _AccountBalance += amount;
        Save();
    }
    bool Withdraw(double amount)
    {
        if (amount > _AccountBalance)
        {
            return false;
        }
        _AccountBalance -= amount;
        Save();
        return true;
    }
    bool Transfer(const double &Amount, clsBankClient &DestinationClient, std::string UserName)
    {
        if (Amount > _AccountBalance)
        {
            return false;
        }
        this->Withdraw(Amount);
        DestinationClient.Deposit(Amount);
        _RegisterTransferLog(DestinationClient, Amount, UserName);
        return true;
    }
    struct stTransferLogRecord
    {
        std::string DateTime;
        std::string SourceAccountNumber;
        std::string DestinationAccountNumber;
        double Amount;
        double SourceBalance;
        double DestinationBalance;
        std::string UserName;
    };
    static stTransferLogRecord _ConvertLineDataTostTransferLogRecord(const std::string &Line, std::string Separator = "#//#")
    {
        std::vector<std::string> vString = clsString::Split(Line, Separator);
        if (vString.size() != 7)
        {
            std::cout << "Error, ..\n\n";
        }
        stTransferLogRecord TransferLog;
        TransferLog.DateTime = vString[0];
        TransferLog.SourceAccountNumber = vString[1];
        TransferLog.DestinationAccountNumber = vString[2];
        TransferLog.Amount = std::stod(vString[3]);
        TransferLog.SourceBalance = std::stod(vString[4]);
        TransferLog.DestinationBalance = std::stod(vString[5]);
        TransferLog.UserName = vString[6];
        return TransferLog;
    }
    static std::vector<stTransferLogRecord> GetTransferLogList()
    {
        std::vector<stTransferLogRecord> vTransfersLog;
        std::fstream MyFile;
        MyFile.open("data/TransferLog.txt", std::ios::in);
        if (MyFile.is_open())
        {
            std::string Line;
            while (getline(MyFile, Line))
            {
                vTransfersLog.push_back(_ConvertLineDataTostTransferLogRecord(Line));
            }
            MyFile.close();
        }
        return vTransfersLog;
    }
};