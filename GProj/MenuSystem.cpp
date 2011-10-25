//
//  MenuSystem.cpp
//  GProj
//
//  Created by Andrew on 10/24/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//


#include "MenuSystem.h"

MenuSystem *MenuSystem::menuSystem = NULL;

MenuSystem *MenuSystem::sharedMenuSystem()
{
    if(menuSystem != NULL)
        return menuSystem;
    
    menuSystem = new MenuSystem;
    return menuSystem;
}

MenuSystem::MenuSystem()
{
    
    ofstream locationsFile;
    locationsFile.open("Locations.gproj");
    locationsFile << "Hi, this is the first text" << endl;
    locationsFile << "Here is some more text" << endl;
    locationsFile.close();
    
    ifstream locations;
    string line;
    locations.open("Locations.gproj");
    while (!locations.eof()) {
        getline(locations, line);
        cout << line << endl;
    }
    locations.close();
    
    LocationsMenu *locationsMenu = new LocationsMenu(this);
    currentMenu = locationsMenu;
    menus.push_back(locationsMenu);
}

MenuSystem::~MenuSystem()
{

}

void MenuSystem::start()
{
    cout << "Starting..." << endl;
    currentMenu->startInterface();
}


