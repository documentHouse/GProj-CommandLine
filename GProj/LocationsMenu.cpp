//
//  LocationsMenu.cpp
//  GProj
//
//  Created by Andy on 10/24/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//



#include "Menu.h"
#include "LocationsMenu.h"

LocationsMenu::LocationsMenu(MenuSystem *menuSystem) : Menu(menuSystem)
{
    setOptions();
}

LocationsMenu::~LocationsMenu()
{
    
}

bool LocationsMenu::isOption(int optionInt)
{
    if((_locations.size() >= optionInt)&&(optionInt != 0))
        return true;
    else
        return false;
}

void LocationsMenu::setOptions()
{
    vector<MenuOption *> options;
   
    map<string,string> configurations = _menuSystem->updateConfigurations();
    _previousLocation = configurations[_menuSystem->CONFIGKEY_PREVIOUS];
    
    string quickOptionString = "Quick open the last location: ";
    quickOptionString.append(_previousLocation);
    
    MenuOption *quickOption = new MenuOption('*',quickOptionString,MenuSystem::ADDREMOVE);
    options.push_back(quickOption);
    MenuOption *addOption = new MenuOption('a',"Add or Remove directories from locations",MenuSystem::ADDREMOVE);
    options.push_back(addOption);
    MenuOption *exitOption = new MenuOption('e',"Exit the program.",MenuSystem::EXIT);
    options.push_back(exitOption);

    Menu::setOptions(options);
}

void LocationsMenu::displayLocations()
{
    cout << "Locations" << endl;
    cout << "=========" << endl;
    
    int position = 0;
    for(vector<string>::iterator it = _locations.begin(); it != _locations.end(); it++)
        cout << ++position << ". " << *it << endl;
    cout << endl;
}

bool LocationsMenu::openShell(const char *directory)
{
    int val;
    if((val = chdir(directory)) != 0)
        return false;
    else
    {
        cout << "Here is the returned val: " << val << endl;
        clearScreen();
        cout << "Opening bash in directory: " << directory << endl;
        system("bash");
        return true;
    }
}

void LocationsMenu::startInterface()
{
    if(_menuSystem->shouldDoLocationUpdate())
        _locations = _menuSystem->updateLocations();
    
    Menu::startInterface();
    displayLocations();
    displayOptions();
}

void LocationsMenu::displayMenu()
{
        
    clearScreen();
    displayLocations();
    displayOptions();
}

MenuSystem::MenuType LocationsMenu::menuType()
{
    return MenuSystem::LOCATION;
}


void LocationsMenu::processInput(string inputString)
{
    
    // Shortcut to the first choice    
    if(inputString.length() == 0)
    {
        openShell(_previousLocation.c_str());
        displayMenu();
        process();
    }
    
    // Holds the value entered by the user for this menu
    static int menuChoiceInt;
    static char menuChoiceChar;
    
    // Holds whether the entered value is valid
    static bool isValidInt; 
    static bool isValidChar;
    
    isValidInt = validateInt(inputString, &menuChoiceInt);
    isValidChar = validateChar(inputString, &menuChoiceChar);
    
    if(isValidInt)
    {
        if(isOption(menuChoiceInt))
        {
            if(openShell(_locations[menuChoiceInt - 1].c_str()))
                _menuSystem->changePreviousLocation(_locations[menuChoiceInt - 1].c_str());
            displayMenu();
            process();
        }
        else
        {
            printInvalidAndProcess();
        }

    }
    else if(isValidChar)
    {
        if(Menu::isOption(menuChoiceChar))
        {
            MenuSystem::MenuType menuType = getOption(menuChoiceChar)->getValue();
            if(menuType == MenuSystem::EXIT)
            {
                kill();
            }
            else
            {
                // Assuming there are no more menus for now
                change(MenuSystem::ADDREMOVE);
            }
        }
        else
        {
            printInvalidAndProcess();
        }
    }
    else
    {
        printInvalidAndProcess();
    }

}
