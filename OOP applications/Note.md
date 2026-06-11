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

