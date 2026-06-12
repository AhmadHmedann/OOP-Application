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