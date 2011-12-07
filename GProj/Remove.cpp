//
//  Remove.cpp
//  GProj
//
//  Created by Andy on 12/6/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "MenuOption.h"
#include "Remove.h"

Remove::Remove(MenuSystem *menuSystem) : Menu(menuSystem)
{
    setOptions();
}

Remove::~Remove()
{
    
}

bool Remove::isOption(int optionInt)
{
    if((_locations.size() >= optionInt)&&(optionInt != 0))
        return true;
    else
        return false;
}

void Remove::setOptions()
{
    vector<MenuOption *> options;
    
    MenuOption *viewLocationOption = new MenuOption('l',"Choose a location",MenuSystem::LOCATION);
    options.push_back(viewLocationOption);
    MenuOption *addRemoveOption = new MenuOption('r',"Return to the location options",MenuSystem::ADDREMOVE);
    options.push_back(addRemoveOption);
    MenuOption *exitOption = new MenuOption('e',"Exit the program.",MenuSystem::EXIT);
    options.push_back(exitOption);
    
    Menu::setOptions(options);
}

void Remove::displayLocations()
{
    cout << "Locations" << endl;
    cout << "=========" << endl;
    
    int position = 0;
    for(vector<string>::iterator it = _locations.begin(); it != _locations.end(); it++)
        cout << ++position << ". " << *it << endl;
    cout << endl;
}

void Remove::startInterface()
{
    if(_menuSystem->shouldDoLocationUpdate())
        _locations = _menuSystem->updateLocations();
    
    Menu::startInterface();
    displayLocations();
    displayOptions();
}

void Remove::displayMenu()
{
    if(_menuSystem->shouldDoLocationUpdate())
        _locations = _menuSystem->updateLocations();
    
    clearScreen();
    displayLocations();
    displayOptions();
}

MenuSystem::MenuType Remove::menuType()
{
    return MenuSystem::REMOVEDIR;
}

void Remove::processInput(string inputString)
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
            string locationToRemove = _locations[menuChoiceInt-1];
            _menuSystem->removeLocation(locationToRemove);
            displayMenu();
            cout << endl << "Removing location: " << locationToRemove << endl;
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
            else if(menuType == MenuSystem::LOCATION)
            {
                change(MenuSystem::LOCATION);
            }
            else if (menuType == MenuSystem::ADDREMOVE)
            {
                change(MenuSystem::ADDREMOVE);
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
    else
    {
        printInvalidAndProcess();
    }

}
