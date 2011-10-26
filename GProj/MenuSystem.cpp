//
//  MenuSystem.cpp
//  GProj
//
//  Created by Andrew on 10/24/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//


#include "MenuSystem.h"

const string MenuSystem::LOCATIONSFILENAME = "Locations.gproj";
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
     
    // Setup the file we read locations from
    locationsFileIn = new ifstream(LOCATIONSFILENAME.c_str(),ios::in);
    
    // Set up the initial menu for the user
    LocationsMenu *locationsMenu = new LocationsMenu(this);
    currentMenu = locationsMenu;
    menus.push_back(locationsMenu);
}

MenuSystem::~MenuSystem()
{
    locationsFileOut->close();
    delete locationsFileOut;
    
    locationsFileIn->close();
    delete locationsFileIn;
}

void MenuSystem::startProcessingLoop()
{
    cout << "Processing..." << endl;
    
    MenuSignal signal;
    do {
        
        signal = KILL;
        
    } while (signal != KILL);
}

void MenuSystem::start()
{
    currentMenu->startInterface();
    this->startProcessingLoop();
}


