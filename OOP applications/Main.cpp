#include <iostream>
using namespace std;
#include "clsBankClient.h"
#include "clsInputValidation.h"

void ReadClientInfo(clsBankClient & Client)
{
    std::cout<<"\nEnter FirstName: ";
    Client.SetFirstName(clsInputValidation::ReadString());
    std::cout<<"\nEnter LastName; ";
    Client.SetLastName(clsInputValidation::ReadString());
    std::cout<<"\nEnter Email: ";
    Client.SetEmail(clsInputValidation::ReadString());
    std::cout<<"\nEnter Phone: ";
    Client.SetPhone(clsInputValidation::ReadString());
    std::cout<<"\nEnter PinCode: ";
    Client.SetPinCode(clsInputValidation::ReadString());
    std::cout<<"\nEnter Account Balance; ";
    Client.SetAccountBalance(clsInputValidation::ReadFloatNumber());
}
void UpdateClient()
{
    std::cout<<"\nPlease Enter Account Number: ";
    std::string AccountNumber =  clsInputValidation::ReadString();

    while(!clsBankClient::IsClientExist(AccountNumber))
    {
        std::cout<<"Account number is not found, Please Enter another one: ";
        AccountNumber = clsInputValidation::ReadString();
    }
    clsBankClient Client = clsBankClient::Find(AccountNumber);
    Client.Print();
    std::cout<<"\n\n Update Client Info:";
    std::cout<<"\n______________________________________________________________\n";
    ReadClientInfo(Client);
    //note: this code below is to separate UI 
    clsBankClient::enSaveResults SaveResults = Client.Save();
    switch(SaveResults)
    {
        case clsBankClient::enSaveResults::svSucceeded:
        {
            Client.Print();
            std::cout<<"\nAccount Updated successfully :)";
            break;
        }
        case clsBankClient::enSaveResults::svFailedEmptyObject:
        {
            std::cout<<"\nError, Account was not save because it's Empty. ";
            break;
        }
        default:
        {
            std::cout << "\nUnknown save result.";
            break;
        }
    }
    
}

int main()
{

    UpdateClient();

}