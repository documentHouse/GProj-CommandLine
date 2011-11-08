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
    if(system("bash") != 0)
        return false;
    return true;
}

void LocationsMenu::startInterface()
{
    this->displayLocations();
}

string LocationsMenu::description()
{
    return string("Locations");
}

#define kill() signalKill();return;
#define change(TYPE) signalChange(TYPE);return;
#define process() signalProcess();return;

void LocationsMenu::processInput(string inputString)
{
    //cout << "Menu: " << description() << endl << " Input String: " << inputString << endl; 
    
    int choice;
    
    if(validateInt(inputString, &choice))
    {
        cout << "Hopefully about to clear the screen" << endl;
        putp(clear_screen);
        ;//putp(clear_screen);//system("clear");//cout << "Here was your choice: " << choice << endl;
    }
    else
    {
        cout << "Your entry was invalid" << endl;
        process();
    }
    
    // If we pick one of the directory then we open the shell in it
    if((_locations.size() >= choice)&&(choice != 0))
    {
        openShell(_locations[choice - 1].c_str());
        kill();
    }
    
    //change(MenuSystem::LOCATION);
    
    /*
    static int sel = 0;
    if(++sel%3 == 0)
        signalKill();
     */
}
