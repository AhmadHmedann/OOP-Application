I have two main classes clsPerson and clsBankClient that inherit clsPerson
                                          %%%%%%%%%%%%%   clsBankClient  %%%%%%%%%%%%%%%%%%%

I have Get and Set for {(FirstName,LastName,Email,Phone ) + FullName()} and _accountNumber, _PinCode , _ AccountBalance and _mode
I have set and get for all private member (FirstName,LastName,Email,Phone,accountNumber(only read),pinCode,AccountBalance )
 I set the mode when I create a new object 
                                            
                                            &&&&&Find Client &&&&&&
The Method in my class{
void GetEmptyObject() That return an empty object (enMode::EmptyMode,"","","","","",,,,,,0);

static clsBankClient _ConvertLineToClientObject(std::string line, std::string Separator = "#//#")

static std::string _ConvertClientObjectToLine(clsBankClient Client, std::string Separator = "#//#") ;

static std::vector<clsBankClient> _LoadClientsDataFromFile() : 

static void _SaveClientsDataToFile(std::vector<clsBankClient> vClients) ;

static clsBankClient Find(std::string AccountNumber)'
static clsBankClient Find(std::string AccountNumber, std::string PinCode) if I found the client return the client with enMode::Updated if not return empty client with enMode::emptyMode.

static bool IsClientExist(std::string AccountNumber)

}
  void _Update() I use this to Find the old client in the vector and replace it with the current updated object, and  overwrite vClients to the file

enSaveResults Save() based on the mood of that object i will return enSaveResults::svFailed... if the _Mode == enMode::EmptyMode or I will Update the file with the new data and return enSaveResults::scSucceeded if the  _Mode == enMode::Updated 

                                        &&&&&&&&&&& Add new Client  &&&&&&&&&&&
void _AddNew()
void _AddNewDataLineToFile(std::string Line)
static clsBankClient GetAddNewClientObject(std::string AccountNumber) with enMode::AddNewClient;
add this option to enSaveResults  ..svFailedAccountNumberExists=2,
Update my save Function add new case {
     case enMode::AddNewClient:
        {
            if (IsClientExist(_AccountNumber))
            {
                return enSaveResults::svFailedAccountNumberExists;
            }else{

                _AddNew();
                _Mode = enMode::UpdateMode;
                return enSaveResults::svSucceeded;
            }
            break;
        }
}


                                                        Delete a Client

