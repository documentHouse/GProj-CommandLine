//
//  main.cpp
//  GProj
//
//  Created by Andrew on 10/24/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include <string>
using namespace std;

void usageStatement();
int main (int argc, const char * argv[])
{

    if(argc == 1)
    {
        cout << "Executing command line gproj" << endl;
    }
    else if (argc == 2)
    {
        const char *guiString = "gui";
        if(strncmp(argv[1], guiString, strlen(guiString)) == 0)
            cout << "Executing gui gproj" << endl;
        else
            usageStatement();
    }
    else
        usageStatement();
    
    return 0;
}

void usageStatement()
{
    cout << "Usage: gproj [gui]" << endl;
}
