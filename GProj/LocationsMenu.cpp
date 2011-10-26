//
//  LocationsMenu.cpp
//  GProj
//
//  Created by Andy on 10/24/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//


#include "LocationsMenu.h"

LocationsMenu::LocationsMenu(MenuSystem *menuSystem) : Menu(menuSystem)
{
    
}

void LocationsMenu::startInterface()
{
    cout << "Here are the locations:" << endl;
    system("cd /Users");
}

string LocationsMenu::description()
{
    return string("Locations");
}


