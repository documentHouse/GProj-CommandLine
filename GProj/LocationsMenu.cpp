//
//  LocationsMenu.cpp
//  GProj
//
//  Created by Andy on 10/24/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//



#include "Menu.h"
#include "LocationsMenu.h"

extern char **environ;

LocationsMenu::LocationsMenu(MenuSystem *menuSystem) : Menu(menuSystem)
{
    _locations = _menuSystem->updateLocations();
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
    cout << "Trying to open the shell for directory: " << directory << endl;
    if(chdir(directory) != 0)
        return false;
    else
    {
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
            openShell(_locations[menuChoiceInt - 1].c_str());
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
                cout << "The PWD: " << getenv("PWD") << endl;

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
