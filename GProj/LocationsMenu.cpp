//
//  LocationsMenu.cpp
//  GProj
//
//  Created by Andy on 10/24/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//


#include "MenuSystem.h"
#include "Menu.h"
#include "LocationsMenu.h"

LocationsMenu::LocationsMenu(MenuSystem *menuSystem) : Menu(menuSystem)
{
    _locations = _menuSystem->createLocations();
}

LocationsMenu::~LocationsMenu()
{
    cout << "Deleting Menu: " << description() << endl;
}

void LocationsMenu::startInterface()
{
    cout << "Here are the locations:" << endl;
    //system("cd /Users");
}

string LocationsMenu::description()
{
    return string("Locations");
}

void LocationsMenu::processInput(string inputString)
{
    cout << "Menu: " << description() << endl << " Input String: " << inputString << endl; 
    
    
    
    
    
    static int sel = 0;
    if(++sel%3 == 0)
        signalKill();
}
