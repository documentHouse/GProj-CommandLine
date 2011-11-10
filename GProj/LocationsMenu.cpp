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
    _locations = _menuSystem->updateLocations();
    updateOptions();
}

LocationsMenu::~LocationsMenu()
{
    for(vector<MenuOption *>::iterator it = _options.begin(); it != _options.end(); it++)
        delete *it;
}

bool LocationsMenu::isOption(char optionChar)
{
    for(vector<MenuOption *>::iterator it = _options.begin(); it != _options.end(); it++)
        if((*it)->getChar() == optionChar)
            return true;
    
    return false;
}

MenuOption *LocationsMenu::getOption(char optionChar)
{
    for(vector<MenuOption *>::iterator it = _options.begin(); it != _options.end(); it++)
        if((*it)->getChar() == optionChar)
            return *it;
    
    return NULL;
}

void LocationsMenu::updateOptions()
{
    MenuOption *exitOption = new MenuOption('e',"Exit the program.",MenuSystem::EXIT);
    _options.push_back(exitOption);
}

void LocationsMenu::displayOptions()
{
    
    // You will need to store the MenuType in the description instead of a string
    // so that you can use this context to pass information...
    // Maybe you can handle this locally since what you present in the options 
    // menu may derive from the internal state of the current menu.
    
    for(vector<MenuOption *>::iterator it = _options.begin(); it != _options.end(); it++)
        cout << (*it)->getChar() << ". " << (*it)->getString() << endl;
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
    displayLocations();
    displayOptions();
}

void LocationsMenu::displayMenu()
{
    clearScreen();
    displayLocations();
    displayOptions();
}

string LocationsMenu::description()
{
    return string("Locations");
}

#define printInvalidAndProcess() cout << "Your entry was invalid" << endl;process();
void LocationsMenu::processInput(string inputString)
{
    // Holds the value entered by the user for this menu
    int menuChoiceInt;
    char menuChoiceChar;
    
    bool isValidInt = validateInt(inputString, &menuChoiceInt);
    bool isValidChar = validateChar(inputString, &menuChoiceChar);

    if(isValidInt)
    {
        if((_locations.size() >= menuChoiceInt)&&(menuChoiceInt != 0))
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
        if(isOption(menuChoiceChar))
        {
            MenuSystem::MenuType menuType = getOption(menuChoiceChar)->getValue();
            if(menuType == MenuSystem::EXIT)
            {
                kill();
            }
            else
            {
                // You will probably call change(MenuType) here to move to a different menu
                process();
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
    
    // If we pick one of the directories then we open the shell in it
       
    //change(MenuSystem::LOCATION);
}
