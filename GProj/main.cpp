//
//  main.cpp
//  GProj
//
//  Created by Andrew on 10/24/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <CoreFoundation/CoreFoundation.h>
#include <iostream>
#include <string>
#include "MenuSystem.h"
using namespace std;

static const char *GUISTRING = "gui";
void usageStatement();
int main (int argc, const char * argv[])
{

    
    CFBundleRef bundle = CFBundleGetMainBundle();
    CFArrayRef resourceURLs = CFBundleCopyResourceURLsOfType(bundle, NULL, NULL);
    char stringBuf[1000];
    
    for(int i = 0; i < CFArrayGetCount(resourceURLs); i++)
    {
        CFURLRef url = (CFURLRef)CFArrayGetValueAtIndex(resourceURLs,i);
        CFStringRef urlString = CFURLGetString(url);

        if(CFStringGetCString(urlString, stringBuf, 1000, kCFStringEncodingUTF8))
            printf("Stringbuf %s\n",stringBuf);
        else
            printf("The string failed to convert again\n");
    }
     
    
    // Starting the command line version of the application
    if(argc == 1)
    {
        MenuSystem *menuSystem = MenuSystem::sharedMenuSystem();
        menuSystem->start();
        delete menuSystem;
    }
    // Starting the GUI version of the application
    else if (argc == 2)
        if(strncmp(argv[1], GUISTRING, strlen(GUISTRING)) == 0)
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
