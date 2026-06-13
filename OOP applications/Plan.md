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