



#include<iostream>
#include "clsLoginScreen.h"
#include "clsUser.h"
int main()
{
    while (true)
    {
        if (!clsLoginScreen::ShowLoginScreen())
        {
            // clsUser::UpdateLoginRegisterFile();
            break;
        }
    }
}
