



#include<iostream>
// #include "clsLoginScreen.h"
#include "Screens/clsLoginScreen.h"

int main()
{
    while (true)
    {
        if (!clsLoginScreen::ShowLoginScreen())
        {
            break;
        }
    }
}
