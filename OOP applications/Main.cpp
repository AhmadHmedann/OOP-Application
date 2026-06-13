#include <iostream>
using namespace std;
#include "clsBankClient.h"
#include "clsInputValidation.h"

void ReadClientInfo(clsBankClient &Client)
{
    std::cout << "\nEnter FirstName: ";
    Client.SetFirstName(clsInputValidation::ReadString());
    std::cout << "\nEnter LastName; ";
    Client.SetLastName(clsInputValidation::ReadString());
    std::cout << "\nEnter Email: ";
    Client.SetEmail(clsInputValidation::ReadString());
    std::cout << "\nEnter Phone: ";
    Client.SetPhone(clsInputValidation::ReadString());
    std::cout << "\nEnter PinCode: ";
    Client.SetPinCode(clsInputValidation::ReadString());
    std::cout << "\nEnter Account Balance; ";
    Client.SetAccountBalance(clsInputValidation::ReadFloatNumber());
}
void UpdateClient()
{
    std::cout << "\nPlease Enter Account Number: ";
    std::string AccountNumber = clsInputValidation::ReadString();

    while (!clsBankClient::IsClientExist(AccountNumber))
    {
        std::cout << "Account number is not found, Please Enter another one: ";
        AccountNumber = clsInputValidation::ReadString();
    }
    clsBankClient Client = clsBankClient::Find(AccountNumber);
    Client.Print();
    std::cout << "\n\n Update Client Info:";
    std::cout << "\n______________________________________________________________\n";
    ReadClientInfo(Client);
    // note: this code below is to separate UI
    clsBankClient::enSaveResults SaveResults = Client.Save();
    switch (SaveResults)
    {
    case clsBankClient::enSaveResults::svSucceeded:
    {
        Client.Print();
        std::cout << "\nAccount Updated successfully :)";
        break;
    }
    case clsBankClient::enSaveResults::svFailedEmptyObject:
    {
        std::cout << "\nError, Account was not save because it's Empty. ";
        break;
    }
    default:
    {
        std::cout << "\nUnknown save result.";
        break;
    }
    }
}
void AddNewClient()
{
    std::cout << "Please Enter Account Number: ";
    std::string AccountNumber = clsInputValidation::ReadString();
    while (clsBankClient::IsClientExist(AccountNumber))
    {
        std::cout << "\nClient with [" << AccountNumber << "] is already exist, please Enter another one.";
        AccountNumber = clsInputValidation::ReadString();
    }
    clsBankClient NewClient = clsBankClient::GetAddNewClientObject(AccountNumber);
    ReadClientInfo(NewClient);
    clsBankClient::enSaveResults SaveResults = NewClient.Save();
    switch (SaveResults)
    {
    case clsBankClient::enSaveResults::svSucceeded:
        std::cout << "\nClient Added successfully :)";
        break;
    case clsBankClient::enSaveResults::svFailedAccountNumberExists:
        std::cout << "\nError account was not saved because account number is used!\n";
        break;
    case clsBankClient::enSaveResults::svFailedEmptyObject:
    {
        std::cout << "\nError, Account was not save because it's Empty. ";
        break;
    }
    default:
    {
        std::cout << "\nUnknown save result.";
        break;
    }
    }
}
void DeleteClient()
{
    std::cout << "\nPlease Enter an Account Number: ";
    std::string AccountNumber = clsInputValidation::ReadString();
    while (!clsBankClient::IsClientExist(AccountNumber))
    {
        std::cout << "Account Number is not Found. Please Enter another one: ";
        AccountNumber = clsInputValidation::ReadString();
    }
    clsBankClient Client = clsBankClient::Find(AccountNumber);
    Client.Print();

    
    char Confirm;
    std::cout<<"Are you sure you want to Delete this client? Y/N? ";
    std::cin>>Confirm;
    if(std::tolower(Confirm)=='y')
    {
        if(Client.Delete())
        {
            std::cout<<"\nClient Deleted Successfully. \n";
            Client.Print(); 
        }else{
            std::cout<<"Error: Client was not Deleted \n"; 
        }
    }
}

int main()
{
    DeleteClient();
}