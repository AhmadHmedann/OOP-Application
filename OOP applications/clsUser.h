
#pragma once
#include <iostream>
#include <iomanip>
#include <limits>
#include <vector>
#include <fstream>
#include "clsPerson.h"
#include "clsInputValidation.h"
#include "clsString.h"

class clsUser : public clsPerson
{

private:
    std::string _UserName;
    std::string _Password;
    int _Permissions;
    bool _MarkToDelete = false;
    enum enMode
    {
        EmptyMode = 0,
        UpdateMode = 1,
        AddNewUser = 2,
    };
    enMode _Mode;

    static clsUser GetEmptyUser()
    {
        return clsUser(enMode::EmptyMode, "", "", "", "", "", "", 0);
    }
    static clsUser _ConvertLineToUserObject(std::string Line, std::string Separator = "#//#")
    {
        std::vector<std::string> vString = clsString::Split(Line, Separator);
        // Adli # // #Haddad#//#Adli@Gmail.com#//#8983883#//#User1#//#1234#//#-1
        if (vString.size() != 7)
        {
            return GetEmptyUser();
        }
        return clsUser(enMode::UpdateMode, vString[0], vString[1], vString[2], vString[3], vString[4], vString[5], std::stoi(vString[6]));
    }

    static std::string _ConvertUserObjectToLine(clsUser User, std::string Separator = "#//#")
    {
        return User.FirstName() + Separator + User.LastName() + Separator + User.Email() + Separator + User.Phone() + Separator + User.UserName() + Separator + User.Password() + Separator + std::to_string(User.Permissions());
    }
    static std::vector<clsUser> _LoadUsersDataFromFile()
    {
        std::vector<clsUser> vUsers;
        std::fstream Myfile;
        Myfile.open("Users.txt", std::ios::in);
        if (Myfile.is_open())
        {
            std::string Line;
            while (getline(Myfile, Line))
            {
                vUsers.push_back(_ConvertLineToUserObject(Line));
            }
            Myfile.close();
        }
        return vUsers;
    }
    static void _SaveUsersDataToFile(std::vector<clsUser> &vUsers)
    {
        std::fstream Myfile;
        Myfile.open("Users.txt", std::ios::out);
        if (Myfile.is_open())
        {
            for (const clsUser &User : vUsers)
            {
                if (!User._MarkToDelete)
                {
                    Myfile << _ConvertUserObjectToLine(User) << std::endl;
                }
            }
            Myfile.close();
        }
    }
    void _AddNew()
    {
        _AddDataLineToFile(_ConvertUserObjectToLine(*this));
    }

    void _AddDataLineToFile(std::string Line)
    {
        std::fstream MyFile;
        MyFile.open("Users.txt", std::ios::out | std::ios::app);
        if (MyFile.is_open())
        {
            MyFile << Line << std::endl;
            MyFile.close();
        }
    }
    void _Update()
    {
        std::vector<clsUser> vUsers = _LoadUsersDataFromFile();
        for (clsUser &User : vUsers)
        {
            if (User.UserName() == _UserName)
            {
                User = *this;
                break;
            }
        }
        _SaveUsersDataToFile(vUsers);
    }

public:
    clsUser(enMode Mode, std::string FirstName, std::string LastName, std::string Email, std::string Phone, std::string UserName, std::string Password, int Permissions)
        : clsPerson(FirstName, LastName, Email, Phone)
    {
        _Mode = Mode;
        _UserName = UserName;
        _Password = Password;
        _Permissions = Permissions;
    };
    bool IsEmpty()
    {
        return (_Mode == enMode::EmptyMode);
    }

    bool MarkedForDeleted() const
    {
        return _MarkToDelete;
    }
    void SetUserName(std::string UserName)
    {
        _UserName = UserName;
    }
    std::string UserName() const
    {
        return _UserName;
    }
    void SetPassword(std::string Password)
    {
        _Password = Password;
    }
    std::string Password() const
    {
        return _Password;
    }
    void SetPermissions(int Permissions)
    {
        _Permissions = Permissions;
    }
    int Permissions() const
    {
        return _Permissions;
    }
    void SetMode(enMode Mode)
    {
        _Mode = Mode;
    }
    enMode Mode() const
    {
        return _Mode;
    }

    static clsUser Find(std::string UserName)
    {
        std::fstream MyFile;
        MyFile.open("Users.txt", std::ios::in);
        if (MyFile.is_open())
        {
            std::string line;
            while (getline(MyFile, line))
            {
                clsUser user = _ConvertLineToUserObject(line);
                if (user.UserName() == UserName)
                {
                    MyFile.close();
                    return user;
                }
            }
            MyFile.close();
        }

        return GetEmptyUser();
    }

    static clsUser Find(std::string UserName, std::string Password)
    {
        std::fstream MyFile;
        MyFile.open("Users.txt", std::ios::in);
        if (MyFile.is_open())
        {
            std::string line;
            while (getline(MyFile, line))
            {
                clsUser user = _ConvertLineToUserObject(line);
                if (user.UserName() == UserName && user.Password() == Password)
                {
                    MyFile.close();
                    return user;
                }
            }
        }
        MyFile.close();
        return GetEmptyUser();
    }
    static bool IsUserExists(std::string UserName)
    {
        clsUser User = Find(UserName);
        return (!User.IsEmpty());
    }
    enum enSaveResults
    {
        svFailedEmptyObject = 0,
        svSucceeded = 1,
        svErrorUserIsExists = 2,
    };
    enSaveResults Save()
    {
        switch (_Mode)
        {
        case enMode::EmptyMode:
            return enSaveResults::svFailedEmptyObject;

        case enMode::UpdateMode:
        {
            _Update();
            return enSaveResults::svSucceeded;
        }
        case enMode::AddNewUser:
        {
            if (IsUserExists(_UserName))
            {
                return enSaveResults::svErrorUserIsExists;
            }
            else
            {
                _AddNew();
                _Mode = enMode::UpdateMode;
                return enSaveResults::svSucceeded;
            }
        }
        default:
            enSaveResults::svFailedEmptyObject;
        }
    }
    bool Delete()
    {
        std::vector<clsUser> vUser = _LoadUsersDataFromFile();
        bool IsFound = false;
        for (clsUser &User : vUser)
        {
            if (User.UserName() == _UserName)
            {
                User._MarkToDelete = true;
                IsFound = true;
                break;
            }
        }
        if (!IsFound)
            return false;

        _SaveUsersDataToFile(vUser);
        *this = GetEmptyUser();
        return true;
    }
    static clsUser GetAddNewUserObject(std::string UserName)
    {
        return clsUser(enMode::AddNewUser, "", "", "", "", UserName, "", -1);
    }
    static std::vector<clsUser> GetUsersList()
    {
        return _LoadUsersDataFromFile();
    }
    enum enPermissions
    {
        pAll = -1,
        pListClient = 1,
        pAddNewClient = 2,
        pDeleteClient = 4,
        pUpdateClient = 8,
        pFindClient = 16,
        pTransaction = 32,
        pManageUserMenu = 64
    };
    bool CheckAccessPermission(enPermissions Permissions)
    {
        if(this->Permissions() == enPermissions::pAll)
        return true;

        return ((this->Permissions() & Permissions )== Permissions);
    }    
};
