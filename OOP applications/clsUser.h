
#pragma once
#include <iostream>
#include <iomanip>
#include <limits>
#include <vector>
#include <fstream>
#include "clsPerson.h"
#include "clsInputValidation.h"
#include "clsString.h"

class clsUser : protected clsPerson
{

private:
    std::string _UserName;
    std::string _Password;
    int _Permissions;
    bool MarkToDelete = false;
    enum enMode
    {
        EmptyMode = 1,
        UpdateMode = 2,
        AddNewUser = 3,
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

    static std::string _CovertUserObjectToLine(clsUser User, std::string Separator = "#//#")
    {
        return User.FirstName() + Separator + User.LastName() + Separator + User.Email() + Separator + User.Phone() + Separator + User.UserName() + Separator + User.Password() + Separator + to_string(User.Permissions());
    }
    static std::vector<clsUser> _LoadUserFromFile()
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
    static void _SaveUsersToFile(std::vector<clsUser> &vUsers)
    {
        std::fstream Myfile;
        Myfile.open("Users.txt", std::ios::out);
        if (Myfile.is_open())
        {
            for (const clsUser &User : vUsers)
            {
                Myfile << _CovertUserObjectToLine(User) << std::endl;
            }
            Myfile.close();
        }
    }
    void _AddNew()
    {
        AddDataLineToFile(_CovertUserObjectToLine(*this));
    }

    void AddDataLineToFile(std::string Line)
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
        std::vector<clsUser> vUsers = _LoadUserFromFile();
        for (clsUser &User : vUsers)
        {
            if (User.UserName() == _UserName)
            {
                User = *this;
                break;
            }
            _SaveUsersToFile(vUsers);
        }
    }

    bool _IsEmpty()
    {
        return (_Mode == enMode::EmptyMode);
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
    void SetUserName(std::string UserName)
    {
        _UserName = UserName;
    }
    std::string UserName()
    {
        return _UserName;
    }
    void SetPassword(std::string Password)
    {
        _Password = Password;
    }
    std::string Password()
    {
        return _Password;
    }
    void SetPermissions(int Permissions)
    {
        _Permissions = Permissions;
    }
    int Permissions()
    {
        return _Permissions;
    }
    void SetMode(enMode Mode)
    {
        _Mode = Mode;
    }
    enMode Mode()
    {
        return _Mode;
    }

    static clsUser Find(std::string UserName)
    {
      
    }
    enum enSaveResults
    {
        svFailedEmptyObject = 1,
        svSucceeded = 2,
        svErrorUserIsNorExists = 3,
    };
    enSaveResults Save()
    {
        switch (_Mode)
        {
        case enMode::EmptyMode:
            return enSaveResults::svFailedEmptyObject;
            break;
        case enMode::UpdateMode:
        {
            _Update();
            break;
        }
        case enMode::AddNewUser:
        {
            if (_IsUse)
                _AddNew();
            _Mode = enMode::UpdateMode;
            break;
        }
        default:
            break;
        }
    }
};