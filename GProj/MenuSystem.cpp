//
//  MenuSystem.cpp
//  GProj
//
//  Created by Andrew on 10/24/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//


#include "MenuSystem.h"
#include "sys/stat.h"

const string MenuSystem::LOCATIONSFILENAME = "Locs/Locations.gproj";
MenuSystem *MenuSystem::menuSystem = NULL;

MenuSystem *MenuSystem::sharedMenuSystem()
{
    if(menuSystem != NULL)
        return menuSystem;
    
    menuSystem = new MenuSystem;
    return menuSystem;
}

/*
string line;
while (!locationsFileIn->eof()) {
    getline(*locationsFileIn, line);
    cout << line << endl;
    }
*/
 
MenuSystem::MenuSystem()
{
    
    // Setup the file we write locations to
    locationsFileOut = new ofstream(LOCATIONSFILENAME.c_str(),ios::out);
    
    if(locationsFileOut->fail())
    {
        cout << "Failed to open the file: " << LOCATIONSFILENAME << endl;
        //mkdir("/Users/andrew",S_IFDIR);
    }
    
    // Setup the file we read locations from
    locationsFileIn = new ifstream(LOCATIONSFILENAME.c_str(),ios::in);
    
    // Set up the initial menu for the user
    LocationsMenu *locationsMenu = new LocationsMenu(this);
    currentMenu = locationsMenu;
    menus.push_back(locationsMenu);
}

MenuSystem::~MenuSystem()
{
    // Destroy all the menus
    for(vector<Menu *>::iterator it = menus.begin(); it != menus.end(); it++)
        delete *it;
    
    locationsFileOut->close();
    delete locationsFileOut;
    
    locationsFileIn->close();
    delete locationsFileIn;
}


void MenuSystem::processingLoop()
{
    cout << "Processing..." << endl;
    string input = "Input string";
    
    MenuSignal signal;
    do {
        currentMenu->processInput(input);
        signal = currentMenu->signal();
    } while (signal != KILL);
}

void MenuSystem::start()
{
    currentMenu->startInterface();
    
    // Testing the auto_ptr concept
    //auto_ptr<Menu> autoMenu(new LocationsMenu(this));
    
    this->processingLoop();
}


