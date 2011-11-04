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
#include "CString.h"
#include "sys/stat.h"
using namespace std;


void callback();
void callback(){
    printf("I am a registered callback.\n");
    //chdir("/Users/andrew/nachos");
    //system("bash command pwd");
    //system("cd /Users/andrew/nachos");
    //system("pwd");
    //system("ls");
    //setenv("PWD", "/Users/andrew", true);
    //system("pwd");
    system("bash");
    system("exit");
}

static const char *GUISTRING = "gui";
void usageStatement();
int main (int argc, const char * argv[])
{
    
    atexit(callback);
    
    int ret;
    ret = mkdir("/Users/andrew/BundleDir/MyDir", S_IFDIR | S_IRWXU | S_IRWXG | S_IRWXO);
    printf("The value of the return value is %d\n",ret);
    ret = mkdir("/Users/andrew/BundleDir/MyDir", S_IFDIR | S_IRWXU | S_IRWXG | S_IRWXO);
    printf("The value of the return value is %d\n",ret);
    ret = mkdir("/Users/andrew/BundleDir/Space Dir", S_IFDIR | S_IRWXU | S_IRWXG | S_IRWXO);
    printf("The value of the return value is %d\n",ret);
    
    /*
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
    */
    
    return 0;
}

void usageStatement() { cout << "Usage: gproj [gui]" << endl; }
