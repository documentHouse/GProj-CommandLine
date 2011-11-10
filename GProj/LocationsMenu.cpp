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
    
}

void LocationsMenu::displayLocations()
{
    cout << "Locations" << endl;
    cout << "=========" << endl;
    
    int position = 0;
    for(vector<string>::iterator it = _locations.begin(); it != _locations.end(); it++)
        cout << ++position << ". " << *it << endl;
}

bool LocationsMenu::openShell(const char *directory)
{
    if(chdir(directory) != 0)
        return false;
    else
    {
        clearScreen();
        system("bash");
        return true;
    }
}

void LocationsMenu::startInterface()
{
    Menu::startInterface();
    this->displayLocations();
}

string LocationsMenu::description()
{
    return string("Locations");
}


void LocationsMenu::processInput(string inputString)
{
    // Holds the value entered by the user for this menu
    int menuChoice;
    
    if(validateInt(inputString, &menuChoice))
        ;
    else
    {
        cout << "Your entry was invalid" << endl;
        process();
    }
    
    // If we pick one of the directories then we open the shell in it
    if((_locations.size() >= menuChoice)&&(menuChoice != 0))
    {
        openShell(_locations[menuChoice - 1].c_str());
        kill();
    }
    
    //change(MenuSystem::LOCATION);
}
