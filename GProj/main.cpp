//
//  main.cpp
//  GProj
//
//  Created by Andrew on 10/24/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include <string>
#include "MenuSystem.h"
using namespace std;

static const char *guiString = "gui";
void usageStatement();
int main (int argc, const char * argv[])
{

    // Starting the command line version of the application
    if(argc == 1)
    {
        MenuSystem *menuSystem = MenuSystem::sharedMenuSystem();
        menuSystem->start();
    }
    // Starting the GUI version of the application
    else if (argc == 2)
        if(strncmp(argv[1], guiString, strlen(guiString)) == 0)
            cout << "Executing GProj GUI" << endl;
        else
            usageStatement();
    // Syntax for invoking this application is incorrect
    else
        usageStatement();
    
    return 0;
}

void usageStatement()
{
    cout << "Usage: gproj [gui]" << endl;
}
