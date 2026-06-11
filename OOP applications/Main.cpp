#include <iostream>
using namespace std;
#include "clsUtilities.h"
#include "clsBanckClient.h"
#include "clsInputValidation.h"

void ReadClientInfo(clsBankClient &Client)
{
    std::cout << "\n Enter FirstName: ";
    Client.SetFirstName(clsInputValidation::ReadString());

    std::cout << "\n Enter LastName: ";
    Client.SetLastName(clsInputValidation::ReadString());

    std::cout << "\n Enter Email: ";
    Client.SetEmail(clsInputValidation::ReadString());

    std::cout << "\n Enter Phone: ";
    Client.SetPhone(clsInputValidation::ReadString());

    std::cout << "\n Enter PinCode: ";
    Client.SetPinCode(clsInputValidation::ReadString());

    std::cout << "\n Enter Account Balance: ";
    Client.SetAccountBalance(clsInputValidation::ReadFloatNumber());
}

void UpdateClient()
{
    std::cout << "\n Please Enter client account number: ";
    std::string AccountNumber = clsInputValidation::ReadString();
    while (!clsBankClient::IsClientExist(AccountNumber))
    {
        std::cout << "\nAccount Number is not found, choose another one: ";
        AccountNumber = clsInputValidation::ReadString();
    }
    clsBankClient client = clsBankClient::Find(AccountNumber);
    client.Print();

    std::cout << "\n\n Update Client Info:";
    std::cout << "\n_____________________________________\n";

    ReadClientInfo(client);

    clsBankClient::enSaveResults SaveResults = client.save();
    switch (SaveResults)
    {
    case clsBankClient::enSaveResults::svFailedEmptyObject:

    {
        cout << "\nError account was not saved because it's Empty";
        break;
    }
    case clsBankClient::enSaveResults::svSucceeded:
    {
        cout << "\nAccount Updated Successfully :-)\n";
        client.Print();
        break;
    }
    default:
        break;
    }
}

void AddNewClient()
{
   
    std::cout << "\n Please Enter client account number: ";
    std::string AccountNumber = clsInputValidation::ReadString();
    while (clsBankClient::IsClientExist(AccountNumber))
    {
        std::cout << "\nAccount Number is already used, choose another one: ";
        AccountNumber = clsInputValidation::ReadString();
    }
    clsBankClient NewClient = clsBankClient::GetAddNewClientObject(AccountNumber);
    ReadClientInfo(NewClient);
    clsBankClient::enSaveResults SaveResults = NewClient.save();

    switch (SaveResults)
    {
        case clsBankClient::enSaveResults::svSucceeded:
        {
            std::cout<<"\nAccount Added successfully :(";
            NewClient.Print();
            break;
        }
    case clsBankClient::enSaveResults::svFailedEmptyObject:

    {
        cout << "\nError account was not saved because it's Empty";
        break;
    }
    case clsBankClient::enSaveResults::svFailedAccountNumberExist:
    {
        cout << "\nError account was not saved because account number is used!\n";
        break;
    }

    default:
        break;
    }
}
int main()
{

    AddNewClient();

}