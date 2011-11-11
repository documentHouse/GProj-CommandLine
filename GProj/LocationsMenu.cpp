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
    updateOptions();
}

LocationsMenu::~LocationsMenu()
{
    for(vector<MenuOption *>::iterator it = _options.begin(); it != _options.end(); it++)
        delete *it;
}

bool LocationsMenu::isOption(int optionInt)
{
    if((_locations.size() >= optionInt)&&(optionInt != 0))
        return true;
    else
        return false;
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
    MenuOption *addOption = new MenuOption('a',"Add or Remove directories from locations",MenuSystem::ADDREMOVE);
    _options.push_back(addOption);
    MenuOption *exitOption = new MenuOption('e',"Exit the program.",MenuSystem::EXIT);
    _options.push_back(exitOption);
}

void LocationsMenu::displayOptions()
{
    
    cout << "Options" << endl;
    cout << "=======" << endl;
    
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
    cout << endl;
}

bool LocationsMenu::openShell(const char *directory)
{
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
    int menuChoiceInt;
    char menuChoiceChar;
    
    bool isValidInt = validateInt(inputString, &menuChoiceInt);
    bool isValidChar = validateChar(inputString, &menuChoiceChar);

    if(isValidInt)
    {
        //if((_locations.size() >= menuChoiceInt)&&(menuChoiceInt != 0))
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
        if(isOption(menuChoiceChar))
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
