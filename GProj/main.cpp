//
//  main.cpp
//  GProj
//
//  Created by Andrew on 10/24/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include <string>
#include <sys/stat.h>
#include <getopt.h>
#include "MenuSystem.h"
using namespace std;



static const char *GUISTRING = "gui";
void usageStatement();
int main (int argc, const char * argv[])
{

/*
    int ret;
    ret = mkdir("/Users/andrew/BundleDir/MyDir", S_IFDIR | S_IRWXU | S_IRWXG | S_IRWXO);
    printf("The value of the return value is %d\n",ret);
    ret = mkdir("/Users/andrew/BundleDir/MyDir", S_IFDIR | S_IRWXU | S_IRWXG | S_IRWXO);
    printf("The value of the return value is %d\n",ret);
    ret = mkdir("/Users/andrew/BundleDir/Space Dir", S_IFDIR | S_IRWXU | S_IRWXG | S_IRWXO);
    printf("The value of the return value is %d\n",ret);
 */
    /*
    struct stat sb;
    string dir = "/Users/andy/fakedir/";
    if(stat(dir.c_str(),&sb) == 0)
        cout << "The file passed the test" << endl;
    else
        cout << "The file failed the test" << endl;
    
    if(S_ISDIR(sb.st_mode))
        cout << "We have a directory" << endl;
    else
        cout << "We do not have a directory" << endl;
    */
     
    // Starting the command line version of the application
    if(argc == 1)
    {
        MenuSystem *menuSystem = MenuSystem::sharedMenuSystem();
        menuSystem->start();
        delete menuSystem;
    }
    // Starting the GUI version of the application
    else if (argc >= 2)
    {
        if(strncmp(argv[1], GUISTRING, strlen(GUISTRING)) == 0)
            cout << "Executing GProj GUI" << endl;
        else
            usageStatement();
    }
    
    
    return 0;
}

void usageStatement() { cout << "Usage: gproj [gui]" << endl; }
