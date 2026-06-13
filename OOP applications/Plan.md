                                        Update client Plan

void Update()
{
    1.I need to read  account number (for now must be exist) 
    2.Now I will make an object (client) and store the date for that account number   Then Update the Info
    3.because i want to separate the UI from My Code 
    I will create (in class) enum enSaveResults {svSucceeded=0,svFailedEmptyObject=1}
    then I will implement a method called save (){
        It will check the _Mode (because I'm calling the function from the object client.save() so the _mode is for that object)
        case Mode::enEmptyMode return enSaveResult::svFailedEmptyObject;
        case Mode::enUpdated   {
            First I have the object(client)In my scope(because I'm still in UpdateClientFunction()) 
            I need to Update the client in my vClients Vector( C = *this)
            then I will rewrite me file (::out) saveDateToFile
            finally return enSaveResult::svSucceeded
        } 
    }
}   
                                    Add New Client
void AddNewClient()
{
    1.First I need a unique Account Number,
    2.I need to create an object( client) with _Mode AddNewClient and the account number
    3.I will use ReadClientInfo Function to add that Info
    Now I have a new object (client) with all the data(the mode is AddNewClient) in my scope (AddNewClient())
    Because I want to separate the UI  I Must complete the process in my class
    In the mode I already added AddNewClient mode in my enMode
    4. I need to add add new client process to my save function 
    so, case enMode::AddNewClient:
    {
        _AddNew()    I convert the object to line and add it to the file
                            ////// there is  a question here  \\\\\\\\\\\\\
        next change the mode to updated (question what is the benefit from that ??) I guess we will figure out soon just be patient
        and lastly i return enSaveResults::svSucceeded;
    }
    5. lastly I go to My function and deal with UI

}

                                    Delete a Client
 1. For this I need to  add a _MarkToDelete member.
    and update my _SaveClientDataToFile() just add one condition if (C._MarkToDelete == false) ......

 2. I need to read account number from the user and make sure the user will enter an exists AccountNumber.
 3. Use Find(AccountNumber) to create a clsBankClient  object that  contains the client's current data.
 4. I need to ask to use to confirm the process 
 5. He did not complete the process in save function He Directly call Delete function .    question why he use boolean if I have only true?????????????????????????????

 6. inside Delete(), load clients from the file into  vector find the client with the same account number  then C._MarkToDelete = true.
 7.  rewrite the file using updated vector
 8. return svSucceeded.
 9. In the UI function, handle the save result and print the correct message.


    